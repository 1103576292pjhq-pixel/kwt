from pathlib import Path
import importlib.util
import json
import shutil
import subprocess
import sys
import tempfile
import unittest

HERE=Path(__file__).resolve().parents[1]
PROJECT=HERE.parents[2]
SOURCES=['rtl/kwt_shared_ram_icb.v','rtl/kwt_shared_sram_array.v','rtl/kwt_shared_sram.v']
CONTRACT=r'''`timescale 1ns/1ps
module RAMSP4096X16_rtl_top(output reg [15:0] Q,input CLK,CEN,
 input [15:0] WEN,input [11:0] A,input [15:0] D,input [2:0] EMA,
 input [1:0] EMAW,input GWEN,RET1N);
 reg [15:0] data[0:4095];integer k;
 always @(posedge CLK)if(!CEN)begin
  if(GWEN)Q<=#0.2 data[A];
  else for(k=0;k<16;k=k+1)if(!WEN[k])data[A][k]<=D[k];
 end
 // 测试替身主动令待机Q未知，避免无意依赖Q保持。
 always @(CEN)if(CEN)Q<=#0.1 16'hxxxx;
endmodule
'''


class SharedTests(unittest.TestCase):
    def run_tb(self,mutation=None,quick=True,corrupt=False):
        for rel in SOURCES:self.assertTrue((HERE/rel).is_file(),'Missing shared SRAM implementation: '+rel)
        if not shutil.which('iverilog'):self.skipTest('Requires WSL Icarus')
        with tempfile.TemporaryDirectory() as folder:
            tmp=Path(folder);files=[]
            for rel in SOURCES:
                text=(HERE/rel).read_text()
                if rel.endswith('kwt_shared_sram_array.v'):
                    if mutation=='bank_alias':text=text.replace('mem_req_addr[16:12]','{1\'b0,mem_req_addr[15:12]}')
                    if mutation=='half_swap':text=text.replace('{high_q[return_bank],low_q[return_bank]}','{low_q[return_bank],high_q[return_bank]}')
                    if mutation=='mask_lane':text=text.replace('{8{mem_req_wmask[0]}}','{8{mem_req_wmask[1]}}')
                    if mutation=='return_tag':text=text.replace('{high_q[return_bank],low_q[return_bank]}','{high_q[mem_req_addr[16:12]],low_q[mem_req_addr[16:12]]}')
                p=tmp/Path(rel).name;p.write_text(text);files.append(p)
            model=tmp/'contract.v';model.write_text(CONTRACT)
            exe=tmp/'run.vvp'
            built=subprocess.run(['iverilog','-g2012','-s','tb_shared_sram','-o',str(exe),
                                  *map(str,files),str(model),str(HERE/'tb/tb_shared_sram.v')],capture_output=True,text=True,timeout=30)
            self.assertEqual(built.returncode,0,built.stdout+built.stderr)
            args=['vvp',str(exe)]
            if quick:args.append('+quick')
            if corrupt:args.append('+corrupt_first')
            result=subprocess.run(args,capture_output=True,text=True,timeout=180)
            if mutation or corrupt:
                self.assertNotEqual(result.returncode,0,result.stdout)
                self.assertIn('FAIL SHARED_SRAM_READ',result.stdout)
            else:
                self.assertEqual(result.returncode,0,result.stdout+result.stderr)
                self.assertIn('PASS SHARED_SRAM words=131072 macros=64',result.stdout)
                if not quick:self.assertIn('full_sweeps=2 initialized_words=131072',result.stdout)
                # Icarus展开结果中应有恰好64个宏实例。
                self.assertEqual(exe.read_text().count('"RAMSP4096X16_rtl_top"'),64)
                print(result.stdout.strip())

    def test_full_capacity_and_protocol(self):self.run_tb(quick=False)
    def test_bank_alias_rejected(self):self.run_tb('bank_alias')
    def test_half_swap_rejected(self):self.run_tb('half_swap')
    def test_mask_lane_rejected(self):self.run_tb('mask_lane')
    def test_return_tag_rejected(self):self.run_tb('return_tag')
    def test_corrupt_golden_rejected(self):self.run_tb(corrupt=True)

    def test_production_accelerator_stays_separate(self):
        listing=(PROJECT/'rtl/kwt.f').read_text()
        self.assertNotIn('shared_sram',listing)
        self.assertEqual(sum(v.endswith('.v') for v in listing.splitlines()),15)


if __name__=='__main__':unittest.main()
