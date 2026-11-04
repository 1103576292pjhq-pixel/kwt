"""Three different real tasks, reset invalidation and bus scrub in one simulation."""
from pathlib import Path
import argparse, hashlib, json, re, subprocess, sys

HERE=Path(__file__).resolve().parents[1]
ROOT=HERE.parents[2]
sys.path.insert(0,str(ROOT/'integration/e203/real_shared_suite'))
from suite_tools import prepare_suite

def main():
    parser=argparse.ArgumentParser()
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--skip-reset',action='store_true')
    args=parser.parse_args()
    out=args.output.resolve();out.mkdir(parents=True,exist_ok=False)
    fixtures=ROOT/'verification/real12-20261102-02/fixtures'
    identity=json.loads((ROOT/'integration/e203/real_shared_suite/fixture-identity.json').read_text())
    data=prepare_suite(fixtures,out/'data',identity)[:3]
    assert len({hashlib.sha256((out/f'data/case{i}/w.hex').read_bytes()).hexdigest() for i in range(1,4)})==3
    tb=(HERE/'tests/tb_dma.v').read_text()
    start=tb.index(' kwt_real_loader loader(');end=tb.index(' reg [31:0] gold',start)
    tb=tb[:start]+" assign load_mode=0;assign load_done=1;\n"+tb[end:]
    tb=tb.replace("cfg('h24,0,2,0,value)","cfg('h24,0,task_number,0,value)")
    start=tb.index(' initial begin\n   i=$value$plusargs')
    tb=tb[:start]+r'''
 integer scrub_words,clear_start,trace_fd,neg_reset;
 reg [4095:0] data_path;
 task scrub(input [31:0] base,input integer count);
 begin
   for(i=0;i<count;i=i+1)ram(base+4*i,0,0,value);
   for(i=0;i<count;i=i+1)begin
     ram(base+4*i,1,0,value);
     if(value!==0)$fatal(1,"CLEAR_READBACK_FAIL address=%h",base+4*i);
   end
   scrub_words=scrub_words+count;
 end endtask
 initial begin
   if(!$value$plusargs("real_data=%s",folder))$fatal(1,"Missing data");
   neg_reset=0;i=$value$plusargs("skip_reset=%d",neg_reset);
   trace_fd=$fopen("actual.txt","w");
   for(task_number=0;task_number<3;task_number=task_number+1)begin
     scenario=1;clear_start=tick;
     @(negedge clk);
     if(neg_reset==0 || task_number==0)rst_n=0;
     repeat(4)@(negedge clk);
     rst_n=1;repeat(2)@(negedge clk);
     cfg(4,1,0,0,value);
     if(value!==0)$fatal(1,"CLEAR_STATE_FAIL status=%h task=%0d",value,task_number);
     if(dut.u_accelerator.u_engine.u_load.session_valid!==0 ||
        dut.u_accelerator.u_engine.u_load.x_count!==0 ||
        dut.u_accelerator.u_engine.u_load.w_count!==0 ||
        dut.u_accelerator.u_engine.u_load.bias_count!==0 ||
        dut.u_accelerator.u_engine.u_results.session_valid!==0)
        $fatal(1,"CLEAR_CACHE_VALID_FAIL");
     for(i=0;i<2;i=i+1)begin
       if(dut.u_accelerator.u_engine.u_load.slot_state_reg[i]!==0 ||
          dut.u_accelerator.u_engine.u_results.state[i]!==0)$fatal(1,"CLEAR_SLOT_FAIL");
     end
     scrub_words=0;
     scrub(32'ha0000000,6336);scrub(32'ha0008000,16384);
     scrub(32'ha0018000,256);scrub(32'ha0020000,25344);
     $display("CLEAR_PASS task=%0d words=%0d cycles=%0d cache_invalidation=1 internal_sram_zeroed=0",task_number+1,scrub_words,tick-clear_start);
     $sformat(data_path,"%0s/case%0d/x.hex",folder,task_number+1);$readmemh(data_path,x);
     $sformat(data_path,"%0s/case%0d/w.hex",folder,task_number+1);$readmemh(data_path,w);
     $sformat(data_path,"%0s/case%0d/b.hex",folder,task_number+1);$readmemh(data_path,bias);
     $sformat(data_path,"%0s/case%0d/gold.hex",folder,task_number+1);$readmemh(data_path,gold);
     start_tick=-1;end_tick=-1;loads=0;poisons=0;writes=0;written=0;
     scenario=0;
     for(i=0;i<6336;i=i+1)ram(32'ha0000000+4*i,0,x[i],value);
     for(i=0;i<16384;i=i+1)ram(32'ha0008000+4*i,0,w[i],value);
     for(i=0;i<256;i=i+1)ram(32'ha0018000+4*i,0,bias[i],value);
     for(i=0;i<25344;i=i+1)ram(32'ha0020000+4*i,0,32'hdeadbeef,value);
     ram(32'ha001fffc,0,32'h13579bdf,value);ram(32'ha0038c00,0,32'h2468ace0,value);
     setup(32'hd0000100+task_number);start_dma_tick=tick;cfg(8,0,1,0,value);
     wait_finish;
     cfg(4,1,0,0,value);if(value!==2)$fatal(1,"Task status error");
     if(writes!=25344 || loads!=22976 || poisons!=25344)$fatal(1,"Task ledger incomplete");
     cfg('h34,1,0,0,value);if(value!==400)$fatal(1,"Block count");
     for(i=0;i<25344;i=i+1)begin
       ram(32'ha0020000+4*i,1,0,value);
       if(value!==gold[i])$fatal(1,"Wrong result task=%0d index=%0d",task_number+1,i);
       $fdisplay(trace_fd,"Y %0d %0d %08h",task_number+1,i,value);
     end
     ram(32'ha001fffc,1,0,value);if(value!==32'h13579bdf)$fatal(1,"Low guard");
     ram(32'ha0038c00,1,0,value);if(value!==32'h2468ace0)$fatal(1,"High guard");
     $display("TASK_PASS case=%0d layer=%0d blocks=400 outputs=25344 cycles=%0d",task_number+1,task_number,end_tick-start_tick);
   end
   $fclose(trace_fd);$display("PASS_THREE_CLEAR tasks=3 outputs=76032");$finish;
 end
endmodule
'''
    (out/'tb.v').write_text(tb)
    sources=list((HERE/'rtl').rglob('*.v'))
    hashes={str(p.relative_to(HERE)):hashlib.sha256(p.read_bytes()).hexdigest() for p in sources}
    cmd=['iverilog','-g2012','-DKWT_STORAGE_TEST_CONTRACT','-I',str(HERE/'rtl/include'),'-s','tb_dma',
         '-Ptb_dma.FORWARD_INPUT=1','-Ptb_dma.FORWARD_RESULT=1','-o',str(out/'sim.vvp'),
         *map(str,sources),str(HERE/'tests/support/sram_contract_models.v'),str(HERE/'tests/support/shared_model.v'),str(out/'tb.v')]
    proc=subprocess.run(cmd,capture_output=True,text=True)
    (out/'compile.log').write_text(proc.stdout+proc.stderr);proc.check_returncode()
    with (out/'run.log').open('w') as log:
        proc=subprocess.run(['vvp',str(out/'sim.vvp'),'+real_data=data','+skip_reset='+str(int(args.skip_reset))],cwd=out,stdout=log,stderr=log,timeout=1800)
    log=(out/'run.log').read_text();print(log,flush=True)
    if args.skip_reset:
        assert proc.returncode!=0 and 'CLEAR_STATE_FAIL' in log
        report=dict(status='PASS_NEGATIVE_MISSING_RESET_DETECTED',actual_e203=False,official_sram=False)
    else:
        proc.check_returncode();assert 'PASS_THREE_CLEAR tasks=3 outputs=76032' in log
        from suite_tools import audit_suite
        audit=audit_suite(out/'actual.txt',data,fixtures)
        assert len(re.findall(r'^CLEAR_PASS ',log,re.M))==3
        report=dict(status='PASS_LOCAL_THREE_CLEAR',actual_e203=False,official_sram=False,
                    audit=audit,source_sha256=hashes,clear='Shared X/W/bias/Y bus zero-write and full zero-readback; internal cache metadata reset, not SRAM bit scrub',
                    metrics=[dict(case=int(a),layer=int(b),cycles=int(c)) for a,b,c in re.findall(r'TASK_PASS case=(\d+) layer=(\d+) blocks=400 outputs=25344 cycles=(\d+)',log)])
    (out/'report.json').write_text(json.dumps(report,indent=2,ensure_ascii=False)+'\n')

if __name__=='__main__':main()
