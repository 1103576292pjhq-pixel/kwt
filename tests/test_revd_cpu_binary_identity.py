"""Read-only regressions against a real immutable E203 receipt, plus binder tests.

Run under the receipt's WSL interpreter. The source-current check is deliberately
disabled for historical evidence; byte, command, tool and arithmetic checks stay
enabled. Mutations below are explicit in-memory views, never historical edits.
"""
from __future__ import annotations
import argparse
import copy
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts import revd_offline_gate as gate
from scripts import revd_offline_soc_bindings as binder
from scripts.revd_offline_common import put, read_json, sha, utc

REPORT = ROOT / 'reports/revd_offline/soc/soc-full-pm4-20261017T062100Z/result.json'
OBSERVATIONS = []


class HistoricalCpuIdentity(unittest.TestCase):
    def setUp(self):
        self.binding_path = REPORT.parent / 'binary-binding.json'
        self.original_binding = read_json(self.binding_path)
        self.binary = REPORT.parent / 'obj/Vsoc_cpu_tb'

    def check(self, name, mutate=None, missing=False, replacement=None, error=None, fresh_source_view=False,
              compiled_digest='actual',case_offset_view=0):
        real_read, real_sha, real_is_file = gate.read_json, gate.sha, Path.is_file
        binding = copy.deepcopy(self.original_binding)
        if mutate:
            mutate(binding)
        def read_view(path):
            if Path(path) == self.binding_path:
                if missing:
                    raise FileNotFoundError(str(path))
                return binding
            if fresh_source_view and Path(path)==REPORT:
                # Explicit semantic view of a genuine immutable receipt, not a
                # new CPU run: isolate current-source legacy downgrade policy.
                report=copy.deepcopy(real_read(path))
                report['source_sha256']={p:real_sha(ROOT/p) for p in report['source_sha256']}
                report['source_sha256']['scripts/revd_offline_soc_bindings.py']=real_sha(ROOT/'scripts/revd_offline_soc_bindings.py')
                if case_offset_view:
                    report['profile']['case_offset']=case_offset_view
                    report['source_sha256']['scripts/revd_offline_soc_layers.py']=real_sha(ROOT/'scripts/revd_offline_soc_layers.py')
                report['compiled_simulator_sha256']=real_sha(self.binary) if compiled_digest=='actual' else compiled_digest
                return report
            return real_read(path)
        def hash_view(path):
            if replacement is not None and Path(path) == self.binary:
                return real_sha(replacement)
            return real_sha(path)
        def file_view(path):
            return False if missing and path == self.binding_path else real_is_file(path)
        observation = {'name': name, 'expected': 'REJECT' if error else 'ACCEPT',
                       'current_source_semantic_view':fresh_source_view}
        with patch.object(gate, 'read_json', read_view), patch.object(gate, 'sha', hash_view), patch.object(Path, 'is_file', file_view):
            try:
                result = gate.check_cpu(REPORT, current=fresh_source_view)
                observation.update(actual='ACCEPT', returned_binary_sha256=result['cpu_binary_sha256'])
            except (ValueError, OSError) as exc:
                observation.update(actual='REJECT', error=str(exc))
        OBSERVATIONS.append(observation)
        self.assertEqual(observation['actual'], observation['expected'], observation)
        if error:
            self.assertIn(error, observation['error'])

    def test_legacy_bound_real_cpu_receipt_still_validates(self):
        self.check('legacy_bound_real_receipt')

    def test_missing_expected_binding_rejected(self):
        self.check('missing_binding', missing=True, error='binary binding missing')

    def test_replaced_binary_bytes_rejected(self):
        with tempfile.TemporaryDirectory() as folder:
            replacement = Path(folder) / 'Vsoc_cpu_tb'
            replacement.write_bytes(b'not the simulator that produced the accepted CPU log\n')
            self.assertNotEqual(sha(replacement), self.original_binding['actual_executable_sha256'])
            self.check('replaced_binary_temporary_bytes', replacement=replacement, error='expected executable binding mismatch')

    def test_binding_status_rejected(self):
        self.check('forged_status', lambda b: b.update(status='PASS'), error='binary binding identity')

    def test_report_digest_rejected(self):
        self.check('forged_report_digest', lambda b: b.update(original_report_sha256='0'*64), error='original report binding mismatch')

    def test_report_path_alias_rejected(self):
        self.check('aliased_report_path', lambda b: b.update(original_report='./'+b['original_report']), error='original report binding mismatch')

    def test_executable_path_rejected(self):
        self.check('forged_executable_path', lambda b: b.update(actual_executable='/usr/bin/true'), error='expected executable binding mismatch')

    def test_firmware_digest_rejected(self):
        self.check('forged_firmware_digest', lambda b: b.update(firmware_binary_sha256='0'*64), error='firmware binding mismatch')

    def test_command_digest_rejected(self):
        self.check('forged_command_digest', lambda b: b.update(cpu_command_record_sha256='0'*64), error='command binding mismatch')

    def test_log_digest_rejected(self):
        self.check('forged_log_digest', lambda b: b.update(cpu_log_sha256='0'*64), error='log binding mismatch')

    def test_creator_digest_rejected(self):
        self.check('unknown_creator_digest', lambda b: b.update(binding_script_sha256='0'*64), error='binding creator source mismatch')

    def test_modified_historical_flag_rejected(self):
        self.check('historical_modified_flag', lambda b: b.update(historical_report_modified=True), error='binary binding identity')

    def test_current_source_receipt_cannot_downgrade_creator_to_legacy(self):
        self.check('current_source_legacy_creator_downgrade', fresh_source_view=True,
                   error='legacy binding requires explicit historical validation')

    def test_current_source_current_creator_matches_compiled_identity(self):
        self.check('current_source_current_creator', fresh_source_view=True,
                   mutate=lambda b:b.update(binding_script_sha256=sha(ROOT/'scripts/revd_offline_soc_bindings.py')))

    def test_current_nonzero_pair_must_match_compiled_identity(self):
        self.check('current_source_nonzero_pair_wrong_compile_digest', fresh_source_view=True,
                   compiled_digest='0'*64,case_offset_view=2,error='CPU compiled simulator binding mismatch')

    def test_current_offset0_must_match_compiled_identity(self):
        self.check('current_source_offset0_wrong_compile_digest', fresh_source_view=True,
                   compiled_digest='0'*64,error='CPU compiled simulator binding mismatch',
                   mutate=lambda b:b.update(binding_script_sha256=sha(ROOT/'scripts/revd_offline_soc_bindings.py')))


class BinaryBinder(unittest.TestCase):
    def test_runner_source_inventory_binds_helper_dependency(self):
        from scripts import revd_offline_soc_run as runner
        inventory=runner.inventory()
        self.assertEqual(inventory.get('scripts/revd_offline_soc_bindings.py'),sha(ROOT/'scripts/revd_offline_soc_bindings.py'))

    def fixture(self, folder, sim='verilator'):
        root = Path(folder); out = root/'reports/revd_offline/soc/fresh'; out.mkdir(parents=True)
        binary = out/('obj/Vsoc_cpu_tb' if sim == 'verilator' else 'cpu.vvp')
        binary.parent.mkdir(parents=True, exist_ok=True); binary.write_bytes(b'compiled CPU simulator')
        (out/'revd-driver.bin').write_bytes(b'firmware')
        (out/'cpu.log').write_text('E203_REVD_PASS tasks=1\n')
        command = {'argv': ([str(binary)] if sim == 'verilator' else ['vvp',str(binary)]) + ['+FIRMWARE=revd-driver.hex','+FIRMWARE_BYTES=8'],
                   'exit_code':0,'log':(out/'cpu.log').relative_to(root).as_posix(),'log_sha256':sha(out/'cpu.log'),'cwd':str(out/'cpu')}
        put(out/'cpu.log.command.json', command)
        report = {'status':'PASS','profile':{'sim':sim,'stage':'small'},'compiled_simulator_sha256':sha(binary),
                  'results':{'cpu':{'status':'PASS','command':command}}, 'commands':[command]}
        put(out/'result.json', report)
        return root,out,binary,report

    def test_fresh_verilator_binding(self):
        with tempfile.TemporaryDirectory() as folder:
            root,out,binary,_ = self.fixture(folder)
            before = sha(out/'result.json')
            with patch.object(binder,'ROOT',root):
                value = binder.bind(out/'result.json')
            self.assertEqual(value['actual_executable_sha256'],sha(binary))
            self.assertEqual(value['original_report_sha256'],before)
            self.assertEqual(sha(out/'result.json'),before)

    def test_fresh_icarus_binds_cpu_payload_not_vvp_interpreter(self):
        with tempfile.TemporaryDirectory() as folder:
            root,out,binary,_ = self.fixture(folder,'icarus')
            with patch.object(binder,'ROOT',root):
                value = binder.bind(out/'result.json')
            self.assertEqual(value['actual_executable'],binary.relative_to(root).as_posix())

    def test_unsuccessful_cpu_cannot_bind(self):
        with tempfile.TemporaryDirectory() as folder:
            root,out,_,report = self.fixture(folder)
            report['results']['cpu']['command']['exit_code']=124; put(out/'result.json',report)
            with patch.object(binder,'ROOT',root), self.assertRaisesRegex(RuntimeError,'successful actual CPU'):
                binder.bind(out/'result.json')
            self.assertFalse((out/'binary-binding.json').exists())

    def test_changed_binary_since_compile_cannot_self_sign(self):
        with tempfile.TemporaryDirectory() as folder:
            root,out,binary,_ = self.fixture(folder); binary.write_bytes(b'replacement after compile')
            with patch.object(binder,'ROOT',root), self.assertRaisesRegex(RuntimeError,'compiled simulator digest'):
                binder.bind(out/'result.json')
            self.assertFalse((out/'binary-binding.json').exists())

    def test_existing_binding_never_overwritten(self):
        with tempfile.TemporaryDirectory() as folder:
            root,out,_,_ = self.fixture(folder); target=out/'binary-binding.json'; target.write_bytes(b'preserve me')
            with patch.object(binder,'ROOT',root), self.assertRaisesRegex(RuntimeError,'overwrite'):
                binder.bind(out/'result.json')
            self.assertEqual(target.read_bytes(),b'preserve me')


if __name__ == '__main__':
    parser=argparse.ArgumentParser(); parser.add_argument('--out',required=True); args=parser.parse_args()
    immutable_paths={'report':REPORT,'binding':REPORT.parent/'binary-binding.json',
                     'binary':REPORT.parent/'obj/Vsoc_cpu_tb','firmware':REPORT.parent/'revd-driver.bin',
                     'cpu_log':REPORT.parent/'cpu.log','cpu_command':REPORT.parent/'cpu.log.command.json'}
    started=utc(); immutable_before={name:sha(path) for name,path in immutable_paths.items()}
    result=unittest.TextTestRunner(verbosity=2).run(unittest.defaultTestLoader.loadTestsFromModule(sys.modules[__name__]))
    summary={'status':'PASS' if result.wasSuccessful() else 'FAIL','started_utc':started,'finished_utc':utc(),
             'tests':result.testsRun,'failures':len(result.failures),'errors':len(result.errors),'observations':OBSERVATIONS,
             'source_sha256':{p:sha(ROOT/p) for p in ['scripts/revd_offline_gate.py','scripts/revd_offline_soc_bindings.py','scripts/revd_offline_soc_run.py','scripts/revd_offline_reproduce.py','scripts/revd_offline_soc_layers.py','scripts/revd_offline_soc_baseline.py','scripts/revd_offline_soc_edges.py','tests/test_revd_cpu_binary_identity.py']},
             'historical_bytes_unchanged':immutable_before=={name:sha(path) for name,path in immutable_paths.items()},
             'historical_identity':immutable_before,'historical_current_source_validation':False,
             'scope':'Real immutable CPU receipt checks; explicit read-only hash/file/sidecar overlays for adversarial cases; binder unit fixtures are synthetic, not CPU simulation.'}
    put(ROOT/args.out,summary)
    raise SystemExit(0 if result.wasSuccessful() else 1)
