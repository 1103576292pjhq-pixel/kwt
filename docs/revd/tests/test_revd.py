"""RevD additions: mathematical examples, metric definitions and X prefetch spec."""
from __future__ import annotations
import unittest, random, math
from core_model import finalize, reference_finalize
from memory_review import cover_words, x_location, prefetch, examples
from precision_metrics import precision_points, top1_report, aggregate_layer
from segmented_reference import segmented_dot, worst_case_sum_bits

COUNTS={'x_address_checks':0,'prefetch_runs':0,'prefetch_operand_identity_checks':0,
        'segmented_dots':0,'known_bad_segment_policies_rejected':0}

class MemoryReviewTests(unittest.TestCase):
    def test_capacity_not_total_working_set(self):
        j=examples()
        self.assertLessEqual(j['one_int16_feature_bytes'],j['two_4096_macros_bytes'])
        self.assertGreater(j['x_and_y_int16_bytes'],j['two_4096_macros_bytes'])
        self.assertEqual(j['ffn1_int32_output_bytes'],101376)
    def test_capacity_and_macro_count_tradeoff(self):
        a=cover_words(1600,'capacity');b=cover_words(1600,'macro_count')
        self.assertEqual((a['allocated_words'],a['macros']),(1664,6))
        self.assertEqual((b['allocated_words'],b['macros']),(4096,1))
        self.assertIsNone(a['area_mm2'])
    def test_two_bank_mapping_full_input(self):
        for banks in (2,4):
            seen=set()
            for m in range(99):
                for k in range(64):
                    cell=x_location(m,k,banks)
                    self.assertNotIn(cell,seen);seen.add(cell)
                    self.assertLess(cell[1],4096 if banks==2 else 2048)
                    COUNTS['x_address_checks']+=1
            self.assertEqual(len(seen),6336)
    def test_xp2_one_and_two_cycle_reads(self):
        for latency in (1,2):
            for rows in (1,2,3,4):
                j=prefetch(latency=latency,rows=rows)
                self.assertEqual(j['issue_slots'],256)
                self.assertEqual(j['x_scalar_reads'],64*rows)
                self.assertEqual(j['post_start_nonissue_cycles'],0)
                self.assertEqual(j['gaps_between_vector_starts'],[4])
                COUNTS['prefetch_runs']+=1
                COUNTS['prefetch_operand_identity_checks']+=j['operand_identity_checks']
    def test_xp2_stalls_and_longer_read_latencies(self):
        for latency in (1,2,3,5):
            for period in (3,5,8):
                j=prefetch(latency=latency,stall_period=period)
                self.assertEqual(j['issue_slots'],256)
                self.assertEqual(j['x_scalar_reads'],256)
                self.assertGreater(j['post_start_nonissue_cycles'],0)
                COUNTS['prefetch_runs']+=1
                COUNTS['prefetch_operand_identity_checks']+=j['operand_identity_checks']
    def test_unhidden_latency_is_not_zero(self):
        j=prefetch(banks=1,latency=2)
        self.assertGreater(j['post_start_nonissue_cycles'],0)
        COUNTS['prefetch_runs']+=1
        COUNTS['prefetch_operand_identity_checks']+=j['operand_identity_checks']
    def test_invalid_memory_configuration(self):
        for call in (lambda:cover_words(0),lambda:cover_words(True),lambda:cover_words(1,'area'),
                     lambda:x_location(99,0,2),lambda:x_location(0,64,2),
                     lambda:prefetch(stall_period=1),lambda:prefetch(banks=3)):
            with self.assertRaises(ValueError):call()

class PrecisionReviewTests(unittest.TestCase):
    def test_gate_is_not_full_marks(self):
        j=precision_points(.03)
        self.assertTrue(j['numerical_threshold_pass'])
        self.assertAlmostEqual(j['precision_points_out_of_10'],0)
        self.assertEqual(precision_points(0)['precision_points_out_of_10'],10)
    def test_point_three_percent_is_nine_points(self):
        self.assertAlmostEqual(precision_points(.003)['precision_points_out_of_10'],9)
        self.assertFalse(precision_points(.030001)['numerical_threshold_pass'])
    def test_top1_percentage_points(self):
        j=top1_report(570,558,600)
        self.assertEqual(j['drop_percentage_points'],2)
        self.assertTrue(j['threshold_pass']);self.assertEqual(j['precision_points_out_of_10'],0)
        self.assertFalse(top1_report(570,557,600)['threshold_pass'])
        self.assertEqual(top1_report(570,571,600)['precision_points_out_of_10'],10)
    def test_layer_aggregate_not_mean_of_ratios(self):
        j=aggregate_layer([([1.0],[1.1]),([100.0],[100.0])])
        self.assertAlmostEqual(j['nrmse_fraction'],math.sqrt(.01/10001))
        self.assertNotAlmostEqual(j['nrmse_fraction'],.05)
    def test_reference_floor_and_nonfinite_rejection(self):
        self.assertAlmostEqual(aggregate_layer([([0.0],[1e-10])])['nrmse_fraction'],.01)
        for call in (lambda:precision_points(float('nan')),lambda:precision_points(-1),
                     lambda:aggregate_layer([]),lambda:aggregate_layer([([1],[])]),
                     lambda:aggregate_layer([([1],[float('inf')])]),lambda:top1_report(1,2,1)):
            with self.assertRaises(ValueError):call()

class ReusableDotTests(unittest.TestCase):
    def test_long_k_contract_examples(self):
        rng=random.Random(20261017)
        for k in (64,99,128,256):
            for shift in (0,1,4,16,32,47):
                for rep in range(5):
                    x=[rng.randint(-32768,32767) for _ in range(k)]
                    w=[rng.randint(-32768,32767) for _ in range(k)]
                    bias=rng.choice([-(2**47),2**47-1,0,123])
                    self.assertEqual(segmented_dot(x,w,bias,shift),reference_finalize(sum(a*b for a,b in zip(x,w)),bias,shift))
                    COUNTS['segmented_dots']+=1
    def test_per_block_sat_is_wrong(self):
        x=[32767]*256;w=[32767]*64+[-32766]*64+[0]*128
        correct=segmented_dot(x,w,0,0)
        wrong=sum(finalize(sum(a*b for a,b in zip(x[s:s+64],w[s:s+64])),0,0).data for s in range(0,256,64))
        self.assertEqual(correct.data,2097088);self.assertEqual(wrong,-1)
        COUNTS['known_bad_segment_policies_rejected']+=1
    def test_per_block_round_is_wrong(self):
        x=[1]*99;w=[0]*99;w[0]=1;w[64]=2
        correct=segmented_dot(x,w,0,2)
        wrong=sum(finalize(sum(a*b for a,b in zip(x[s:s+64],w[s:s+64])),0,2).data for s in (0,64))
        self.assertEqual(correct.data,1);self.assertEqual(wrong,0)
        COUNTS['known_bad_segment_policies_rejected']+=1
    def test_bias_once(self):
        x=[1]+[0]*98;w=[1]*99
        self.assertEqual(segmented_dot(x,w,5,0).data,6)
        wrong=sum(finalize(sum(a*b for a,b in zip(x[s:s+64],w[s:s+64])),5,0).data for s in (0,64))
        self.assertEqual(wrong,11)
        COUNTS['known_bad_segment_policies_rejected']+=1
    def test_accumulator_bound_not_bias_bound(self):
        self.assertEqual(worst_case_sum_bits(64),38)
        self.assertEqual(worst_case_sum_bits(256),40)
        self.assertLessEqual(worst_case_sum_bits(256),48)
        # Positive K*2**30 requires 40 signed bits at K=256; 48-bit bias still needs 49-bit add.
        with self.assertRaises(ValueError):segmented_dot([1],[1],0,0,0)
