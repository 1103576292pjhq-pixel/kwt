"""Exercise the real unit CLI around real pytest runs in an isolated copy."""
import importlib.util
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile

ROOT=Path(__file__).resolve().parents[3]


def run(*arguments):
    command=[sys.executable,*map(str,arguments)]
    print('COMMAND:',*command,flush=True)
    result=subprocess.run(command,cwd='/tmp',check=False)
    print('EXIT:',result.returncode,flush=True)
    if result.returncode:
        raise SystemExit(result.returncode)


with tempfile.TemporaryDirectory(prefix='prototype-unit-cli-') as folder:
    copy=Path(folder)
    files=[*ROOT.glob('numeric/*.py'),*ROOT.glob('tests/numeric/*.py'),
           ROOT/'scripts/generate_prototype_vectors.py',ROOT/'config/prototype-numeric.json',
           ROOT/'scripts/prototype_gate.py',ROOT/'scripts/run_prototype.sh',
           ROOT/'dv/ffn1/test_gate.py',ROOT/'work/numeric_handoff.json']
    for path in files:
        target=copy/path.relative_to(ROOT)
        target.parent.mkdir(parents=True,exist_ok=True)
        shutil.copy2(path,target)
    entry=copy/'scripts/prototype_gate.py'
    for group,test_path in [('numeric','tests/numeric'),('gate','dv/ffn1/test_gate.py')]:
        xml=copy/f'reports/prototype/integration-{group}.xml'
        run(entry,'unit-start','--group',group)
        # Make the isolated workspace the import root as normal python -m pytest.
        result=subprocess.run([sys.executable,'-m','pytest',test_path,'-q','-p','no:cacheprovider',
                               f'--junitxml={xml}'],cwd=copy,check=False)
        print('PYTEST EXIT:',result.returncode,flush=True)
        if result.returncode: raise SystemExit(result.returncode)
        run(entry,'unit-finish','--group',group)
    spec=importlib.util.spec_from_file_location('isolated_gate',entry)
    gate=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(gate)
    verified={group:gate.verify_unit_binding(group) for group in ['numeric','gate']}
    (ROOT/'reports/prototype/gate-hardening/unit-cli-results.json').write_text(
        json.dumps({'status':'PASS','groups':verified,'full_or_repeat_simulation_started':False},indent=2)+'\n')
    print('UNIT_CLI_BINDINGS_PASS numeric=67 gate=38',flush=True)
