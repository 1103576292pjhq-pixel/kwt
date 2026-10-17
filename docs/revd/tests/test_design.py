from __future__ import annotations
from dataclasses import asdict
import copy
import random
import unittest
from core_model import (Geometry, analytic, candidate, dense_reference, expected_indices,
                        finalize, make_case, reference_finalize, records, w_address, x_address)
from protocol_model import (ProtocolError, ReadCredits, StableChannel, WeightSlots)
from scoreboard import verify

COUNTS = {"numeric_vectors": 0, "geometry_configurations": 0,
          "synthetic_matrix_configurations": 0, "matrix_output_comparisons": 0,
          "full_size_tasks_per_schedule": 0, "rejected_mutations": 0,
          "credit_scenarios": 0}


class NumericTests(unittest.TestCase):
    def test_all_shifts_and_boundaries(self):
        rng = random.Random(20261017)
        for shift in range(48):
            for _ in range(40):
                dot = rng.randint(-(1 << 36), 1 << 36)
                bias = rng.choice([-(1 << 47), (1 << 47) - 1,
                                   rng.randint(-(1 << 47), (1 << 47) - 1)])
                self.assertEqual(finalize(dot, bias, shift), reference_finalize(dot, bias, shift))
                COUNTS["numeric_vectors"] += 1

    def test_rne_ties_positive_negative(self):
        for shift in range(1, 48):
            for q in (0, 1, 2, 3, 17):
                value = q * (1 << shift) + (1 << (shift - 1))
                for signed in (value, -value):
                    if -(1 << 47) <= signed < (1 << 47):
                        result = finalize(0, signed, shift)
                        self.assertEqual(result, reference_finalize(0, signed, shift))
                        COUNTS["numeric_vectors"] += 1
        self.assertEqual(finalize(0, -5, 1).data, -2)
        self.assertEqual(finalize(0, -3, 1).data, -2)

    def test_overflow_and_saturation_are_distinct(self):
        result = finalize(1, (1 << 47) - 1, 47)
        self.assertTrue(result.overflow)
        self.assertFalse(result.saturated)
        result = finalize(1 << 35, 0, 0)
        self.assertFalse(result.overflow)
        self.assertTrue(result.saturated)

    def test_reject_invalid_values(self):
        for shift in (-1, 48, True, 1.0):
            with self.assertRaises(ValueError):
                finalize(0, 0, shift)
        for bias in (1 << 47, -(1 << 47) - 1, True):
            with self.assertRaises(ValueError):
                finalize(0, bias, 0)
        g = Geometry(m=1, n=16)
        case = make_case(g, 1)
        case["x"][0][0] = 32768
        with self.assertRaises(ValueError):
            candidate(g, case["x"], case["w"], case["bias"], 0)


class GeometryTests(unittest.TestCase):
    def test_supported_grid_address_bijection(self):
        for m in (1, 3, 4, 5, 99):
            for n in (16, 32, 256):
                for pm in (1, 2, 4):
                    g = Geometry(m=m, n=n, pm=pm)
                    xa = {x_address(g, row, k) for row in range(m) for k in range(64)}
                    wa = {w_address(g, k, col, False) for k in range(64) for col in range(n)}
                    self.assertEqual(len(xa), m * 64)
                    self.assertEqual(len(wa), n * 64)
                    for nt in range(0, n, 16):
                        addresses = {w_address(g, k, col, True) for k in range(64) for col in range(nt, nt + 16)}
                        self.assertEqual(len(addresses), 64 * 16)
                    ids = expected_indices(g)
                    self.assertEqual(len(ids), m * n)
                    self.assertEqual(set(ids), set(range(m * n)))
                    self.assertEqual(ids[-1], m * n - 1)
                    COUNTS["geometry_configurations"] += 1

    def test_broadcast_step_never_same_bank_conflict(self):
        g = Geometry()
        for m0 in range(0, 99, 4):
            for k in range(64):
                banks = [x_address(g, m, k)[0] for m in range(m0, min(m0 + 4, 99))]
                self.assertEqual(len(banks), len(set(banks)))
        for n0 in range(0, 256, 4):
            banks = [w_address(g, 0, n, True)[0] for n in range(n0, n0 + 4)]
            self.assertEqual(len(set(banks)), 4)

    def test_unsupported_parameters_fail_explicitly(self):
        for params in (dict(n=17), dict(n=0), dict(n=255), dict(pm=3), dict(k=63),
                       dict(n_tile=32), dict(m=100), dict(pn=8), dict(m=True)):
            with self.assertRaises(ValueError):
                Geometry(**params)

    def test_analytic_main_configuration(self):
        g = Geometry()
        old, new = analytic(g, "micro"), analytic(g, "ctx4")
        self.assertEqual(old["ideal_issue_slots"], 102400)
        self.assertEqual(new["ideal_issue_slots"], 102400)
        self.assertEqual(old["x_bank_reads"], 405504)
        self.assertEqual(new["x_bank_reads"], 101376)
        self.assertEqual(new["w_bank_reads"], 409600)
        self.assertEqual(old["operand_bank_reads"], 815104)
        self.assertEqual(new["operand_bank_reads"], 510976)
        self.assertEqual((old["accumulator_bytes"], new["accumulator_bytes"]), (96, 384))
        self.assertEqual(new["useful_macs"], 1622016)
        self.assertEqual(new["invalid_lane_slots"], 16384)


class MatrixTests(unittest.TestCase):
    def check_case(self, g, seed, shift):
        case = make_case(g, seed, shift)
        reference = dense_reference(g, case["x"], case["w"], case["bias"], shift)
        for schedule in ("micro", "ctx4"):
            output, counts = candidate(g, case["x"], case["w"], case["bias"], shift, schedule)
            self.assertEqual(reference, output)
            prediction = analytic(g, schedule)
            self.assertEqual(counts["issue_slots"], prediction["ideal_issue_slots"])
            for key in ("x_bank_reads", "w_bank_reads", "useful_macs", "invalid_lane_slots"):
                self.assertEqual(counts[key], prediction[key])
            verify(list(records(g, output, seed)), reference, g, seed)
            COUNTS["matrix_output_comparisons"] += g.m * g.n
        COUNTS["synthetic_matrix_configurations"] += 1

    def test_small_geometries_and_shifts(self):
        for pm in (1, 2, 4):
            for m in (1, 3, 5):
                for shift in (0, 1, 17, 47):
                    self.check_case(Geometry(m=m, n=16, pm=pm), 53 + m, shift)

    def test_full_99_64_256(self):
        self.check_case(Geometry(), 20261017, 8)
        COUNTS["full_size_tasks_per_schedule"] += 1

    def test_only_final_product_nonzero(self):
        g = Geometry(m=3, n=16)
        x = [[0] * 63 + [r + 1] for r in range(3)]
        w = [[0] * 16 for _ in range(63)] + [[c - 8 for c in range(16)]]
        reference = dense_reference(g, x, w, [0] * 16, 0)
        output, _ = candidate(g, x, w, [0] * 16, 0)
        self.assertEqual(reference, output)
        self.assertEqual(output[2 * 16].data, -24)
        w[-1] = [0] * 16
        broken, _ = candidate(g, x, w, [0] * 16, 0)
        self.assertNotEqual(reference, broken)
        COUNTS["rejected_mutations"] += 1


class ScoreboardTests(unittest.TestCase):
    def test_actual_record_mutations_rejected(self):
        g = Geometry(m=5, n=32)
        case = make_case(g, 2026, 8)
        reference = dense_reference(g, case["x"], case["w"], case["bias"], 8)
        good = list(records(g, reference, 7))
        self.assertEqual(verify(good, reference, g, 7)["outputs"], 160)
        mutations = []
        wrong = copy.deepcopy(good); wrong[0]["data"] ^= 1; mutations.append(wrong)
        wrong = copy.deepcopy(good); wrong[0]["overflow"] ^= True; mutations.append(wrong)
        wrong = copy.deepcopy(good); wrong[0]["saturated"] ^= True; mutations.append(wrong)
        wrong = copy.deepcopy(good); wrong[1] = copy.deepcopy(wrong[0]); mutations.append(wrong)
        wrong = copy.deepcopy(good); wrong[0]["task_id"] = 8; mutations.append(wrong)
        wrong = copy.deepcopy(good); wrong[-1]["last"] = False; mutations.append(wrong)
        wrong = copy.deepcopy(good); wrong[0]["last"] = True; mutations.append(wrong)
        wrong = copy.deepcopy(good); wrong[0]["y_index"] = 160; mutations.append(wrong)
        wrong = copy.deepcopy(good); wrong[0]["data"] = True; mutations.append(wrong)
        wrong = copy.deepcopy(good); wrong[0]["overflow"] = 0; mutations.append(wrong)
        wrong = copy.deepcopy(good); wrong[0], wrong[1] = wrong[1], wrong[0]; mutations.append(wrong)
        mutations.append(good[:-1]); mutations.append(good + [good[-1]])
        for bad in mutations:
            with self.assertRaises(ValueError):
                verify(bad, reference, g, 7)
            COUNTS["rejected_mutations"] += 1


class ProtocolTests(unittest.TestCase):
    def prepare_slot(self, slots, tile):
        i = slots.open(tile)
        for w in range(slots.weight_words):
            slots.write(i, "W", w)
            slots.acknowledge_write(i)
        for b in range(slots.bias_words):
            slots.write(i, "B", b)
            slots.acknowledge_write(i)
        slots.commit(i)
        return i

    def test_double_buffer_ownership(self):
        slots = WeightSlots(weight_words=8, bias_words=4)
        i = self.prepare_slot(slots, 0); slots.activate(i)
        j = self.prepare_slot(slots, 1)
        self.assertNotEqual(i, j)
        with self.assertRaises(ProtocolError): slots.write(i, "W", 0)
        with self.assertRaises(ProtocolError): slots.release(i)
        with self.assertRaises(BlockingIOError): slots.open(2)
        slots.finish_bias_use(i); slots.release(i)
        slots.activate(j)
        self.assertEqual(slots.open(2), i)

    def test_incomplete_duplicate_and_commit_barrier(self):
        slots = WeightSlots(weight_words=1, bias_words=1)
        i = slots.open(0)
        with self.assertRaises(ProtocolError): slots.commit(i)
        slots.write(i, "W", 0)
        with self.assertRaises(ProtocolError): slots.write(i, "W", 0)
        slots.write(i, "B", 0)
        with self.assertRaises(BlockingIOError): slots.commit(i)
        slots.acknowledge_write(i); slots.acknowledge_write(i); slots.commit(i)
        self.assertEqual(slots.slots[i].state, "READY")

    def test_reset_clears_validity_not_memory_assumption(self):
        slots = WeightSlots(weight_words=1, bias_words=1)
        i = self.prepare_slot(slots, 0); slots.activate(i)
        slots.reset()
        self.assertTrue(all(s.state == "EMPTY" for s in slots.slots))
        self.assertEqual(slots.open(0), 0)

    def test_out_of_order_or_multiple_fill_rejected(self):
        slots = WeightSlots()
        with self.assertRaises(ProtocolError): slots.open(1)
        slots.open(0)
        with self.assertRaises(ProtocolError): slots.open(1)

    def test_read_credit_latencies_and_stalls(self):
        for latency in (1, 2):
            for period in (1, 2, 4, 8, 16):
                credits = ReadCredits(4)
                returns, issued, consumed = {}, 0, 0
                for cycle in range(10000):
                    if cycle in returns:
                        credits.returned()
                    if cycle % period == 0 and credits.buffered:
                        credits.consume(); consumed += 1
                    if credits.can_issue and issued < 257:
                        credits.issue(); returns[cycle + latency] = issued; issued += 1
                    self.assertLessEqual(credits.inflight + credits.buffered, 4)
                    if consumed == 257: break
                self.assertEqual((issued, consumed, credits.inflight, credits.buffered), (257, 257, 0, 0))
                COUNTS["credit_scenarios"] += 1

    def test_credit_overflow_rejected(self):
        credits = ReadCredits(1); credits.issue()
        with self.assertRaises(BlockingIOError): credits.issue()
        credits.returned()
        with self.assertRaises(BlockingIOError): credits.issue()
        credits.consume(); self.assertTrue(credits.can_issue)

    def test_stable_payload_and_reset_exception(self):
        monitor = StableChannel(); monitor.observe(True, False, (1, 2))
        monitor.observe(True, False, (1, 2))
        monitor.observe(True, True, (1, 2))
        monitor.observe(False, False, (0, 0))
        monitor.observe(True, False, (1, 3))
        with self.assertRaises(ProtocolError): monitor.observe(True, False, (1, 4))
        monitor.observe(False, False, (0, 0), reset=True)
        monitor.observe(True, True, (2, 0))

if __name__ == "__main__":
    unittest.main()
