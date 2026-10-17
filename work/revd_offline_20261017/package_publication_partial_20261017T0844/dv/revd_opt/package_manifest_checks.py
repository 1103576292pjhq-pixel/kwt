"""Exercise package integrity on real temporary files, including path escapes."""
from pathlib import Path
import sys
import tempfile
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from scripts import revd_offline_reproduce as entry
from scripts.revd_offline_common import put, sha, run_id, utc


def main():
    out = ROOT / 'reports/revd_offline/package_manifest_tests' / run_id()
    out.mkdir(parents=True, exist_ok=False)
    tests = []
    original = entry.ROOT
    try:
        with tempfile.TemporaryDirectory(dir=out) as folder:
            package = Path(folder).resolve()
            entry.ROOT = package
            (package / 'source.py').write_text('value = 1\n', encoding='utf-8')
            members = {'source.py': sha(package / 'source.py')}
            def check(name, expected_pass, changes=None):
                put(package / 'MANIFEST.json', {'files': changes if changes is not None else members})
                try:
                    entry.manifest_check()
                    passed = True
                except ValueError as exc:
                    passed = False
                    error = str(exc)
                if passed != expected_pass:
                    raise AssertionError(name + ' was incorrectly accepted/rejected')
                tests.append({'name': name, 'status': 'PASS', 'accepted': passed,
                              'rejection': None if passed else error})
            check('valid_original', True)
            (package / 'reports/revd_offline/new').mkdir(parents=True)
            (package / 'reports/revd_offline/new/run.json').write_text('{}')
            check('new_runtime_evidence_allowed', True)
            (package / 'source.py').write_text('value = 2\n')
            check('changed_source_rejected', False)
            (package / 'source.py').write_text('value = 1\n')
            (package / 'shadow.py').write_text('value = 3\n')
            check('unlisted_source_rejected', False)
            (package / 'shadow.py').unlink()
            check('casefold_alias_rejected', False, {**members, 'SOURCE.PY': members['source.py']})
            check('semantic_alias_rejected', False, {**members, 'a/../source.py': members['source.py']})
            check('parent_escape_rejected', False, {'../outside.py': members['source.py']})
            check('absolute_escape_rejected', False, {str((out / 'outside.py').resolve()): members['source.py']})
            (package / 'source.py').unlink()
            check('missing_member_rejected', False)
    finally:
        entry.ROOT = original
    put(out / 'result.json', {'status': 'PASS', 'checked_utc': utc(), 'tests': tests,
        'source_sha256': {str(Path(__file__).relative_to(ROOT)): sha(Path(__file__)),
                          'scripts/revd_offline_reproduce.py': sha(ROOT / 'scripts/revd_offline_reproduce.py')}})
    print(out, 'PASS', len(tests), flush=True)


if __name__ == '__main__':
    main()
