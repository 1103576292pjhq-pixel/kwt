"""Catch overlap double-counting, wrong throughput aggregation and bad ledgers."""
import csv
import importlib.util
from pathlib import Path
import tempfile
import unittest


class PerformanceTests(unittest.TestCase):
    def setUp(self):
        path=Path(__file__).resolve().parents[1]/'integration/e203/performance_baseline/performance.py'
        self.assertTrue(path.exists(),'Performance auditor is missing')
        spec=importlib.util.spec_from_file_location('performance_metrics',path)
        self.module=importlib.util.module_from_spec(spec);spec.loader.exec_module(self.module)
        self.temp=tempfile.TemporaryDirectory();self.addCleanup(self.temp.cleanup)
        self.csv=Path(self.temp.name)/'metrics.csv'

    def row(self,index=0,scale=1):
        start=index*2000000+100
        return dict(task=index,start_cycle=start,first_core_cycle=start+900,
                    final_commit_cycle=start+800000*scale,last_core_cycle=start+950000*scale,
                    last_read_cycle=start+990000*scale,last_ack_cycle=start+999000*scale,
                    complete_cycle=start+1000000*scale,span_cycles=1000000*scale,
                    load_bus_cycles=400000*scale,status_bus_cycles=200000*scale,
                    output_bus_cycles=300000*scale,ack_bus_cycles=50000*scale,tb_gap_cycles=50000*scale,
                    core_busy_cycles=200000,operand_groups=102400,core_output_stall_cycles=0,
                    core_blocks=400,core_outputs=25344,read_outputs=25344,ack_blocks=400,
                    mmio_requests=100000,mmio_responses=100000,error_responses=0,
                    response_hold_cycles=0,command_backpressure_cycles=0,ready_wait_polls=0,result_wait_polls=0)

    def audit(self,rows):
        with self.csv.open('w',newline='') as stream:
            writer=csv.DictWriter(stream,fieldnames=list(rows[0]));writer.writeheader();writer.writerows(rows)
        return self.module.analyse_metrics(self.csv,len(rows),150.)

    def test_single_task_units_and_core_overlap(self):
        report=self.audit([self.row()])
        self.assertEqual(report['total_cycles'],1000000)
        self.assertEqual(report['normalized_tasks_per_second'],150.)
        self.assertAlmostEqual(report['tasks'][0]['normalized_time_ms'],20/3)
        self.assertAlmostEqual(report['tasks'][0]['useful_mac_utilization_total'],.101376)
        self.assertAlmostEqual(report['tasks'][0]['useful_mac_utilization_core_busy'],.50688)

    def test_throughput_uses_total_time_not_mean_rates(self):
        report=self.audit([self.row(),self.row(1,2)])
        self.assertEqual(report['total_cycles'],3000000)
        self.assertEqual(report['normalized_tasks_per_second'],100.)

    def test_bad_bucket_sum_rejected(self):
        row=self.row();row['load_bus_cycles']+=1
        with self.assertRaises(ValueError):self.audit([row])

    def test_bad_counts_errors_holds_and_events_rejected(self):
        for key,value in [('core_blocks',399),('operand_groups',102399),('read_outputs',25343),
                          ('ack_blocks',399),('error_responses',1),('response_hold_cycles',1),
                          ('last_ack_cycle',1),('core_busy_cycles',100),('mmio_responses',99999)]:
            with self.subTest(key=key),self.assertRaises(ValueError):
                row=self.row();row[key]=value;self.audit([row])

    def test_duplicate_task_or_overlapping_windows_rejected(self):
        with self.assertRaises(ValueError):self.audit([self.row(),self.row()])
        row=self.row(1);row['start_cycle']=1
        with self.assertRaises(ValueError):self.audit([self.row(),row])


if __name__=='__main__':unittest.main()
