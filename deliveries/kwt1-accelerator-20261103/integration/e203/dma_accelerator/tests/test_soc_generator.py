from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
HERE=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(HERE))
from prepare_soc import convert,BUS

def fixture():
    declarations=['input kwt_bus_clk,kwt_bus_rst_n']
    for prefix in ['sysper_icb','sysmem_icb']:
        for name in BUS:
            direction='output' if name in ['cmd_ready','rsp_valid','rsp_rdata','rsp_err'] else 'input'
            width='[31:0] ' if name in ['cmd_addr','cmd_wdata','rsp_rdata'] else ('[3:0] ' if name=='cmd_wmask' else '')
            declarations.append(direction+' '+width+prefix+'_'+name)
    text='module kwt_shared_soc_top('+',\n'.join(declarations)+');\n'
    for module,instance,prefix in [('kwt_accelerator','u_kwt_accelerator','sysper_icb'),('kwt_shared_sram','u_shared_sram','sysmem_icb')]:
        ports=['.clk(kwt_bus_clk)','.rst_n(kwt_bus_rst_n)']+['.icb_'+name+'('+prefix+'_'+name+')' for name in BUS]
        if module=='kwt_accelerator':ports+=['.external_abort_req(1\'b0)','.busy()','.compute_done()','.task_done()','.fault()','.error_code()','.abort_pending()','.abort_done()']
        text+=module+" #(.SRAM_EMA(3'd2)) "+instance+'('+',\n'.join(ports)+');\n'
    return text+'endmodule\n'

class GeneratorTests(unittest.TestCase):
    def test_generated_top_elaborates_with_dma_and_shared_array(self):
        original=fixture();result=convert(original)
        with tempfile.TemporaryDirectory() as folder:
            temp=Path(folder);top=temp/'top.v';top.write_text(result)
            (temp/'model.v').write_bytes((HERE/'tests/support/shared_model.v').read_bytes())
            sources=list((HERE/'rtl').rglob('*.v'))
            p=subprocess.run(['iverilog','-g2001','-DKWT_STORAGE_TEST_CONTRACT','-I',str(HERE/'rtl/include'),
                '-s','kwt_dma_soc_top','-o',str(temp/'sim'),*map(str,sources),str(temp/'model.v'),
                str(HERE/'tests/support/sram_contract_models.v'),str(top)],capture_output=True,text=True)
            self.assertEqual(p.returncode,0,p.stderr)
            self.assertIn('u_dma_shared_arbiter',(temp/'sim').read_text())
    def test_existing_live_status_and_unknown_or_repeated_top_rejected(self):
        original=fixture()
        for text in [original.replace('.busy()','.busy(live_signal)'),original.replace(".external_abort_req(1'b0)",'.external_abort_req(live_abort)'),convert(original)]:
            with self.assertRaises(ValueError):convert(text)

if __name__=='__main__':unittest.main()
