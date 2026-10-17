from pathlib import Path
import json,types,os,sys
sys.dont_write_bytecode=True
ROOT=Path('/mnt/d/github/kwt');sys.path.insert(0,str(ROOT))
from scripts.revd_offline_common import sha,put,utc
out=Path(__file__).resolve().parent
sources=['scripts/package_revd_candidate.py','scripts/revd_offline_reproduce.py','scripts/revd_offline_package_check.py','scripts/revd_offline_final_regression.py'];before={p:sha(ROOT/p) for p in sources}
def load(p,n):
 b=(ROOT/p).read_bytes();(out/(n+'.source.txt')).write_bytes(b);m=types.ModuleType(n);m.__file__=str(ROOT/p);exec(compile(b,str(ROOT/p),'exec'),m.__dict__);return m
pkg=load(sources[0],'publisher');rep=load(sources[1],'reproducer');tests=[]
for scenario,extra in [('empty_command_proof',False),('unmanifested_code_after_proof',True)]:
 scratch=out/scenario;stage=scratch/'stage';stage.mkdir(parents=True);(stage/'valid.txt').write_text('known bytes\n');put(stage/'MANIFEST.json',{'files':{'valid.txt':sha(stage/'valid.txt')},'file_count':1})
 if extra:(stage/'scripts').mkdir();(stage/'scripts/unlisted.py').write_text('print("unmanifested")\n')
 proof={'status':'PASS','package_manifest_sha256':sha(stage/'MANIFEST.json'),'suites':['manifest','smoke','numeric'],'commands':[]};put(scratch/'proof.json',proof);pkg.ROOT=scratch
 try:pkg.publish(stage,scratch/'proof.json')
 except ValueError as e:r={'name':scenario,'expected':'REJECT','actual':'REJECT','passed':('unlisted' if extra else 'exactly one') in str(e),'error':str(e)}
 except Exception as e:r={'name':scenario,'expected':'REJECT','actual':'UNEXPECTED_EXCEPTION','passed':False,'error':repr(e)}
 else:r={'name':scenario,'expected':'REJECT','actual':'ACCEPT','passed':False}
 tests.append(r)
for scenario,files,extra,expected in [('nominal',{'valid.txt':None},False,'ACCEPT'),('semantic_alias',{'valid.txt':None,'aliases/../valid.txt':None},False,'REJECT'),('casefold_alias',{'valid.txt':None,'VALID.txt':None},False,'REJECT'),('backslash',{'valid.txt':None,'aliases\\..\\valid.txt':None},False,'REJECT'),('parent_escape',{'../valid.txt':None},False,'REJECT'),('unlisted_code',{'valid.txt':None},True,'REJECT')]:
 fixture=out/'manifest_fixture'/scenario;fixture.mkdir(parents=True);(fixture/'aliases').mkdir();(fixture/'valid.txt').write_text('known bytes\n');digest=sha(fixture/'valid.txt')
 if extra:(fixture/'extra.py').write_text('x=1\n')
 put(fixture/'MANIFEST.json',{'files':{p:digest for p in files},'file_count':len(files)})
 try:result=rep.manifest_check(fixture,allow_runtime=False)
 except ValueError as e:r={'name':scenario,'expected':expected,'actual':'REJECT','passed':expected=='REJECT','error':str(e)}
 except Exception as e:r={'name':scenario,'expected':expected,'actual':'UNEXPECTED_EXCEPTION','passed':False,'error':repr(e)}
 else:r={'name':scenario,'expected':expected,'actual':'ACCEPT','passed':expected=='ACCEPT','result':result}
 tests.append(r)
changed=[p for p,d in before.items() if sha(ROOT/p)!=d];result={'status':'PASS' if all(t['passed'] for t in tests) and not changed else 'FAIL','pid':os.getpid(),'finished_utc':utc(),'source_sha256':before,'changed_sources':changed,'tests':tests,'count':len(tests),'scope':'Independent isolated current-source publish/manifest red-to-green probes; actual final stage positive proof pending.','parent_accepted':False,'official_contest_acceptance':False};put(out/'summary.json',result);print(json.dumps(result),flush=True)
raise SystemExit(0 if result['status']=='PASS' else 1)
