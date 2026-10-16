"""Freeze final production/CPU compilation inputs before starting long cases."""
import argparse,json
from pathlib import Path
import sys,time,subprocess
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'dv/encoder'))
from run_encoder import hashes,sha,write,fp32_release,prepare

def paths():
 fixed=['rtl/encoder_core.sv','rtl/encoder_nonlinear.sv','rtl/encoder_sync_ram.sv','rtl/encoder_fp32.sv','rtl/encoder_icb.sv',
        'rtl/ffn1_top.sv','rtl/ffn1_icb.sv','rtl/dot64.sv','rtl/prototype_sync_ram.sv',
        'soc/e203_common/e203_cpu_shell.sv','soc/e203_encoder/e203_encoder_soc.sv','soc/e203_encoder/encoder_shared_ram.sv',
        'sw/encoder_driver.h','sw/encoder_driver.c','sw/e203_encoder/main.c','sw/e203/start.S','sw/e203/link.ld',
        'dv/e203_boot/timescale.v','dv/e203_encoder/tb_e203_encoder.sv','dv/e203_encoder/run_system.py',
        'dv/encoder/tb_encoder.sv','dv/encoder/run_encoder.py','dv/fp32/hardfloat_sources.py',
        'numeric/encoder/verify_bundle.py','numeric/encoder/contracts.py','numeric/encoder/__init__.py',
        'numeric/encoder/encoder_ref.c','numeric/encoder/encoder_ref.h','numeric/encoder/run_reference.py',
        'work/encoder_reference_handoff.json','work/encoder_reference_core_ready.json',
        'scripts/run_encoder.sh','scripts/run_e203_encoder.sh']
 generated=ROOT/'reports/encoder/verification/frozen-hardfloat'
 return [ROOT/p for p in fixed]+[generated/'divSqrtRecFN_small.v',generated/'compatibility.json']+[p for base in ['vendor/e203_hbirdv2-upstream/rtl/e203','vendor/HardFloat-1-upstream/source'] for p in (ROOT/base).rglob('*') if p.is_file()]

def main():
 p=argparse.ArgumentParser();p.add_argument('--verify',action='store_true');a=p.parse_args()
 record=ROOT/'work/encoder_source_freeze.json'
 if not a.verify:prepare(ROOT/'reports/encoder/verification/frozen-hardfloat')
 current=hashes(paths())
 if a.verify:
  data=json.loads(record.read_text(encoding='utf-8'))
  if current!=data['source_sha256'] or fp32_release()!=data['fp32_handoff_sha256']:raise ValueError('production or dependency changed after freeze')
  print('ENCODER_SOURCE_FREEZE_CURRENT files='+str(len(current)));return
 fp=fp32_release()
 # This file freezes sources. Numeric owner already performed full independent
 # readback; bind that immutable release here. Actual case entry points still
 # read every consumed hex/bin/NPY word before running the simulator.
 hand=json.loads((ROOT/'work/encoder_reference_handoff.json').read_text(encoding='utf-8'))
 if hand['status']!='PASS' or not hand.get('read_only_after_handoff'):raise ValueError('numeric source release not frozen')
 for key in ['source_sha256','artifacts_sha256']:
  for relative,digest in hand[key].items():
   if sha(ROOT/relative)!=digest:raise ValueError('numeric release changed '+relative)
 ref=ROOT/'reports/encoder/reference';ref12=ROOT/'reports/encoder/reference-test12'
 for directory in [ref,ref12]:
  status=json.loads((directory/'status.json').read_text(encoding='utf-8'))
  readback=json.loads((directory/'readback-verification.json').read_text(encoding='utf-8'))
  if status['status']!='PASS' or readback['status']!='PASS' or status['manifest_sha256']!=sha(directory/'manifest.json') or readback['manifest_sha256']!=sha(directory/'manifest.json'):raise ValueError('numeric release/readback identity stale')
 toolchain={}
 for name,command in [('python',[sys.executable,'--version']),('verilator',['verilator','--version']),
                      ('iverilog',['iverilog','-V']),('gcc',['gcc','--version']),
                      ('riscv-gcc',['riscv64-unknown-elf-gcc','--version']),('yosys',['yosys','-V'])]:
  done=subprocess.run(command,capture_output=True,text=True,encoding='utf-8',check=True)
  toolchain[name]=(done.stdout+done.stderr).splitlines()[0]
 # Do not create a freeze while a known short check is still failed/stale.
 for rel in ['reports/encoder/verification/checks/status.json','reports/encoder/rtl/nonlinear-icarus/status.json','reports/encoder/rtl/nonlinear-verilator/status.json']:
  data=json.loads((ROOT/rel).read_text(encoding='utf-8'))
  if data['status']!='PASS':raise ValueError('short evidence incomplete '+rel)
  for path,digest in data['source_sha256'].items():
   if sha(ROOT/path)!=digest:raise ValueError('short evidence stale '+path)
 if record.exists():
  previous=json.loads(record.read_text(encoding='utf-8'))
  if previous.get('source_sha256')==current and previous.get('fp32_handoff_sha256')==fp and previous.get('reference_manifest_sha256')==sha(ref/'manifest.json') and previous.get('test12_manifest_sha256')==sha(ref12/'manifest.json'):
   print('ENCODER_SOURCE_FREEZE_REUSED files='+str(len(current)));return
  archive=ROOT/'reports/encoder/verification/source-freezes'/str(time.time_ns());archive.mkdir(parents=True,exist_ok=True)
  (archive/'encoder_source_freeze.json').write_bytes(record.read_bytes())
 write(record,{'status':'FROZEN_FOR_LONG_VALIDATION','created_unix':time.time(),'source_sha256':current,
               'toolchain':toolchain,
               'fp32_handoff_sha256':fp,'reference_manifest_sha256':sha(ref/'manifest.json'),
               'test12_manifest_sha256':sha(ref12/'manifest.json'),
               'policy':'No production, firmware, CPU TB, or imported runner edits after long validation begins; changed sources require stop/archive/fix/reverify.'})
 print('ENCODER_SOURCE_FROZEN files='+str(len(current)))

if __name__=='__main__':
 try:main()
 except Exception as exc:print(str(exc),file=sys.stderr);sys.exit(1)
