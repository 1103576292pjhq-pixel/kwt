"""Fresh-process regression for the official import/default-flags entry."""
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

WORKSPACE = Path(__file__).resolve().parents[2]


@unittest.skipUnless(os.environ.get("KWT_TEST_OFFICIAL_FLAGS"), "requires the real model environment")
class OfficialEntryTests(unittest.TestCase):
    def test_official_flags_in_fresh_process_from_another_directory(self):
        program = "\n".join([
            "from pathlib import Path",
            "from model.run_baseline import official_flags",
            "flags, overrides, builder = official_flags(Path({!r}) / 'vendor/keyword-transformer')".format(str(WORKSPACE)),
            "assert flags.mlp_dim == 256",
            "assert flags.prenorm is False",
            "assert flags.training is False",
            "assert flags.batch_size == 1",
            "assert flags.approximate_gelu is False",
        ])
        environment = dict(os.environ, PYTHONPATH=str(WORKSPACE), PYTHONDONTWRITEBYTECODE="1", TF_CPP_MIN_LOG_LEVEL="2")
        with tempfile.TemporaryDirectory() as directory:
            result = subprocess.run([sys.executable, "-c", program], cwd=directory,
                                    env=environment, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                    universal_newlines=True)
        self.assertEqual(result.returncode, 0, result.stdout)


if __name__ == "__main__":
    unittest.main()
