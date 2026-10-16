import hashlib
import importlib.util
import unittest
from pathlib import Path
import tempfile

ROOT = Path(__file__).resolve().parents[1]
SCRIPT = ROOT / 'scripts' / 'fetch_official_sources.py'


class SourceFetchTests(unittest.TestCase):
    def setUp(self):
        self.assertTrue(SCRIPT.is_file(), 'Official source acquisition is not implemented')
        spec = importlib.util.spec_from_file_location('source_fetch', SCRIPT)
        self.module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(self.module)

    def test_rejects_corrupt_git_blob(self):
        payload = b'known upstream bytes\n'
        expected = hashlib.sha1(b'blob ' + str(len(payload)).encode() + b'\0' + payload).hexdigest()
        self.module.verify_blob(payload, expected)
        with self.assertRaises(ValueError):
            self.module.verify_blob(payload + b'changed', expected)

    def test_rejects_path_outside_snapshot(self):
        with tempfile.TemporaryDirectory() as temp:
            for path in ('../outside', '/absolute', 'safe/../../outside'):
                with self.assertRaises(ValueError):
                    self.module.safe_destination(Path(temp), path)

    def test_selects_only_required_checkpoint(self):
        paths = ['kws_streaming/models/kws_transformer.py',
                 'models_data_v2_12_labels/kwt1/best_weights.index',
                 'models_data_v2_12_labels/kwt1/last_weights.index',
                 'models_data_v2_12_labels/kwt3/best_weights.index']
        tree = [{'type': 'blob', 'path': path} for path in paths]
        selected = [item['path'] for item in self.module.select_sources(tree)]
        self.assertEqual(selected, paths[:2])


if __name__ == '__main__':
    unittest.main()
