#!/usr/bin/env python3
"""Preview/apply a NEW shared-SRAM SoC top, preserving the old top and backups."""
import argparse
import difflib
import hashlib
import json
from pathlib import Path
import re

SOC='rtl/e203/soc/kwt_soc_top.v'
NEW='rtl/e203/soc/kwt_shared_soc_top.v'
TB='tb/tb_top.v'
STAGE='verification/shared_sram_wiring_01'


def digest(data):return hashlib.sha256(data).hexdigest()
def save(path,data):path.write_text(json.dumps(data,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
def inside(root,relative):
    p=root/relative
    if root not in p.resolve().parents:raise ValueError('Path escapes SoC root: '+relative)
    if p.is_symlink():raise ValueError('Refusing symlink input/target: '+relative)
    return p
def once(text,pattern,replacement):
    matches=list(re.finditer(pattern,text,re.M))
    if len(matches)!=1:raise ValueError('Expected one unmodified anchor: '+pattern)
    m=matches[0];new=replacement(m) if callable(replacement) else replacement
    return text[:m.start()]+new+text[m.end():]


def candidates(soc_bytes,tb_bytes,ema=2,emaw=0):
    soc=soc_bytes.decode('utf-8').replace('\r\n','\n')
    tb=tb_bytes.decode('utf-8').replace('\r\n','\n')
    for name in ['kwt_bus_clk','kwt_bus_rst_n','u_kwt_accelerator']:
        if name not in soc:raise ValueError('Expected already-integrated accelerator SoC: '+name)
    soc=once(soc,r'^module\s+kwt_soc_top\s*\(','module kwt_shared_soc_top(')
    wires='''
 // Shared SRAM is separate from accelerator-local X/W SRAM.
 wire [31:0] sysmem_icb_cmd_addr;
 wire sysmem_icb_cmd_read;
 wire [31:0] sysmem_icb_cmd_wdata;
 wire [3:0] sysmem_icb_cmd_wmask;
 wire sysmem_icb_rsp_valid,sysmem_icb_rsp_ready,sysmem_icb_rsp_err;
 wire [31:0] sysmem_icb_rsp_rdata;
'''
    soc=once(soc,r'^[ \t]*wire\s+sysmem_icb_cmd_ready\s*;',lambda m:m[0]+'\n'+wires)
    expected={'cmd_valid':'sysmem_icb_cmd_valid','cmd_ready':'sysmem_icb_cmd_ready',
              'cmd_addr':'','cmd_read':'','cmd_wdata':'','cmd_wmask':'',
              'rsp_valid':'sysmem_icb_cmd_valid','rsp_ready':'sysmem_icb_cmd_ready',
              'rsp_err':"1'b0",'rsp_rdata':"32'b0"}
    for suffix,old in expected.items():
        port='sysmem_icb_'+suffix
        def replace(m):
            if re.sub(r'\s+','',m[1])!=old:raise ValueError('Unknown/already wired SysMem port: '+port)
            return '.'+port+'('+port+')'
        soc=once(soc,r'\.'+port+r'\s*\(([^()]*)\)',replace)
    instance='''
 // DEVELOPMENT shared window, pending official address-map confirmation.
 kwt_shared_sram #(.BASE_ADDR(32'ha0000000),.SRAM_EMA(3'd2),.SRAM_EMAW(2'd0)) u_shared_sram(
   .clk(kwt_bus_clk),.rst_n(kwt_bus_rst_n),
   .icb_cmd_valid(sysmem_icb_cmd_valid),.icb_cmd_ready(sysmem_icb_cmd_ready),
   .icb_cmd_addr(sysmem_icb_cmd_addr),.icb_cmd_read(sysmem_icb_cmd_read),
   .icb_cmd_wdata(sysmem_icb_cmd_wdata),.icb_cmd_wmask(sysmem_icb_cmd_wmask),
   .icb_rsp_valid(sysmem_icb_rsp_valid),.icb_rsp_ready(sysmem_icb_rsp_ready),
   .icb_rsp_rdata(sysmem_icb_rsp_rdata),.icb_rsp_err(sysmem_icb_rsp_err));
'''
    instance=instance.replace(".SRAM_EMA(3'd2)",".SRAM_EMA(3'd%d)"%ema).replace(".SRAM_EMAW(2'd0)",".SRAM_EMAW(2'd%d)"%emaw)
    soc=once(soc,r'^[ \t]*endmodule\b',instance+'\nendmodule')
    tb=once(tb,r'\bkwt_soc_top\s+u_e203_soc_top\s*\(','kwt_shared_soc_top u_e203_soc_top(')
    result={NEW:soc,TB:tb}
    return {rel:text.replace('\n','\r\n').encode('utf-8') if b'\r\n' in (soc_bytes if rel==NEW else tb_bytes)
            else text.encode('utf-8') for rel,text in result.items()}


def preview(root,bundle,stage_name,ema=2,emaw=0,validation_run='official-run-01'):
    stage=inside(root,stage_name)
    if stage.exists() or inside(root,NEW).exists():raise ValueError('Existing preview/new SoC top preserved; use a new stage or inspect existing work')
    raw={rel:inside(root,rel).read_bytes() for rel in (SOC,TB)}
    changed=candidates(raw[SOC],raw[TB],ema,emaw)
    report=dict(root=str(root),bundle=str(bundle),inputs={r:digest(b) for r,b in raw.items()},
                outputs={r:digest(b) for r,b in changed.items()},ema=ema,emaw=emaw,status='PREVIEW_ONLY_NOT_COMPILED')
    stage.mkdir(parents=True)
    for kind,files in [('before',raw),('after',changed)]:
        for rel,data in files.items():
            p=stage/kind/rel;p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(data)
    differences=[]
    for rel,data in changed.items():
        original=raw.get(rel,b'')
        differences.extend(difflib.unified_diff(original.decode().splitlines(True),data.decode().splitlines(True),
                                              fromfile='before/'+rel,tofile='after/'+rel))
    (stage/'wiring.diff').write_text(''.join(differences),encoding='utf-8')
    default_models=Path('/storage1/admin_public_dir/SRAM_Lib_2025/RAMSP4096X16/verilog')
    model_paths=[default_models/name for name in ['RAMSP4096X16_rtl.v','RAMSP4096X16.v']]
    evidence_path=(bundle/validation_run/'report.json').resolve()
    if bundle not in evidence_path.parents:raise ValueError('Validation evidence escapes bundle')
    if evidence_path.is_file():
        evidence=json.loads(evidence_path.read_text(encoding='utf-8'))
        if evidence.get('status')=='PASS_SHARED_SRAM_OFFICIAL_COMPONENTS':
            model_paths=[Path(v['path']).resolve() for v in evidence['official_models']]
    if len(model_paths)!=2 or {p.name for p in model_paths}!={'RAMSP4096X16_rtl.v','RAMSP4096X16.v'}:
        raise ValueError('Expected qualified4096wrapper and model files')
    report['model_paths']=[str(p) for p in model_paths]
    additions=['+define+ARM_UD_MODEL']+['+incdir+'+str(p) for p in sorted({p.parent for p in model_paths})]+[str(bundle/'rtl'/name) for name in
               ['kwt_shared_ram_icb.v','kwt_shared_sram_array.v','kwt_shared_sram.v']]+[str(root/NEW),
               *map(str,model_paths)]
    additions_path=stage/'shared_sram_additions.f'
    additions_path.write_text('\n'.join(additions)+'\n',encoding='utf-8')
    report['additions_sha256']=digest(additions_path.read_bytes())
    save(stage/'report.json',report)
    print('PREVIEW_READY_SHARED_SRAM; original SoC/TB unchanged; inspect',stage/'wiring.diff')


def apply(root,bundle,stage_name,validation_run='official-run-01'):
    stage=inside(root,stage_name)
    report=json.loads((stage/'report.json').read_text(encoding='utf-8'))
    if report['root']!=str(root) or report['bundle']!=str(bundle):raise ValueError('Preview root/bundle differs')
    if set(report['inputs'])!={SOC,TB} or set(report['outputs'])!={NEW,TB}:raise ValueError('Unexpected preview file set')
    if inside(root,NEW).exists() or (stage/'applied.json').exists():raise ValueError('Existing output/applied stage preserved')
    for rel,want in report['inputs'].items():
        if digest(inside(root,rel).read_bytes())!=want:raise ValueError('Source changed since preview: '+rel)
    checked={}
    for rel,want in report['outputs'].items():
        data=(stage/'after'/rel).read_bytes()
        if digest(data)!=want:raise ValueError('Candidate changed since preview: '+rel)
        checked[rel]=data
    if digest((stage/'shared_sram_additions.f').read_bytes())!=report['additions_sha256']:
        raise ValueError('Additional source/model filelist changed since preview')
    manifest=bundle/'package-sha256.json'
    evidence_path=(bundle/validation_run/'report.json').resolve()
    if bundle not in evidence_path.parents:raise ValueError('Validation evidence escapes bundle')
    evidence=json.loads(evidence_path.read_text(encoding='utf-8'))
    if evidence.get('status')!='PASS_SHARED_SRAM_OFFICIAL_COMPONENTS' or evidence.get('package_manifest_sha256')!=digest(manifest.read_bytes()):
        raise ValueError('Matching official component run must PASS before applying')
    if evidence.get('ema',2)!=report['ema'] or evidence.get('emaw',0)!=report['emaw']:
        raise ValueError('Preview EMA/EMAW differs from the qualified component run')
    if [str(Path(v['path']).resolve()) for v in evidence['official_models']]!=report['model_paths']:
        raise ValueError('Preview model paths differ from the qualified component run; make a new preview')
    for info in evidence['official_models']:
        if digest(Path(info['path']).read_bytes())!=info['sha256']:raise ValueError('Official model changed after component run')
    for rel,want in json.loads(manifest.read_text(encoding='utf-8')).items():
        if digest((bundle/rel).read_bytes())!=want:raise ValueError('Bundle changed after component run: '+rel)
    # 新顶层先独占创建；所有输入/候选已检查。备份保留，不声称多文件整体原子写。
    with inside(root,NEW).open('xb') as stream:stream.write(checked[NEW])
    inside(root,TB).write_bytes(checked[TB])
    save(stage/'applied.json',report)
    print('APPLY_DONE_SHARED_SRAM; original kwt_soc_top retained; new top kwt_shared_soc_top')
    print('Recompile original SoC filelist PLUS',stage/'shared_sram_additions.f')
    print('Do not reuse the old simv for CPU shared-RAM tests; CPU execution remains unverified.')


def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('action',choices=['preview','apply']);p.add_argument('--root',type=Path,required=True)
    p.add_argument('--stage',default=STAGE)
    p.add_argument('--validation-run',default='official-run-01')
    p.add_argument('--ema',type=int,choices=range(8),default=2)
    p.add_argument('--emaw',type=int,choices=range(4),default=0)
    args=p.parse_args();root=args.root.resolve();bundle=Path(__file__).resolve().parent
    if not root.is_dir() or root.name!='kwt-soc':p.error('Use the existing isolated kwt-soc copy')
    try:
        if args.action=='preview':preview(root,bundle,args.stage,args.ema,args.emaw,args.validation_run)
        else:apply(root,bundle,args.stage,args.validation_run)
    except (OSError,ValueError,KeyError) as error:print('STOP:',error);return 1
    return 0


if __name__=='__main__':raise SystemExit(main())
