#!/usr/bin/env python3
"""Standalone official RAMSP4096X16 functional smoke; upload this file only."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import subprocess


TB = r'''`timescale 1ns/1ps
`default_nettype none
// 单颗官方wrapper；不读取宏内部数组，不假定上电内容、待机Q或写穿行为。
module tb_sram4096_smoke;
    reg clk=0; always #10 clk=~clk;
    reg cen=1,gwen=1,ret1n=1;
    reg [15:0] wen=16'hffff,d=0;
    reg [11:0] a=0;
    reg [2:0] ema=2; reg [1:0] emaw=0;
    wire [15:0] q;
    RAMSP4096X16_rtl_top dut(.Q(q),.CLK(clk),.CEN(cen),.WEN(wen),
        .A(a),.D(d),.EMA(ema),.EMAW(emaw),.GWEN(gwen),.RET1N(ret1n));

    reg [15:0] golden[0:4095];
    integer reads=0,writes=0,masked_writes=0,zero_mask_writes=0,disabled_writes=0;
    integer config_ema=2,config_emaw=0,corrupt_first=0;
    integer address,phase,bitnum,location,j;
    integer boundaries[0:5];
    reg [15:0] value,mask;

    function [15:0] pattern;
        input integer addr,kind;
        begin
            pattern=(addr*37)^16'h9a53;
            if(kind!=0)pattern=~pattern;
        end
    endfunction

    // 每次都在下降沿后1ns改变控制，离上升沿9ns；采样在上升沿后8ns。
    // 20ns仅为功能测试时钟，不是150MHz测量或建立/保持时序验收。
    task access_cycle;
        input chip_disabled,read_mode;
        input [11:0] addr;
        input [15:0] data,write_mask;
        begin
            @(negedge clk);#1;
            cen=chip_disabled;gwen=read_mode;a=addr;d=data;wen=write_mask;
            @(posedge clk);#8;
        end
    endtask

    task write_word;
        input [11:0] addr;
        input [15:0] data,write_mask;
        begin
            access_cycle(0,0,addr,data,write_mask);
            // 这是待验证的低有效逐位写合同，由请求更新软件期望值。
            golden[addr]=(golden[addr]&write_mask)|(data&~write_mask);
            writes=writes+1;
            if(write_mask==16'hffff)zero_mask_writes=zero_mask_writes+1;
            else if(write_mask!=0)masked_writes=masked_writes+1;
        end
    endtask

    task read_word;
        input [11:0] addr;
        reg [15:0] expected;
        begin
            access_cycle(0,1,addr,0,16'hffff);
            expected=golden[addr];
            if(corrupt_first && reads==0)expected=expected^16'h0001;
            if(q!==expected)begin
                $display("FAIL SRAM4096_READ addr=%0d actual=%h expected=%h read_index=%0d",addr,q,expected,reads);
                $fatal(1,"Official wrapper read mismatch or X");
            end
            reads=reads+1;
        end
    endtask

    initial begin
        if($value$plusargs("ema=%d",config_ema))begin end
        if($value$plusargs("emaw=%d",config_emaw))begin end
        if(config_ema<0||config_ema>7||config_emaw<0||config_emaw>3)
            $fatal(1,"Invalid EMA/EMAW");
        ema=config_ema;emaw=config_emaw;
        corrupt_first=$test$plusargs("corrupt_first");
        for(j=0;j<4;j=j+1)access_cycle(1,1,0,0,16'hffff);

        // 两次全容量填充和回读：模式与地址一一对应，检出高位地址别名。
        for(phase=0;phase<2;phase=phase+1)begin
            for(address=0;address<4096;address=address+1)begin
                // 全位写不依赖之前未知内容；软件期望直接初始化。
                access_cycle(0,0,address,pattern(address,phase),16'h0000);
                golden[address]=pattern(address,phase);writes=writes+1;
            end
            for(address=0;address<4096;address=address+1)read_word(address);
        end

        // 逐位掩码：每次只改变一个bit；全1掩码应禁止全部位写入。
        for(bitnum=0;bitnum<16;bitnum=bitnum+1)begin
            location=(bitnum*251+17)%4096;
            value=~golden[location];mask=~(16'h0001<<bitnum);
            write_word(location,value,mask);read_word(location);
            write_word(location,~golden[location],16'hffff);read_word(location);
        end
        // 后续32位共享封装需要的高低字节掩码。
        write_word(2047,~golden[2047],16'hff00);read_word(2047);
        write_word(2048,~golden[2048],16'h00ff);read_word(2048);

        // CEN禁用的写不得改变内容，不对禁用期间Q作假设。
        access_cycle(1,0,0,~golden[0],16'h0000);disabled_writes=disabled_writes+1;read_word(0);
        access_cycle(1,0,4095,~golden[4095],16'h0000);disabled_writes=disabled_writes+1;read_word(4095);

        boundaries[0]=0;boundaries[1]=1;boundaries[2]=2047;
        boundaries[3]=2048;boundaries[4]=4094;boundaries[5]=4095;
        for(j=0;j<6;j=j+1)begin
            write_word(boundaries[j],16'h0000,0);read_word(boundaries[j]);
            write_word(boundaries[j],16'hffff,0);read_word(boundaries[j]);
        end
        // 掩码和禁用访问后重新检查全部存储，捕捉旁路误写。
        for(address=0;address<4096;address=address+1)read_word(address);
        if(reads!=12336||writes!=8238||masked_writes!=18||zero_mask_writes!=16||disabled_writes!=2)
            $fatal(1,"Coverage counts incomplete");
        $display("PASS SRAM4096_SMOKE words=4096 reads=%0d writes=%0d masked_writes=%0d zero_mask_writes=%0d disabled_writes=%0d ema=%0d emaw=%0d period_ns=20",
                 reads,writes,masked_writes,zero_mask_writes,disabled_writes,config_ema,config_emaw);
        $finish;
    end
    initial begin #1000000; $fatal(1,"SRAM4096 smoke watchdog");end
endmodule
`default_nettype wire
'''


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def save(path, value):
    path.write_text(json.dumps(value, ensure_ascii=False, indent=2)+'\n', encoding='utf-8')


def audit_summary(text, ema, emaw):
    matches=re.findall(r'^PASS SRAM4096_SMOKE (.*)$',text,re.M)
    if len(matches)!=1:
        raise ValueError('Expected exactly one complete SRAM4096 pass summary')
    values={k:int(v) for k,v in re.findall(r'(\w+)=(\d+)',matches[0])}
    expected=dict(words=4096,reads=12336,writes=8238,masked_writes=18,zero_mask_writes=16,
                  disabled_writes=2,ema=ema,emaw=emaw,period_ns=20)
    if values!=expected:
        raise ValueError('Wrong coverage/configuration: '+str(values))
    return values


def audit_negative(text,returncode):
    # VCS2020可在$fatal后返回0；只能接受明确的首项故意改错，不能只看退出码。
    found=re.findall(r'^FAIL SRAM4096_READ addr=0 actual=([0-9a-fA-F]{4}) expected=([0-9a-fA-F]{4}) read_index=0$',text,re.M)
    if (returncode not in (0,1) or len(found)!=1 or 'PASS SRAM4096_SMOKE' in text or
        tuple(int(v,16) for v in found[0])!=(0x9a53,0x9a52)):
        raise ValueError('Negative control did not produce the exact injected first-read failure')


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output',type=Path,default=Path('verification/sram4096_smoke_01'))
    parser.add_argument('--sram-root',type=Path,default=Path('/storage1/admin_public_dir/SRAM_Lib_2025'))
    parser.add_argument('--ema',type=int,choices=range(8),default=2)
    parser.add_argument('--emaw',type=int,choices=range(4),default=0)
    args=parser.parse_args()
    root=Path(__file__).resolve().parent
    out=(root/args.output).resolve()
    if root not in out.parents:
        parser.error('Output must be a new directory inside the script directory')
    if out.exists():
        parser.error('Output already exists; use a new number; no files overwritten')
    out.mkdir(parents=True,exist_ok=False)
    models=[args.sram_root/'RAMSP4096X16/verilog'/name for name in
            ('RAMSP4096X16_rtl.v','RAMSP4096X16.v')]
    report=dict(status='RUNNING',scope='SINGLE_OFFICIAL_SRAM_FUNCTIONAL_ONLY',commands=[],
                mode='ARM_UD_MODEL fast functional',clock_period_ns=20,
                ema=args.ema,emaw=args.emaw,configuration_status='CANDIDATE_UNTIL_RUN_PASSES',
                runner_sha256=digest(Path(__file__)),official_models=[],
                exclusions=['512KiB bank/width assembly','E203/ICB integration','150MHz STA or setup/hold closure',
                            'area/power/energy','retention/power cycling'])
    save(out/'report.json',report)
    try:
        missing=[str(p) for p in models if not p.is_file()]
        if missing:
            report.update(status='BLOCKED_MISSING_OFFICIAL_MODELS',missing=missing)
            save(out/'report.json',report)
            raise FileNotFoundError('Official models missing: '+', '.join(missing))
        report['official_models']=[dict(path=str(p),sha256=digest(p)) for p in models]
        tb=out/'tb_sram4096_smoke.v';tb.write_text(TB,encoding='utf-8')
        report['tb_sha256']=digest(tb)
        def run(name,argv,negative=False):
            with (out/(name+'.log')).open('w',encoding='utf-8') as log:
                result=subprocess.run(list(map(str,argv)),cwd=out,stdout=log,stderr=subprocess.STDOUT,timeout=600)
            report['commands'].append(dict(name=name,argv=list(map(str,argv)),returncode=result.returncode))
            save(out/'report.json',report)
            text=(out/(name+'.log')).read_text(encoding='utf-8',errors='replace')
            if (not negative and result.returncode!=0) or (negative and result.returncode not in (0,1)):
                raise RuntimeError(name+' unexpected exit status; see '+str(out/(name+'.log')))
            return text
        print('COMPILING_OFFICIAL_SRAM4096 EMA=%d EMAW=%d; functional20ns, not150MHz STA'%(args.ema,args.emaw),flush=True)
        run('compile',['vcs','-full64','-sverilog','-timescale=1ns/1ps',
                       '+define+ARM_UD_MODEL','+incdir+'+str(models[0].parent),
                       '-top','tb_sram4096_smoke','-Mdir='+str(out/'csrc'),'-o',out/'simv',tb,*models])
        print('COMPILE_PASS; running full4096-address read/write checks',flush=True)
        plusargs=['+ema='+str(args.ema),'+emaw='+str(args.emaw)]
        positive=run('run',[out/'simv',*plusargs])
        report['counts']=audit_summary(positive,args.ema,args.emaw)
        negative=run('negative-golden',[out/'simv',*plusargs,'+corrupt_first'],negative=True)
        audit_negative(negative,report['commands'][-1]['returncode'])
        if digest(Path(__file__))!=report['runner_sha256'] or digest(tb)!=report['tb_sha256']:
            raise ValueError('Verifier changed while running')
        for p,info in zip(models,report['official_models']):
            if digest(p)!=info['sha256']:raise ValueError('Official model changed while running')
        report.update(status='PASS_SINGLE_SRAM4096_OFFICIAL_FUNCTIONAL',official_macro_functional_verified=True,
                      negative_golden_caught=True,configuration_status='FUNCTIONAL_PASS_AT_RECORDED_TEST_CONDITIONS',
                      log_sha256={name:digest(out/name) for name in ('compile.log','run.log','negative-golden.log')})
        save(out/'report.json',report)
        print(positive[positive.index('PASS SRAM4096_SMOKE'):].splitlines()[0],flush=True)
        print('PASS SRAM4096_OFFICIAL negative_golden_caught=1; not sharedRAM/CPU/STA acceptance',flush=True)
        print('REPORT',out/'report.json',flush=True)
        return 0
    except Exception as error:
        if report['status']=='RUNNING':report['status']='FAIL_SINGLE_SRAM4096_OFFICIAL'
        report['error']=str(error);save(out/'report.json',report)
        print(report['status']+': '+str(error),flush=True)
        print('REPORT',out/'report.json',flush=True)
        return 1


if __name__=='__main__':raise SystemExit(main())
