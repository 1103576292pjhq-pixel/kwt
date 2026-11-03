"""Breaks caught: averaging sample NRMSE, wrong RMS floor, lost multiplicity."""
import importlib.util
from pathlib import Path
import math
import unittest
import numpy as np


class PrecisionMetricsTests(unittest.TestCase):
    def setUp(self):
        path = Path(__file__).resolve().parents[1]/'scripts/evaluate_precision.py'
        self.assertTrue(path.exists(), 'Real-data precision evaluator is missing')
        spec = importlib.util.spec_from_file_location('precision_evaluator', path)
        self.module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(self.module)
        self.metrics = self.module.LayerMetrics(1)

    def test_combines_energy_before_normalizing(self):
        self.metrics.add(np.array([1.]), np.array([0.]), 'a')
        self.metrics.add(np.array([100.]), np.array([100.]), 'b')
        got = self.metrics.result()
        self.assertAlmostEqual(got['nrmse'], math.sqrt(1/10001))
        self.assertEqual(got['worst_task']['sample'], 'a')
        self.assertEqual(got['worst_task']['nrmse'], 1.)
        self.assertEqual(got['values'], 2)

    def test_floor_applies_to_rms_not_squared_energy(self):
        self.metrics.add(np.array([0., 0.]), np.array([1e-10, -1e-10]), 'zero')
        self.assertAlmostEqual(self.metrics.result()['nrmse'], .01)

    def test_multiplicity_preserves_original_index(self):
        self.metrics.add(np.array([1.]), np.array([0.]), 'silence', multiplicity=3)
        self.metrics.add(np.array([2.]), np.array([2.]), 'voice')
        got = self.metrics.result()
        self.assertEqual(got['values'], 4)
        self.assertEqual(got['tasks'], 4)
        self.assertAlmostEqual(got['nrmse'], math.sqrt(3/7))
        self.assertEqual(got['max_abs_error'], 1.)

    def test_threshold_is_three_percent_not_three(self):
        self.metrics.add(np.array([100.]), np.array([97.]), 'boundary')
        self.assertTrue(self.metrics.result()['within_3_percent'])
        self.metrics.add(np.array([100.]), np.array([96.]), 'over')
        self.assertFalse(self.metrics.result()['within_3_percent'])

    def test_rejects_invalid_references_and_weights(self):
        for reference, result, multiplicity in [
            ([float('nan')], [0.], 1), ([1.], [float('inf')], 1),
            ([1.], [0.], 0), ([1.], [0.], True), ([1.], [0.], 1.5),
            ([1., 2.], [0.], 1), ([], [], 1),
        ]:
            with self.subTest(reference=reference, result=result, weight=multiplicity):
                with self.assertRaises(ValueError):
                    self.metrics.add(np.array(reference), np.array(result), 'bad', multiplicity)


if __name__ == '__main__':
    unittest.main()
