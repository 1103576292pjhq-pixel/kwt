from pathlib import Path
import importlib.util
import json
import shutil
import subprocess
import sys
import tempfile
import unittest

SCRIPT = Path(__file__).resolve().parents[1] / 'run_sram4096_smoke.py'

# 独立测试替身：不属于官方宏，不作STA或官方功能通过依据。
MODEL = r'''`timescale 1ns/1ps
module RAMSP4096X16_rtl_top(output reg [15:0] Q,
 input CLK,CEN,input [15:0] WEN,input [11:0] A,input [15:0] D,
 input [2:0] EMA,input [1:0] EMAW,input GWEN,RET1N);
 reg [15:0] cells[0:4095]; integer bitnum;
 wire [11:0] selected_addr=A;
 always @(posedge CLK) if (!CEN) begin
  if (GWEN) Q <= #0.2 cells[selected_addr];
  else for(bitnum=0;bitnum<16;bitnum=bitnum+1)
   if(!WEN[bitnum]) cells[selected_addr][bitnum] <= D[bitnum];
 end
endmodule
'''


class SmokeTests(unittest.TestCase):
    def test_negative_vcs_zero_requires_exact_injected_failure(self):
        runner=self.load_runner()
        check=getattr(runner,'audit_negative',None)
        self.assertTrue(callable(check),'VCS zero-exit negative-result audit is not implemented')
        text='FAIL SRAM4096_READ addr=0 actual=9a53 expected=9a52 read_index=0\nFatal: deliberate golden mismatch\n'
        for code in [0,1]:check(text,code)
        for bad,code in [('Fatal: unrelated failure\n',0),(text+'PASS SRAM4096_SMOKE\n',0),
                         (text.replace('9a52','9a53'),0),(text.replace('9a53','xxxx'),1),(text,-11)]:
            with self.assertRaises(ValueError):check(bad,code)

    def load_runner(self):
        self.assertTrue(SCRIPT.is_file(), 'Single-macro verifier is not implemented')
        spec=importlib.util.spec_from_file_location('sram4096_smoke_runner', SCRIPT)
        module=importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)
        return module

    def test_missing_models_are_blocked_not_passed(self):
        self.load_runner()
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder); script=root/SCRIPT.name
            shutil.copy2(SCRIPT,script)
            proc=subprocess.run([sys.executable,'-B',str(script),'--sram-root',str(root/'missing'),
                                 '--output','run-01'],capture_output=True,text=True)
            self.assertNotEqual(proc.returncode,0)
            report=json.loads((root/'run-01/report.json').read_text())
            self.assertEqual(report['status'],'BLOCKED_MISSING_OFFICIAL_MODELS')
            self.assertEqual(report['commands'],[])
            self.assertNotIn('PASS SRAM4096_OFFICIAL',proc.stdout)

    def test_existing_output_is_preserved(self):
        self.load_runner()
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder); script=root/SCRIPT.name
            shutil.copy2(SCRIPT,script)
            out=root/'run-01';out.mkdir();(out/'report.json').write_text('KEEP')
            proc=subprocess.run([sys.executable,'-B',str(script),'--output','run-01'],capture_output=True,text=True)
            self.assertNotEqual(proc.returncode,0)
            self.assertEqual((out/'report.json').read_text(),'KEEP')
            self.assertNotIn('PASS SRAM4096_OFFICIAL',proc.stdout)

    def test_incomplete_duplicate_and_wrong_config_summaries_are_rejected(self):
        runner=self.load_runner()
        good='PASS SRAM4096_SMOKE words=4096 reads=12336 writes=8238 masked_writes=18 zero_mask_writes=16 disabled_writes=2 ema=2 emaw=0 period_ns=20\n'
        self.assertEqual(runner.audit_summary(good,2,0)['reads'],12336)
        for bad in [good.replace('reads=12336','reads=1'),good+good,good.replace('ema=2','ema=0'),'PASS\n']:
            with self.assertRaises(ValueError):runner.audit_summary(bad,2,0)

    def run_tb(self, mutation=None, corrupt=False):
        runner=self.load_runner()
        if not shutil.which('iverilog') or not shutil.which('vvp'):
            self.skipTest('Requires local Icarus; official macro remains server-only')
        with tempfile.TemporaryDirectory() as folder:
            root=Path(folder)
            model=MODEL
            if mutation=='address_alias':model=model.replace('selected_addr=A;','selected_addr={1\'b0,A[10:0]};')
            elif mutation=='mask_ignored':model=model.replace('if(!WEN[bitnum])','if(1\'b1)')
            elif mutation=='cen_ignored':model=model.replace('if (!CEN)','if (1\'b1)')
            (root/'tb.v').write_text(runner.TB,encoding='utf-8')
            (root/'model.v').write_text(model,encoding='utf-8')
            cp=subprocess.run(['iverilog','-g2012','-s','tb_sram4096_smoke','-o',str(root/'sim.vvp'),
                               str(root/'tb.v'),str(root/'model.v')],capture_output=True,text=True,timeout=30)
            self.assertEqual(cp.returncode,0,cp.stdout+cp.stderr)
            args=['vvp',str(root/'sim.vvp'),'+ema=2','+emaw=0']
            if corrupt:args.append('+corrupt_first')
            result=subprocess.run(args,capture_output=True,text=True,timeout=30)
            if mutation or corrupt:
                self.assertNotEqual(result.returncode,0,result.stdout)
                self.assertIn('FAIL SRAM4096_READ',result.stdout)
                self.assertNotIn('PASS SRAM4096_SMOKE',result.stdout)
            else:
                self.assertEqual(result.returncode,0,result.stdout+result.stderr)
                runner.audit_summary(result.stdout,2,0)

    def test_tb_passes_independent_contract_model(self):self.run_tb()
    def test_tb_rejects_corrupted_golden(self):self.run_tb(corrupt=True)
    def test_tb_rejects_address_alias(self):self.run_tb('address_alias')
    def test_tb_rejects_ignored_mask(self):self.run_tb('mask_ignored')
    def test_tb_rejects_ignored_cen(self):self.run_tb('cen_ignored')


if __name__=='__main__':unittest.main()
