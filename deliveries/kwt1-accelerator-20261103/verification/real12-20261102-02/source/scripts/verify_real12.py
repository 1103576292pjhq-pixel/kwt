#!/usr/bin/env python3
"""Real12 data preparation, actual accelerator RTL run and portable audit."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tarfile

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT))
sys.path.insert(0,str(ROOT/'scripts'))
sys.path.insert(0,str(ROOT/'integration/e203/real12_validation'))
import numpy as np
from evaluate_precision import source_identity,checked_audio,sha256
from model.fixed_numeric import encode_finite,ffn1_int16,decode_fixed,load_contract
from real12_audit import audit_result_trace

LABELS=('_silence_','_unknown_','yes','no','up','down','left','right','on','off','stop','go')


def audit_trace(path,expected,references):
    if expected.ndim!=3 or expected.shape[1:]!=(99,256) or references.shape!=expected.shape:
        raise ValueError('Invalid audit shapes')
    return audit_result_trace(path,[row.reshape(-1).tolist() for row in expected],
                              [row.reshape(-1).tolist() for row in references])


def write_json(path,value):
    path.write_text(json.dumps(value,ensure_ascii=False,indent=2,allow_nan=False)+'\n',encoding='utf-8')


def generate_fixtures(folder,cache):
    manifest_path=cache/'manifest.json'
    original=json.loads(manifest_path.read_text())
    if original['status']!='passed' or original['split']!='validation':
        raise ValueError('Completed validation source required')
    identity=source_identity(ROOT.parent)
    if original['source_commit']!=identity['source_commit'] or original['checkpoint_sha256']!=identity['checkpoint_sha256']:
        raise ValueError('Source/checkpoint identity mismatch')
    indexed={row['path']:row for row in original['files']}
    selected=[]
    for layer,label in enumerate(LABELS):
        position=next(i for i,row in enumerate(original['samples']) if row['label']==label)
        sample=dict(original['samples'][position])
        sample.update(layer=layer+1,cache_index=position,task_index=layer)
        selected.append(sample)
    audio_audit=checked_audio(ROOT.parent,selected)
    folder.mkdir()
    goldens=[];references=[];tasks=[];source_hashes={}
    for layer,sample in enumerate(selected):
        arrays={}
        for name in ('X','W','b','Y_reference'):
            rel='layer_%02d/%s.npy'%(layer,name)
            path=cache/rel
            digest=sha256(path)
            if digest!=indexed[rel]['sha256']:
                raise ValueError('Changed source '+rel)
            source_hashes[str(path)]=digest
            arrays[name]=np.load(str(path),mmap_mode='r',allow_pickle=False)
        i=sample['cache_index'];x=arrays['X'][i];w=arrays['W'];b=arrays['b'];ref=arrays['Y_reference'][i]
        enc=[encode_finite(value,role) for value,role in ((x,'x'),(w,'w'),(b,'bias'))]
        y,flags=ffn1_int16(*(v.values for v in enc))
        words=y.astype(np.int32).astype(np.uint32)&65535
        words|=flags.astype(np.uint32)<<16
        goldens.append(words);references.append(np.array(ref,copy=True))
        error=decode_fixed(y,'y')-ref.astype(np.float64)
        nrmse=float(np.sqrt(np.mean(error**2))/max(float(np.sqrt(np.mean(ref.astype(np.float64)**2))),1e-8))
        if not np.isfinite(nrmse) or nrmse>.03:
            raise ValueError('Selected task fails local3% gate')
        for suffix,values,bits in [('x',enc[0].values.reshape(-1),16),
                                   ('w',enc[1].values.T.reshape(-1),16),
                                   ('b',enc[2].values.reshape(-1),32),('y',words.reshape(-1),32)]:
            text=''.join(('%0*x\n'%(bits//4,int(v)&((1<<bits)-1))) for v in values)
            (folder/('case%d-%s.hex'%(layer+1,suffix))).write_text(text,encoding='ascii')
        (folder/('case%d-ref.f32'%(layer+1))).write_bytes(np.asarray(ref,dtype='<f4').tobytes(order='C'))
        tasks.append(dict(sample,software_nrmse=nrmse,software_nrmse_percent=nrmse*100,
                          x_clips=enc[0].endpoint_clipped_count,w_clips=enc[1].endpoint_clipped_count,
                          bias_clips=enc[2].endpoint_clipped_count))
    report=dict(scope='LOCAL_REAL12_REPRESENTATIVE_TASKS_NOT_OFFICIAL_PERFORMANCE_SET',tasks=tasks,
                source=identity,audio_audit=audio_audit,cache_manifest_sha256=sha256(manifest_path),
                source_float_sha256=source_hashes,
                files_sha256={p.name:sha256(p) for p in sorted(folder.iterdir())},
                limitations=['Float cache extracted using TF2.4.0 instead of2.4.0rc1; equivalence unproven.',
                             'ICB initiator is a testbench, not E203 firmware; no official throughput claim.'])
    write_json(folder/'manifest.json',report)
    return np.asarray(goldens),np.asarray(references),report


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--cache',type=Path,default=ROOT.parent/'generated/validation/20261018_val_p20_v1')
    args=parser.parse_args();out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
    sources=[ROOT/line.strip() for line in (ROOT/'rtl/kwt.f').read_text().splitlines()
             if line.strip() and not line.startswith('+')]
    sources+=list((ROOT/'rtl/include').glob('*.vh'))
    tb=ROOT/'tb/interface/tb_icb_real12.v'
    sources+=[tb,ROOT/'tb/memory/support/sram_contract_models.v',ROOT/'model/fixed_numeric.py',
              ROOT/'model/numeric-contract.json',Path(__file__),ROOT/'integration/e203/real12_validation/real12_audit.py']
    before={str(p.relative_to(ROOT)):sha256(p) for p in sources}
    for p in sources:
        dest=out/'source'/p.relative_to(ROOT);dest.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(p,dest)
    report=dict(status='RUNNING',official_macro_verified=False,soc_cpu_executed=False,
                source_sha256=before,commands=[])
    def run(name,argv,expected_failure=False,cwd=ROOT):
        with (out/(name+'.log')).open('w',encoding='utf-8') as log:
            p=subprocess.run(list(map(str,argv)),cwd=cwd,stdout=log,stderr=subprocess.STDOUT,timeout=1200)
        output=(out/(name+'.log')).read_text(encoding='utf-8')
        report['commands'].append(dict(name=name,argv=list(map(str,argv)),returncode=p.returncode))
        write_json(out/'report.json',report)
        if (p.returncode!=0)!=expected_failure:
            raise RuntimeError(name+': '+output[-3000:])
        return output
    try:
        load_contract(ROOT/'model/numeric-contract.json')
        expected,references,fixture_info=generate_fixtures(out/'fixtures',args.cache.resolve())
        report['tasks']=fixture_info['tasks']
        binary=out/'real12.vvp';trace=out/'icb-trace.txt'
        run('compile',['iverilog','-g2012','-DKWT_STORAGE_TEST_CONTRACT','-s','tb_icb_real12',
                       '-o',binary,'-f','rtl/kwt.f',ROOT/'tb/memory/support/sram_contract_models.v',tb])
        # Packed Verilog strings in Icarus cannot safely receive Chinese paths.
        # Run beside the files so all runtime file names remain ASCII.
        output=run('rtl',['vvp',binary,'+fixtures=fixtures','+trace=icb-trace.txt'],cwd=out)
        match=re.search(r'^PASS ICB_REAL12_CONTRACT (.*)$',output,re.M)
        if not match: raise RuntimeError('No real12 summary')
        report['rtl']={key:int(value) for key,value in re.findall(r'(\w+)=(\d+)',match[1])}
        if report['rtl'].get('tasks')!=12 or report['rtl'].get('blocks')!=4800 or report['rtl'].get('outputs')!=304128:
            raise ValueError('Wrong real12 totals')
        report['audit']=audit_trace(trace,expected,references)
        if not report['audit']['all_tasks_within_3_percent']:
            raise ValueError('Actual RTL output fails3% gate')
        negative=run('corrupt-golden',['vvp',binary,'+fixtures=fixtures','+corrupt_first'],True,cwd=out)
        if 'FAIL ICB_SYSTEM Y case0 index0' not in negative:
            raise ValueError('Negative run did not fail on the intended output comparison')
        report['corrupt_golden_caught']=True
        run('software-tests',['python3','-B','-m','unittest','discover','-s','tests','-v'])
        if before!={str(p.relative_to(ROOT)):sha256(p) for p in sources}:
            raise ValueError('RTL/test/model source changed during run')
        if any(sha256(Path(p))!=digest for p,digest in fixture_info['source_float_sha256'].items()):
            raise ValueError('Float data changed during run')
        package=out/'server-package'/'kwt-real12-validation';package.mkdir(parents=True)
        for relative in [Path('rtl/kwt.f')]+[p.relative_to(ROOT) for p in sources if p.suffix in ('.v','.vh') and 'rtl' in p.relative_to(ROOT).parts]+[tb.relative_to(ROOT)]:
            dest=package/relative;dest.parent.mkdir(parents=True,exist_ok=True);shutil.copy2(ROOT/relative,dest)
        shutil.copytree(out/'fixtures',package/'fixtures')
        for name in ('run_official.py','real12_audit.py','README.md'):
            shutil.copy2(ROOT/'integration/e203/real12_validation'/name,package/name)
        package_hashes={p.relative_to(package).as_posix():sha256(p) for p in package.rglob('*') if p.is_file()}
        write_json(package/'package-sha256.json',package_hashes)
        archive=out/'kwt-real12-validation.tar.gz'
        with tarfile.open(archive,'w:gz') as tar: tar.add(package,arcname='kwt-real12-validation')
        report.update(status='PASS_REAL12_RTL_CONTRACT',rtl_and_model_unchanged=True,
                      archive=str(archive),archive_sha256=sha256(archive),archive_bytes=archive.stat().st_size)
        write_json(out/'report.json',report)
        lines=['# 12层真实数据：完整独立加速器RTL对照','',
               '状态：PASS_REAL12_RTL_CONTRACT。实际ICB响应304128项Y/flags与当前整数模型逐位一致，连续12任务4800块；生产RTL未修改。','',
               '| 层 | 样本类 | 实际RTL NRMSE (%) |','| --- | --- | ---: |']
        lines+=['| %d | %s | %.8f |'%(i+1,report['tasks'][i]['label'],task['nrmse_percent'])
                for i,task in enumerate(report['audit']['tasks'])]
        lines+=['','后端为本地SRAM合同模型，发起方为TB。官方模型待服务器运行；不是E203真实CPU12任务、官方任务性能或STA通过。',
                '误差范围、输入来源、所有源码及浮点文件SHA256、实际ICB账本、负向检错和打包信息见report.json。']
        (out/'README.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
        print(match[0],flush=True)
        print('PASS REAL12_AUDIT outputs=304128 bit_mismatches=0 max_nrmse_percent=%.8f'%report['audit']['max_task_nrmse_percent'],flush=True)
        print('UPLOAD',archive,flush=True)
    except Exception as error:
        report.update(status='FAIL_REAL12',error=str(error));write_json(out/'report.json',report);raise


if __name__=='__main__': main()
