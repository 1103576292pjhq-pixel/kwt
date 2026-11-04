"""Report rejection tests using a real local RTL trace; no simulated CPU claim."""
import unittest
from pathlib import Path
import run_suite

ROOT=Path(__file__).resolve().parents[3]
class AuditTests(unittest.TestCase):
    def setUp(self):
        self.work=ROOT/'verification/dma-suite-wiring-20261104-01'
        self.log=(self.work/'case1/run.log').read_text()
        self.gold=[int(x,16) for x in (self.work/'data/case1/gold.hex').read_text().splitlines()]
        self.original=run_suite.audit_cpu
        # Only the CPU model is stubbed; full data, timing, counters and clear checks run.
        run_suite.audit_cpu=lambda text:dict(cpu_model='BFM_ONLY')
    def tearDown(self):run_suite.audit_cpu=self.original
    def audit(self,text):
        return run_suite.audit(text,self.gold,ROOT/'verification/real12-20261102-02/fixtures/case1-ref.f32',self.work/'case1/shared-y.txt')
    def test_real_trace(self):
        result=self.audit(self.log)
        self.assertEqual(result['correctness']['outputs'],25344)
        self.assertEqual(result['bus']['dma_writes'],25344)
    def test_missing_scrub_rejected(self):
        with self.assertRaises(ValueError):self.audit(self.log.replace('CLEAR_SHARED_PASS','REMOVED'))
    def test_missing_invalidation_rejected(self):
        with self.assertRaises(ValueError):self.audit(self.log.replace('CLEAR_CACHE_PASS','REMOVED'))
    def test_missing_write_rejected(self):
        with self.assertRaises(ValueError):self.audit(self.log.replace('dma_writes=25344','dma_writes=25343'))
    def test_duplicate_metrics_rejected(self):
        line=next(x for x in self.log.splitlines() if x.startswith('SUITE_METRICS '))
        with self.assertRaises(ValueError):self.audit(self.log+'\n'+line+'\n')

if __name__=='__main__':unittest.main()
