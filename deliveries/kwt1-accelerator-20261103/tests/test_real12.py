"""The actual response ledger must catch missing/duplicate/corrupted outputs."""
import importlib.util
from pathlib import Path
import tempfile
import unittest
import numpy as np


class Real12TraceTests(unittest.TestCase):
    def setUp(self):
        path=Path(__file__).resolve().parents[1]/'scripts/verify_real12.py'
        self.assertTrue(path.exists(),'Real12 ledger auditor is missing')
        spec=importlib.util.spec_from_file_location('real12_verifier',path)
        self.module=importlib.util.module_from_spec(spec)
        spec.loader.exec_module(self.module)
        self.expected=np.ones((1,99,256),dtype=np.uint32)
        self.expected[0,-1,-1] |= np.uint32(4<<16)
        self.reference=np.full((1,99,256),1/4096,dtype=np.float32)
        self.lines=['R 0 %d %08x\n'%(index,int(value))
                    for index,value in enumerate(self.expected.reshape(-1))]
        self.temp=tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.trace=Path(self.temp.name)/'trace.txt'

    def audit(self,lines):
        self.trace.write_text(''.join(lines),encoding='ascii')
        return self.module.audit_trace(self.trace,self.expected,self.reference)

    def test_complete_trace_uses_actual_decoded_outputs(self):
        result=self.audit(self.lines)
        self.assertEqual(result['outputs'],25344)
        self.assertEqual(result['tasks'][0]['nrmse'],0)
        self.assertEqual(result['tasks'][0]['last_flags'],1)

    def test_missing_last_output_is_rejected(self):
        with self.assertRaisesRegex(ValueError,'missing'):
            self.audit(self.lines[:-1])

    def test_duplicate_does_not_mask_missing_output(self):
        with self.assertRaisesRegex(ValueError,'duplicate'):
            self.audit(self.lines[:-1]+self.lines[:1])

    def test_value_and_flag_corruption_are_rejected(self):
        for bad in ['R 0 0 00000000\n','R 0 0 00010001\n']:
            with self.subTest(bad=bad), self.assertRaisesRegex(ValueError,'mismatch'):
                self.audit([bad]+self.lines[1:])

    def test_out_of_range_task_index_or_unknown_value_rejected(self):
        for bad in ['R 1 0 00000001\n','R 0 25344 00000001\n',
                    'R 0 -1 00000001\n','R 0 0 xxxxxxxx\n']:
            with self.subTest(bad=bad), self.assertRaises(ValueError):
                self.audit([bad]+self.lines[1:])


if __name__=='__main__':
    unittest.main()
