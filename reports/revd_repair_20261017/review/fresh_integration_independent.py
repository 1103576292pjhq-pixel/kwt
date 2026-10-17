"""Inspect immutable fresh integration receipts; no simulation or compilation."""
from pathlib import Path
import datetime
import hashlib
import json
import re
import subprocess
import time
import zipfile
import sys
import numpy as np

ROOT = Path(__file__).resolve().parents[3]
REVIEW = Path(__file__).resolve().parent

def native(p):
    value=str(p.resolve())
    return Path('\\\\?\\'+value) if sys.platform=='win32' and not value.startswith('\\\\?\\') else p

def read(p):
    return json.loads(native(p).read_text(encoding='utf-8'))

def sha(p):
    h=hashlib.sha256()
    with native(p).open('rb') as f:
        for block in iter(lambda:f.read(1024*1024),b''):h.update(block)
    return h.hexdigest()

def disk(value):
    value=str(value)
    m=re.match(r'^/mnt/([a-z])/(.*)$',value)
    return Path(m[1].upper()+':/'+m[2]) if m else Path(value)

def wsl(p):
    p=p.resolve().as_posix()
    return '/mnt/'+p[0].lower()+p[2:]

def hashes(folder, entries):
    for name,digest in entries.items():
        assert sha(folder/name)==digest,(name,digest)

COMMANDS=[]
def command(folder,c,expected=0):
    assert c['exit_code']==expected and c['pid']>0 and 0<c['timeout_seconds']<900 and c.get('finished_utc')
    log=folder/c['log']
    assert sha(log)==c['log_sha256']
    assert read(log.with_suffix(log.suffix+'.command.json'))==c
    assert native(disk(c['cwd'])).is_dir()
    COMMANDS.append(dict(log=str(log.relative_to(ROOT)),exit_code=c['exit_code'],pid=c['pid']))

def scalar_expected(package,report,m,n):
    frozen=read(package/'reports/prototype/vectors/manifest.json')
    result={}
    for task,case in enumerate(report['cases']):
        source=next(c for c in frozen['cases'] if c['case_id']==case['case_id'])
        arrays={}
        for k in ('Xq','Wq','bq'):
            meta=source['arrays'][k];p=package/'reports/prototype/vectors'/meta['path']
            assert sha(p)==meta['sha256']
            arrays[k]=np.load(native(p),allow_pickle=False)
        shift=case['shift']
        assert source['config']['output_shift']==shift
        for row in range(m):
            for col in range(n):
                total=sum(int(arrays['Xq'][row,k])*int(arrays['Wq'][k,col]) for k in range(64))+int(arrays['bq'][col])
                raw=max(-(1<<47),min((1<<47)-1,total))
                mag=abs(raw)
                if shift:
                    q,r=divmod(mag,1<<shift)
                    q+=int(r>(1<<(shift-1)) or (r==(1<<(shift-1)) and q%2==1))
                else:q=mag
                rounded=-q if raw<0 else q
                output=max(-(1<<31),min((1<<31)-1,rounded))
                flags=int(raw!=total)|(int(output!=rounded)<<1)|(4 if row==m-1 and col==n-1 else 0)
                result[(task,row*n+col)]=(output&0xffffffff,flags)
    return result

def readback(out,expected):
    for field,name in enumerate(('cpu-output.txt','cpu-flags.txt')):
        actual={}
        for line in native(out/'cpu'/name).read_text().splitlines():
            task,index,value=line.split();key=int(task),int(index)
            assert key not in actual
            actual[key]=int(value,16)
        assert actual=={key:pair[field] for key,pair in expected.items()}

def cpu_run(package,path,w2=False):
    r=read(path);out=path.parent
    assert r['status']=='PASS' and r['source_unchanged'] is True and r['profile']['tasks']==2
    hashes(package,r['source_sha256']);hashes(package,r['input_sha256']);hashes(out,r['artifacts_sha256'])
    negative=[v['command'] for k,v in r['results'].items() if k.startswith('negative_')]
    for c in r['commands']:command(package,c,-6 if c in negative else 0)
    c=r['results']['cpu']['command'];binary=disk(c['argv'][0]);assert c in r['commands'] and c['exit_code']==0
    assert binary.parent==out/'obj' and binary.name==('Vsoc_cpu_tb_w2' if w2 else 'Vsoc_cpu_tb')
    text=native(package/c['log']).read_text()
    assert 'E203_REVD_PASS ' in text
    m=re.search(r'E203_REVD_PASS ([^\n]+)',text)
    assert {k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',m[1])}==r['results']['cpu']['metrics']
    metrics=r['results']['cpu']['metrics'];expected_count=192 if w2 else 96
    assert all(metrics[k]==expected_count for k in ('outputs','flags','response_outputs','response_flags','pops'))
    assert metrics['tasks']==metrics['starts']==2
    for t in r['results']['cpu']['task_metrics']:
        assert t['cold_cycles']==t['last_write_response']-t['cold_start']+1
        assert t['issue_count']==t['retire_count'] and t['effective_macs']==(6144 if w2 else 3072)
    assert len(r['results']['cpu']['task_metrics'])==2
    if w2:
        assert sha(binary)==r['actual_simulator_executable_sha256']
        assert sha(out/'revd-w2-driver.bin')==r['firmware_binary_sha256']
        for item in r['results']['boundaries'].values():
            assert item['status']=='PASS' and item['token'] in native(package/item['command']['log']).read_text()
    else:
        binding=read(out/'binary-binding.json')
        assert binding['status']=='VERIFIED' and binding['historical_report_modified'] is False
        assert binding['original_report']==path.relative_to(package).as_posix() and binding['original_report_sha256']==sha(path)
        assert binding['actual_executable']==binary.relative_to(package).as_posix()
        assert binding['actual_executable_sha256']==r['compiled_simulator_sha256']==sha(binary)
        assert binding['firmware_binary_sha256']==sha(out/'revd-driver.bin')
        assert binding['cpu_command_record_sha256']==sha(out/'cpu.log.command.json')
        assert binding['cpu_log_sha256']==sha(out/'cpu.log')==c['log_sha256']
        assert binding['binding_script_sha256']==sha(package/'scripts/revd_offline_soc_bindings.py')
    hashes(out/'cpu',r['results']['cpu']['output_sha256'])
    wanted=scalar_expected(package,r,3,32 if w2 else 16);readback(out,wanted)
    return r,len(wanted),sha(binary)

def main():
    state_path=ROOT/'work/revd_repair_20261017/package_state.json';state=read(state_path)
    assert state['status']=='ROUNDTRIP_AND_W2_PASS'
    proof_path=ROOT/state['roundtrip_report'];assert sha(proof_path)==state['roundtrip_report_sha256']
    proof=read(proof_path);assert proof['status']=='PASS' and proof['source_unchanged']
    assert proof['suites']==['manifest','smoke','numeric','cpu-small']
    assert proof['python_isolated_flag'] and proof['original_root_excluded_from_pythonpath']
    package=ROOT/proof['extraction'];stage=ROOT/state['stage'];archive=ROOT/proof['archive']
    assert sha(archive)==proof['archive_sha256']
    assert sha(package/'MANIFEST.json')==sha(stage/'MANIFEST.json')==proof['package_manifest_sha256']==state['manifest_sha256']
    manifest=read(package/'MANIFEST.json');assert len(manifest['files'])==manifest['file_count']==6944
    hashes(package,manifest['files']);hashes(stage,manifest['files'])
    with zipfile.ZipFile(archive) as z:
        assert len(z.namelist())==len(set(z.namelist()))==6945
        for name,digest in {**manifest['files'],'MANIFEST.json':state['manifest_sha256']}.items():
            assert hashlib.sha256(z.read(package.name+'/'+name)).hexdigest()==digest
    summary=read(stage/'SUMMARY.json');hashes(ROOT,summary['current_delivery_source_sha256'])
    assert summary['historical_batch_status']=='TIMEBOX_ENDED_PARTIAL' and summary['official_contest_acceptance'] is False
    cpu_summary=read(ROOT/'reports/revd_repair_20261017/cpu_identity/summary.json');hashes(ROOT,cpu_summary['changed_sources'])
    hashes(ROOT,proof['source_sha256'])
    outer=proof['commands'];assert len(outer)==1
    assert outer[0]['argv'][1:]==['-I','-B',wsl(package/'scripts/revd_offline_reproduce.py'),'--suite','portable','--with-cpu']
    assert disk(outer[0]['cwd'])==package;command(ROOT,outer[0])
    detail_path=ROOT/proof['portable_result'];detail=read(detail_path)
    assert detail['status']=='PASS' and detail['suite']=='portable' and detail['completed_phases']==proof['suites']
    assert detail['tools_unchanged'] and detail['tool_binary_sha256_before']==detail['tool_binary_sha256_after']
    assert detail['manifest']['manifest_sha256']==state['manifest_sha256'] and detail['manifest']['members']==6944
    assert all(disk(p).is_relative_to(package) for p in detail['local_module_origins'].values())
    smoke=[];cpu_path=None
    for phase in detail['phase_results']:
        if phase['phase']=='smoke':
            for run in phase['runs']:
                path=package/run['manifest'];assert sha(path)==run['sha256']
                r=read(path);assert r['status']=='PASS'
                hashes(package,r['source_sha256']);hashes(path.parent,r['input_sha256']);hashes(path.parent,r['output_sha256'])
                for c in r['commands']:command(package,c)
                assert r['comparison']['outputs']==r['comparison']['unique']==r['raw48_trace_checked']==160
                assert r['comparison']['last_count']==1 and sha(path.parent/'sim.vvp')==r['binary_sha256']
                smoke.append(dict(latency=r['config']['READ_LATENCY'],outputs=160))
        else:
            command(package,phase['command']);path=package/phase['evidence'];assert sha(path)==phase['evidence_sha256']
            if phase['phase']=='numeric':
                n=read(path);assert n['status']=='PASS' and n['unit_source_unchanged']
                hashes(package,n['unit_source_sha256']);hashes(path.parent,n['artifacts'])
                for c in n['commands']:command(package,c)
                assert phase['gate']=={'status':'PASS','unit_vectors':2170,'public_core_cases':52,'all_shifts':48}
                assert all(t['passed'] for t in n['tests'])
                for test in n['tests']:
                    if 'manifest' in test:
                        mpath=package/test['manifest'];r=read(mpath);assert r['status']=='PASS'
                        hashes(package,r['source_sha256']);hashes(mpath.parent,r['input_sha256']);hashes(mpath.parent,r['output_sha256'])
                        for c in r['commands']:command(package,c)
            else:
                assert phase['phase']=='cpu-small';cpu_path=path
                cpu,cpu_words,cpu_binary_sha=cpu_run(package,path)
                assert sha(package/phase['binary_binding'])==phase['binary_binding_sha256']==phase['gate']['binary_binding_sha256']
    assert sorted(smoke,key=lambda r:r['latency'])==[{'latency':1,'outputs':160},{'latency':2,'outputs':160}]
    w2_path=ROOT/state['w2_report'];assert sha(w2_path)==state['w2_report_sha256']
    command(ROOT,state['w2_command']);assert disk(state['w2_command']['cwd'])==package
    assert state['w2_command']['argv'][1:]==['-B','scripts/revd_offline_soc_w2_run.py','--stage','small']
    assert '`python3 -B scripts/revd_offline_soc_w2_run.py --stage small`' in (package/'README.md').read_text(encoding='utf-8')
    w2_report,w2_words,w2_binary_sha=cpu_run(package,w2_path,w2=True)
    assert w2_report['tool_sha256']==cpu['tool_sha256']
    assert w2_words==state['w2_independent_output_words']==state['w2_independent_flag_words']==192
    hashes(ROOT,state['w2_independent_oracle_sha256']);hashes(package,state['w2_independent_oracle_sha256'])
    # Re-run only the read-only gate probe, using the actual receipt interpreter.
    argv=['wsl.exe','-d','Ubuntu-24.04','--',detail['python'],'-I','-B',wsl(package/'tests/probe_revd_fresh_cpu_identity.py'),
          '--package-root',wsl(package),'--report',cpu_path.relative_to(package).as_posix(),
          '--out',wsl(REVIEW/'fresh-cpu-probe-independent.json')]
    started=datetime.datetime.now(datetime.timezone.utc).isoformat();t=time.monotonic()
    process=subprocess.run(argv,capture_output=True,timeout=100,cwd=ROOT)
    log=REVIEW/'fresh-cpu-probe-independent.log';log.write_bytes(process.stdout+process.stderr)
    execution=dict(argv=argv,started_utc=started,finished_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
                   seconds=time.monotonic()-t,exit_code=process.returncode,log=log.relative_to(ROOT).as_posix(),log_sha256=sha(log))
    (REVIEW/'fresh-cpu-probe-independent.execution.json').write_text(json.dumps(execution,indent=2)+'\n',encoding='utf-8')
    assert process.returncode==0,(process.returncode,process.stderr)
    probe=read(REVIEW/'fresh-cpu-probe-independent.json')
    assert probe['status']=='PASS' and probe['immutable_bytes_unchanged'] and len(probe['observations'])==5
    assert all(r['matches_expected'] for r in probe['observations'])
    assert probe['observations'][0]['actual']=='ACCEPT' and all(r['actual']=='REJECT' for r in probe['observations'][1:])
    hashes(package,probe['source_sha256'])
    result=dict(status='PASS_INDEPENDENT_FRESH_INTEGRATION_AUDIT',checked_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
                audit_source_sha256=sha(Path(__file__)),manifest_sha256=state['manifest_sha256'],archive_sha256=sha(archive),
                manifest_members_checked_in_stage_extraction_and_zip=6944,zip_members_checked=6945,
                current_delivery_source_files_checked=len(summary['current_delivery_source_sha256']),current_cpu_frozen_source_files_checked=len(cpu_summary['changed_sources']),
                command_records_and_sidecars_checked=len(COMMANDS),command_exit_histogram={str(c):sum(r['exit_code']==c for r in COMMANDS) for c in (0,-6)},
                smoke=smoke,numeric=dict(unit_vectors=2170,public_core_cases=52,all_shifts=48),
                cpu=dict(tasks=2,output_words=cpu_words,flag_words=cpu_words,payload_sha256=cpu_binary_sha),
                w2=dict(tasks=2,output_words=w2_words,flag_words=w2_words,payload_sha256=w2_binary_sha,scalar_integer_oracle='Independent Python integers: DOT64 + bias + sat48 + ties-to-even shift + sat32 + flags + last'),
                independent_fresh_probe=dict(status=probe['status'],positive=1,negative=4,execution_exit_code=0,source_import_root_verified=True),
                historical_batch_status='TIMEBOX_ENDED_PARTIAL',official_contest_acceptance=False,
                state_path=state_path.relative_to(ROOT).as_posix(),state_sha256=sha(state_path),portable_proof_path=proof_path.relative_to(ROOT).as_posix(),portable_proof_sha256=sha(proof_path),
                portable_detail_path=detail_path.relative_to(ROOT).as_posix(),portable_detail_sha256=sha(detail_path),
                cpu_result=cpu_path.relative_to(ROOT).as_posix(),cpu_result_sha256=sha(cpu_path),w2_result=w2_path.relative_to(ROOT).as_posix(),w2_result_sha256=sha(w2_path),
                source_and_package_bytes_unchanged_after_probe=True,
                scope='Read-only receipt/hash validation and independent scalar readback recomputation. No simulator/compiler rerun by this reviewer. External final teammate bundle not yet reviewed.')
    hashes(package,manifest['files']);hashes(ROOT,cpu_summary['changed_sources'])
    out=REVIEW/'fresh_integration_independent.json'
    with out.open('x',encoding='utf-8') as f:f.write(json.dumps(result,indent=2)+'\n')
    print(json.dumps(result,indent=2))

if __name__=='__main__':main()
