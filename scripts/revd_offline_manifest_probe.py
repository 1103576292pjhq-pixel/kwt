"""Check the threaded integrity reader against an actual old staging tree."""
from pathlib import Path
import sys
import time
sys.dont_write_bytecode = True
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))
from scripts.revd_offline_common import put, sha, run_id, utc
from scripts.revd_offline_reproduce import manifest_check


def main():
    stage = (ROOT / sys.argv[1]).resolve()
    if (ROOT / 'work/revd_offline_20261017/package_build').resolve() not in stage.parents:
        raise ValueError('not an actual local staging tree')
    out = ROOT / 'reports/revd_offline/package_manifest_tests' / ('full-tree-' + run_id())
    out.mkdir(parents=True, exist_ok=False)
    start = time.monotonic()
    result = manifest_check(stage, allow_runtime=False)
    result.update(seconds=time.monotonic() - start, checked_utc=utc(),
        stage=str(stage.relative_to(ROOT)),
        checker_sha256=sha(ROOT / 'scripts/revd_offline_reproduce.py'),
        scope='Threaded manifest algorithm on a real prior stage; not final package reproduction or publication approval.')
    put(out / 'result.json', result)
    print(out, result, flush=True)


if __name__ == '__main__':
    main()
