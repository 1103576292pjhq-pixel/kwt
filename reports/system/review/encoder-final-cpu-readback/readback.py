"""Independent, bounded read-only CPU evidence readback; writes only beside self."""
from pathlib import Path
import argparse, datetime as dt, hashlib, importlib.util, json, os, re
import subprocess, sys, tempfile, time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[3]

def digest(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()

def load(path):
    return json.loads(Path(path).read_text(encoding='utf-8-sig'))

def save(name, value):
    (HERE/name).write_text(json.dumps(value, indent=2, ensure_ascii=False)+'\n', encoding='utf-8')

def require(ok, message):
    if not ok:
        raise ValueError(message)

def hashes(mapping):
    require(bool(mapping), 'empty hash mapping')
    for rel, expected in mapping.items():
        path = (ROOT/rel).resolve()
        require(ROOT in path.parents, 'source escaped workspace: '+rel)
        require(digest(path) == expected, 'hash differs: '+rel)
    return len(mapping)

def words(path, count):
    rows = Path(path).read_text(encoding='utf-8').splitlines()
    require(len(rows) == count, 'word count '+str(path))
    require(all(re.fullmatch('[0-9a-fA-F]{8}', row) for row in rows), 'invalid hex '+str(path))
    values = [int(row,16) for row in rows]
    require(all(((word>>23)&255) != 255 for word in values), 'nonfinite word '+str(path))
    return values

def module(path, name):
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod

def observe():
    answer = {'time_unix':time.time(), 'policies':{}}
    for name in ('pingpong','reload'):
        out = ROOT/'reports/encoder/system'/name
        r = load(out/'status.json')
        progress = load(out/'cycle-progress.json')
        answer['policies'][name] = {'status':r.get('status'), 'status_sha256':digest(out/'status.json'),
                                    'progress':progress}
    with (HERE/'observations.jsonl').open('a',encoding='utf-8') as handle:
        handle.write(json.dumps(answer,ensure_ascii=False)+'\n')
    print(json.dumps(answer,ensure_ascii=True),flush=True)
    return answer

def audit_one(name, policy, freeze_sha):
    out = ROOT/'reports/encoder/system'/name
    status_sha = digest(out/'status.json')
    r = load(out/'status.json')
    require(r.get('status') == 'PASS' and r.get('exit_code') == 0, 'CPU not PASS/exit0 '+name)
    require(r.get('policy') == policy and r.get('layers') == 12 and r.get('neural_words') == 76032, 'CPU scope '+name)
    require(r.get('output_words') == (6336 if policy==1 else 76032), 'CPU writeback scope '+name)
    require(isinstance(r.get('pid'),int) and r['pid']>0 and re.fullmatch('[0-9a-f]{32}',r.get('run_id','')), 'run identity '+name)
    require(0 < r['started_unix'] <= r['completed_unix'] <= time.time(), 'timestamps '+name)
    require(r['input_sha256'].get('work/encoder_source_freeze.json') == freeze_sha, 'freeze binding '+name)
    counts = {key:hashes(r[key]) for key in ('source_sha256','compiled_source_sha256','input_sha256')}
    artifact_keys = {'binary_sha256':'obj/Vtb_e203_encoder','firmware_sha256':'firmware.elf',
                     'compile_log_sha256':'compile.log','build_key_sha256':'build.json',
                     'output_sha256':'cpu-output.hex','log_sha256':'simulation.log','neural_sha256':'neural-output.hex'}
    artifacts = {}
    for key, rel in artifact_keys.items():
        artifacts[rel] = digest(out/rel)
        require(artifacts[rel] == r[key], 'artifact changed '+name+'/'+rel)
    build = load(out/'build.json')
    require(build['sources'] == r['compiled_source_sha256'], 'compiled sources not build sources '+name)
    require(build['fp'] == digest(ROOT/'work/fp32_handoff.json') and build['e203'] == digest(ROOT/'work/e203_boot_handoff.json'), 'build dependency '+name)
    ref = ROOT/'reports/encoder/reference'
    case = (ref/'cases'/r['case']).resolve()
    require((ref/'cases').resolve() in case.parents, 'case outside reference')
    canonical = {str((case/'input.hex').relative_to(ROOT))}
    expected = []
    expected_text = ''
    for layer in range(12):
        path = case/f'layer_{layer:02d}/y.hex'
        expected += words(path,6336)
        expected_text += path.read_text(encoding='utf-8')
        canonical.add(str(path.relative_to(ROOT)))
    require((out/'input.hex').read_bytes() == (case/'input.hex').read_bytes(), 'staged input differs '+name)
    words(out/'input.hex',6336)
    require((out/'expected.hex').read_text(encoding='utf-8') == expected_text, 'staged expected differs '+name)
    require((out/'weights').resolve() == (ref/'weights').resolve(), 'staged weight target '+name)
    for layer in range(12):
        path = ref/f'weights/layer_{layer:02d}.hex'
        words(path,49792)
        require((out/f'weights/layer_{layer:02d}.hex').read_bytes() == path.read_bytes(), 'staged weights differ '+name)
        canonical.add(str(path.relative_to(ROOT)))
    require(canonical <= set(r['input_sha256']), 'canonical input bindings incomplete '+name)
    with tempfile.TemporaryDirectory(prefix='independent-encoder-elf-') as temp:
        image = Path(temp)/'derived.bin'
        proc = subprocess.run(['riscv64-unknown-elf-objcopy','-O','binary',str(out/'firmware.elf'),str(image)],capture_output=True,timeout=30)
        require(proc.returncode == 0, 'ELF readback objcopy '+name)
        firmware = image.read_bytes()
    require(firmware and (out/'firmware.bin').read_bytes() == firmware, 'ELF/bin differs '+name)
    require((out/'firmware.hex').read_text(encoding='utf-8') == ''.join(f'{byte:02x}\n' for byte in firmware), 'ELF/hex differs '+name)
    actual_command = [str(out/'obj/Vtb_e203_encoder'),f'+BYTES={len(firmware)}',f'+POLICY={policy}']
    require(r['command'] == actual_command, 'actual command differs '+name)
    commands = [json.loads(line) for line in (out/'commands.jsonl').read_text(encoding='utf-8').splitlines() if line.strip()]
    matching = [row for row in commands if row.get('command') == actual_command and Path(row.get('cwd','')).resolve()==out and r['started_unix'] <= row.get('time',0) <= r['completed_unix']]
    require(len(matching)==1, 'not exactly one actual command in interval '+name)
    log = (out/'simulation.log').read_text(encoding='utf-8')
    markers = re.findall(r'^E203_ENCODER_PASS[^\r\n]*',log,re.M)
    require(len(markers)==1 and markers[0] == r['summary'], 'completion marker '+name)
    stats = {key:int(value) for key,value in re.findall(r'(\w+)=(\d+)',markers[0])}
    require(stats['policy']==policy and stats['layers']==12 and stats['outputs']==r['output_words'] and stats['neural_words']==76032, 'summary scope '+name)
    require(stats['cpu_weight_words']==stats['host_words']==597504, 'full host/CPU weights '+name)
    require(stats['end_to_end_cycles']==stats['final_write_cycle']-stats['begin_cycle']+1>0, 'endpoint arithmetic '+name)
    loads = [tuple(map(int,row)) for row in re.findall(r'HOST_LAYER_LOAD layer=(\d+) words=(\d+) begin=(\d+) end=(\d+) cycles=(\d+)',log)]
    starts = [tuple(map(int,row)) for row in re.findall(r'CPU_ENCODER_START layer=(\d+) cycle=(\d+)',log)]
    require(len(loads)==len(starts)==12 and [x[0] for x in loads]==list(range(12)) and [x[0] for x in starts]==list(range(12)), 'host/start sequence '+name)
    partitions = {'initial':loads[0][2]-stats['begin_cycle'],'host':0,'ready_to_start':0,'start_to_next':0}
    require(partitions['initial']>=0, 'initial timing '+name)
    for layer, row in enumerate(loads):
        _,count,begin,end,elapsed = row
        start = starts[layer][1]
        next_boundary = loads[layer+1][2] if layer<11 else stats['final_write_cycle']+1
        require(count==elapsed==end-begin==49792 and begin<end<=start<next_boundary, 'timing sequence '+name)
        partitions['host'] += elapsed
        partitions['ready_to_start'] += start-end
        partitions['start_to_next'] += next_boundary-start
    require(sum(partitions.values())==stats['end_to_end_cycles'], 'disjoint sum '+name)
    neural = words(out/'neural-output.hex',76032)
    cpu = words(out/'cpu-output.hex',r['output_words'])
    require(neural == expected, 'independent neural word mismatch '+name)
    require(cpu == (expected[-6336:] if policy==1 else expected), 'independent CPU word mismatch '+name)
    cpu_tx = stats['shared_reads']+stats['shared_writes']
    traffic = {'cpu_reads':stats['shared_reads'],'cpu_writes':stats['shared_writes'],'cpu_transactions':cpu_tx,
               'cpu_word_bytes':cpu_tx*4,'host_parameter_writes':stats['host_words'],'host_ready_writes':12,'host_request_reads':12,
               'logical_combined_transactions':cpu_tx+stats['host_words']+24,'logical_combined_word_bytes':(cpu_tx+stats['host_words']+24)*4}
    for filename in ('input.hex','expected.hex','firmware.elf','firmware.bin','firmware.hex','commands.jsonl','status.json'):
        artifacts[filename] = digest(out/filename)
    require(digest(out/'status.json')==status_sha, 'status changed during audit '+name)
    audit = {'status':'PASS','case':r['case'],'policy':policy,'pid':r['pid'],'run_id':r['run_id'],
             'started_unix':r['started_unix'],'completed_unix':r['completed_unix'],'command':actual_command,
             'hash_counts':counts,'canonical_bound_files':len(canonical),'artifacts_sha256':artifacts,
             'firmware_bytes':len(firmware),'neural_compared_words':len(neural),'cpu_compared_words':len(cpu),
             'bit_mismatches':0,'nonfinite_words':0,'summary':r['summary'],'stats':stats,'partitions':partitions,'traffic':traffic,
             'build_compiler_options':build['compiler_options'],'normalized_compiled_sources':{key.replace('/'+name+'/hardfloat/','/<policy>/hardfloat/'):value for key,value in build['sources'].items()}}
    save(name+'.json',audit)
    return audit

def main():
    parser=argparse.ArgumentParser()
    parser.add_argument('--deadline',required=True)
    args=parser.parse_args()
    deadline=dt.datetime.fromisoformat(args.deadline).timestamp()
    while True:
        state=observe()
        statuses=[item['status'] for item in state['policies'].values()]
        if all(s=='PASS' for s in statuses):break
        if any(s not in ('PASS','RUNNING') for s in statuses):raise ValueError('unexpected CPU status '+repr(statuses))
        if time.time()>=deadline:
            save('result.json',{'status':'PENDING','observed':state,'reason':'30-minute bound expired'})
            return 2
        time.sleep(min(30,max(0,deadline-time.time())))
    freeze_path=ROOT/'work/encoder_source_freeze.json'
    freeze_sha=digest(freeze_path);freeze=load(freeze_path)
    require(freeze_sha=='4c11f4fa9c83592ee0e622e9c6a6ccf52a21eacef8d4a898e44aaf57cd27cc17', 'unexpected freeze release')
    require(len(freeze['source_sha256'])==192,'freeze count not 192')
    hashes(freeze['source_sha256'])
    ping=audit_one('pingpong',1,freeze_sha);reload=audit_one('reload',2,freeze_sha)
    require(ping['case']==reload['case'],'policies different cases')
    require(ping['artifacts_sha256']['input.hex']==reload['artifacts_sha256']['input.hex'], 'different actual inputs')
    require(ping['artifacts_sha256']['neural-output.hex']==reload['artifacts_sha256']['neural-output.hex'],'different neural outputs')
    require(ping['build_compiler_options']==reload['build_compiler_options'] and ping['normalized_compiled_sources']==reload['normalized_compiled_sources'],'different compiled configuration')
    gate=module(ROOT/'scripts/formal_seven_gate.py','independent_gate_readback')
    supplemental={}
    for name,policy in [('pingpong',1),('reload',2)]:
        verified,stats=gate.cpu_record(ROOT/'reports/encoder/system'/name/'status.json',policy)
        supplemental[name]={'result':'PASS','runtime_artifact_count':len(verified['verified_runtime_artifacts_sha256'])}
    reporter=module(ROOT/'scripts/encoder_report.py','independent_report_readback')
    require(digest(ROOT/'scripts/encoder_report.py')=='7c58df30fe5e456fc6722f5f95e4df43fb4867c0872f3b9054847758075db748','reporter changed from review snapshot')
    comparison={}
    for key in ('cpu_transactions','logical_combined_transactions','cpu_word_bytes','logical_combined_word_bytes'):
        a=ping['traffic'][key];b=reload['traffic'][key]
        comparison[key]={'pingpong':a,'reload':b,'saved':b-a,'fraction_of_reload':(b-a)/b if b else None}
    a=ping['stats']['end_to_end_cycles'];b=reload['stats']['end_to_end_cycles']
    comparison['end_to_end_cycles']={'pingpong':a,'reload':b,'saved':b-a,'fraction_of_reload':(b-a)/b}
    for name,record in [('pingpong',ping),('reload',reload)]:
        r=load(ROOT/'reports/encoder/system'/name/'status.json')
        t=reporter.cpu_timing(name,r,record['stats'])
        require(t['end_to_end_cycles']==sum(record['partitions'].values()),'reporter timing differs '+name)
    hashes(freeze['source_sha256'])
    require(digest(freeze_path)==freeze_sha,'freeze changed during audit')
    result={'status':'PASS','completed_utc':dt.datetime.now(dt.timezone.utc).isoformat(),'freeze_count':192,'freeze_sha256':freeze_sha,
            'same_input_and_all_neural_words':True,'neural_words_independently_compared':152064,'cpu_words_independently_compared':82368,
            'bit_mismatches':0,'nonfinite_words':0,'supplemental_gate':supplemental,'comparison':comparison,
            'review_source_sha256':digest(Path(__file__)),'gate_sha256':digest(ROOT/'scripts/formal_seven_gate.py'),
            'reporter_sha256':digest(ROOT/'scripts/encoder_report.py')}
    save('result.json',result)
    print(json.dumps(result,ensure_ascii=True),flush=True)
    return 0

if __name__=='__main__':
    try:
        sys.exit(main())
    except Exception as exc:
        save('failure.json',{'status':'FAIL','exception':type(exc).__name__,'message':str(exc),'time_unix':time.time()})
        raise
