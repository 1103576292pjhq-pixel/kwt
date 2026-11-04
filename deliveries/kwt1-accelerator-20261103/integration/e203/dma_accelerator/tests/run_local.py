from pathlib import Path
import argparse,subprocess,re
HERE=Path(__file__).resolve().parents[1]
from support_tools import prepare_fixture,sha,save,audit_trace


def main():
    parser=argparse.ArgumentParser()
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--variant',type=int,default=0)
    parser.add_argument('--repeat',type=int,default=1)
    parser.add_argument('--stress',action='store_true')
    parser.add_argument('--mutation',action='store_true')
    args=parser.parse_args();out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
    data=prepare_fixture(out/'data')
    (out/'loader.v').write_bytes((HERE/'tests/support/real_loader.v').read_bytes())
    (out/'shared_model.v').write_bytes((HERE/'tests/support/shared_model.v').read_bytes())
    sources=[p for p in (HERE/'rtl').rglob('*.v')]
    before={str(p.relative_to(HERE)):sha(p) for p in sources+list((HERE/'rtl/include').glob('*.vh'))}
    if args.mutation:
        original=HERE/'rtl/dma/kwt_dma_controller.v'
        text=original.read_text(encoding='utf-8')
        assert text.count('assign wr_addr=yb+')==1
        mutant=out/'wrong_output_address.v'
        mutant.write_text(text.replace('assign wr_addr=yb+','assign wr_addr=yb+32\'d4+'),encoding='utf-8')
        sources=[mutant if p==original else p for p in sources]
    flags=[f'-Ptb_dma.FORWARD_INPUT={int(args.variant>=1)}',f'-Ptb_dma.FORWARD_RESULT={int(args.variant>=2)}',f'-Ptb_dma.RESULT_PRIORITY={int(args.variant>=3)}']
    (out/'tb_dma.v').write_bytes((HERE/'tests/tb_dma.v').read_bytes())
    command=['iverilog','-g2012','-DKWT_STORAGE_TEST_CONTRACT','-I',str(HERE/'rtl/include'),
             '-s','tb_dma',*flags,'-o',str(out/'sim.vvp'),*map(str,sources),
             str(HERE/'tests/support/sram_contract_models.v'),str(out/'shared_model.v'),
             str(out/'loader.v'),str(out/'tb_dma.v')]
    proc=subprocess.run(command,capture_output=True,text=True)
    (out/'compile.log').write_text(proc.stdout+proc.stderr);proc.check_returncode()
    with (out/'run.log').open('w') as log:
        proc=subprocess.run(['vvp',str(out/'sim.vvp'),'+real_data=data','+repeat_tasks='+str(args.repeat),'+stress='+str(int(args.stress))],cwd=out,stdout=log,stderr=log,timeout=1200)
    text=(out/'run.log').read_text();print(text,flush=True)
    if args.mutation:
        assert proc.returncode!=0 and 'DMA wrong/duplicate result' in text,text
        save(out/'report.json',dict(status='PASS_NEGATIVE_ADDRESS_CORRUPTION_CAUGHT',source_sha256=before))
        return
    proc.check_returncode()
    if 'PASS DMA_SYSTEM' not in text:raise RuntimeError('Missing final PASS')
    metrics=[]
    for line in re.findall(r'^DMA_METRIC (.+)$',text,re.M):
        values={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',line)}
        assert values['full_cycles']==values['load_cycles']+values['init_config_cycles']+values['dma_to_writeback_cycles']
        values['target_150mhz_ms']=values['full_cycles']/150000
        values['target_150mhz_tasks_s']=150000000/values['full_cycles']
        metrics.append(values)
    assert len(metrics)==args.repeat
    for name,want in before.items():assert sha(HERE/name)==want
    profiles=[{k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',line)} for line in re.findall(r'^DMA_PROFILE (.+)$',text,re.M)]
    save(out/'report.json',dict(status='PASS_LOCAL_DMA_CONTRACT',variant=args.variant,metrics=metrics,profiles=profiles,
       actual_e203_executed=False,official_sram=False,source_sha256=before,scope='Actual DMA+engine+arbiter+shared RTL; contract SRAM models, TB host configuration and initialization',
       sample=data['sample'],data_sha256=data['files_sha256']))

if __name__=='__main__':main()
