"""Preserve compilable behavioral RED evidence against independent tests."""
import json
import os
from pathlib import Path
import subprocess
import sys

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from numeric.encoder.contracts import sha,json_write


def main():
    report=ROOT/'reports/encoder/reference/tests/mutations'
    report.mkdir(parents=True,exist_ok=True)
    source=(ROOT/'numeric/encoder/encoder_ref.c').read_text(encoding='utf-8')
    replacements={
        'exp_range_sign':('float scaled=x*1.4426950408889634f;','float scaled=-x*1.4426950408889634f;'),
        'wrong_residual_base':('s[KWT_R2][k]=s[KWT_N1][k]+s[KWT_FFN2][k];','s[KWT_R2][k]=x[k]+s[KWT_FFN2][k];'),
        'unfused_dot':('acc=fmaf(x[i*in+k],w[k*out+j],acc);','acc=x[i*in+k]*w[k*out+j]+acc;'),
        'variance_sample_divisor':('float variance=varsum*inv_d;','float variance=varsum/(float)(d-1);')}
    records=[]
    for name,(before,after) in replacements.items():
        if source.count(before)!=1:raise ValueError('ambiguous mutation '+name)
        path=report/(name+'.c');path.write_text(source.replace(before,after),encoding='utf-8')
        library=report/(name+'.so')
        command=['gcc','-std=c11','-O2','-ffp-contract=off','-fno-fast-math','-Wall','-Wextra','-Werror',
                 '-fPIC','-shared','-I',str(ROOT/'numeric/encoder'),str(path),'-lm','-o',str(library)]
        compiled=subprocess.run(command,capture_output=True,text=True)
        (report/(name+'.compile.log')).write_text(compiled.stdout+compiled.stderr,encoding='utf-8')
        compiled.check_returncode()
        env=os.environ.copy();env['KWT_ENCODER_REFERENCE_SOURCE']=str(path)
        tested=subprocess.run([sys.executable,'-m','unittest','discover','-s',str(ROOT/'tests/encoder_reference'),'-p','test_reference.py','-v'],
                              capture_output=True,text=True,env=env)
        (report/(name+'.test.log')).write_text(tested.stdout+tested.stderr,encoding='utf-8')
        if tested.returncode==0 or 'FAILED (failures=' not in tested.stderr:
            raise ValueError('mutation was not killed by a functional assertion: '+name)
        records.append({'name':name,'source_sha256':sha(path),'compile_exit_code':compiled.returncode,
                        'test_exit_code':tested.returncode,'assertion_failure':True})
    json_write(report/'status.json',{'status':'PASS','mutations':records,
                                    'production_source_sha256':sha(ROOT/'numeric/encoder/encoder_ref.c')})
    print('All {} compilable mutations detected'.format(len(records)))

if __name__=='__main__':main()
