"""Exercise the persistent runner with a local CLI stub, never a real agent."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import time

import pytest


ROOT = Path(__file__).resolve().parents[2]
PWSH = shutil.which("pwsh")
pytestmark = pytest.mark.skipif(os.name != "nt" or not PWSH, reason="Windows runner")
SCRIPTS = ("start_prototype_run.ps1", "run_prototype_worker.ps1",
           "check_prototype_run.ps1", "stop_prototype_run.ps1")


@pytest.fixture
def workspace(tmp_path):
    root = tmp_path / "执行 空间"
    (root / "scripts").mkdir(parents=True)
    (root / "work").mkdir()
    (root / ".omx").mkdir()
    for name in SCRIPTS:
        source = ROOT / "scripts" / name
        assert source.is_file(), f"Runner is missing: {name}"
        shutil.copy2(source, root / "scripts" / name)
    (root / "work" / "prototype_task.md").write_text("任务：完成点积与矩阵。", encoding="utf-8")
    return root


def run_script(root, name, *args):
    return subprocess.run([PWSH, "-NoProfile", "-File", str(root / "scripts" / name),
                           "-Workspace", str(root), *map(str, args)],
                          capture_output=True, encoding="utf-8", errors="replace", timeout=30)


def write_state(root, **updates):
    state = {"engine": "codex-cli", "workspace": str(root), "status": "STARTING",
             "pid": 0, "runner": "cmd.exe", "visible_console": True,
             "started_at": "2020-01-01T00:00:00Z"}
    state.update(updates)
    (root / ".omx" / "prototype-run.json").write_text(json.dumps(state), encoding="utf-8")


def stub(root, exit_code=0, cases=36):
    program = root / "stub.py"
    program.write_text('''import json, pathlib, sys
root=pathlib.Path(__file__).parent
payload=sys.stdin.buffer.read().decode('utf-8-sig')
(root/'received.txt').write_text(payload, encoding='utf-8')
count=root/'calls.txt'
count.write_text(str(int(count.read_text())+1 if count.exists() else 1))
assert '--ignore-user-config' in sys.argv
assert '--skip-git-repo-check' in sys.argv
assert '--dangerously-bypass-approvals-and-sandbox' in sys.argv
assert sys.argv[-1]=='-'
out=pathlib.Path(sys.argv[sys.argv.index('--output-last-message')+1])
out.write_text('stub finished', encoding='utf-8')
(root/'work'/'prototype_status.json').write_text(json.dumps({'status':'READY_FOR_REVIEW', 'numeric':True, 'dot64':True, 'ffn1':True, 'full_matrix_cases':CASES}))
print('stub round output')
sys.exit(''' .replace('CASES', str(cases)) + str(exit_code) + ')\n', encoding="utf-8")
    command = root / "stub.cmd"
    command.write_text(f'@echo off\n"{sys.executable}" "{program}" %*\nexit /b %errorlevel%\n', encoding="utf-8")
    return command


def encoder_stub(root, report):
    command = stub(root)
    program = root / 'stub.py'
    text = program.read_text(encoding='utf-8')
    marker = "(root/'work'/'prototype_status.json').write_text"
    lines = text.splitlines()
    lines = ["(root/'work'/'encoder_status.json').write_text(" 
             + repr(json.dumps(report)) + ", encoding='utf-8')" if line.startswith(marker)
             else line for line in lines]
    program.write_text('\n'.join(lines) + '\n', encoding='utf-8')
    return command


ENCODER_ARGS = ('-ReadinessFile', 'work/encoder_status.json',
                '-RequiredFields', 'task1,task2,task3,task4,task5,task6,task7',
                '-CountField', 'full_encoder_cases', '-MinimumCount', 3)


def test_formal_seven_does_not_accept_legacy_three(workspace):
    write_state(workspace)
    result = run_script(workspace, SCRIPTS[1], '-CodexBin', stub(workspace),
                        '-MaxRounds', 1, *ENCODER_ARGS)
    assert result.returncode == 2, result.stdout + result.stderr
    state = json.loads((workspace / '.omx/prototype-run.json').read_text(encoding='utf-8'))
    assert state['status'] == 'EXHAUSTED'


def test_failed_round_ready_cannot_be_consumed_by_a_later_empty_success(workspace):
    command = stub(workspace)
    program = workspace / 'stub.py'
    text = program.read_text(encoding='utf-8')
    marker = "(root/'work'/'prototype_status.json').write_text"
    text = '\n'.join('if int(count.read_text()) == 1:\n    ' + line
                     if line.startswith(marker) else line for line in text.splitlines())
    text = text.replace('sys.exit(0)', 'sys.exit(3 if int(count.read_text()) == 1 else 0)')
    program.write_text(text + '\n', encoding='utf-8')
    write_state(workspace)
    result = run_script(workspace, SCRIPTS[1], '-CodexBin', command, '-MaxRounds', 2)
    assert result.returncode == 2, result.stdout + result.stderr
    state = json.loads((workspace / '.omx/prototype-run.json').read_text(encoding='utf-8'))
    assert state['status'] == 'EXHAUSTED'


@pytest.mark.parametrize('change,accepted', [({}, True), ({'task7': False}, False),
    ({'task5': 'true'}, False), ({'task4': None}, False),
    ({'full_encoder_cases': 2}, False), ({'full_encoder_cases': True}, False),
    ({'full_encoder_cases': '3'}, False)])
def test_formal_seven_typed_readiness(workspace, change, accepted):
    report = {'status': 'READY_FOR_REVIEW', 'full_encoder_cases': 3,
              **{f'task{i}': True for i in range(1, 8)}, **change}
    write_state(workspace)
    result = run_script(workspace, SCRIPTS[1], '-CodexBin', encoder_stub(workspace, report),
                        '-MaxRounds', 1, *ENCODER_ARGS)
    assert result.returncode == (0 if accepted else 2), result.stdout + result.stderr
    state = json.loads((workspace / '.omx/prototype-run.json').read_text(encoding='utf-8'))
    assert state['status'] == ('AWAITING_REVIEW' if accepted else 'EXHAUSTED')


@pytest.mark.parametrize('arg,value', [('-ReadinessFile', '../outside.json'),
    ('-RequiredFields', 'one,one'), ('-RequiredFields', 'one;command'),
    ('-CountField', 'count;command')])
def test_readiness_configuration_rejects_invalid_input(workspace, arg, value):
    result = run_script(workspace, SCRIPTS[0], '-ValidateOnly', arg, value)
    assert result.returncode != 0
    assert not (workspace / '.omx/prototype-run.json').exists()


def test_validate_only_rejects_active_lane_and_outside_task(workspace, tmp_path):
    outside = tmp_path / "outside.md"
    outside.write_text("outside", encoding="utf-8")
    result = run_script(workspace, SCRIPTS[0], "-TaskFile", outside, "-ValidateOnly")
    assert result.returncode != 0
    assert "within" in (result.stdout + result.stderr).lower()
    write_state(workspace, pid=os.getpid(), status="RUNNING")
    result = run_script(workspace, SCRIPTS[0], "-ValidateOnly")
    assert result.returncode != 0
    assert "active" in (result.stdout + result.stderr).lower()


def test_unicode_task_and_ready_result_stop_after_one_round(workspace):
    write_state(workspace)
    result = run_script(workspace, SCRIPTS[1], "-CodexCommand", stub(workspace), "-MaxRounds", 3)
    assert result.returncode == 0, result.stdout + result.stderr
    state = json.loads((workspace / ".omx" / "prototype-run.json").read_text(encoding="utf-8-sig"))
    assert state["status"] == "AWAITING_REVIEW"
    assert state["round"] == 1
    assert (workspace / "calls.txt").read_text() == "1"
    assert "任务：完成点积与矩阵。" in (workspace / "received.txt").read_text(encoding="utf-8")
    assert "stub round output" in (workspace / ".omx" / "prototype-run.log").read_text(encoding="utf-8-sig")
    assert not (workspace / ".git").exists()


def test_failed_cli_cannot_claim_ready_and_stops_after_two_errors(workspace):
    write_state(workspace)
    result = run_script(workspace, SCRIPTS[1], "-CodexCommand", stub(workspace, 3), "-MaxRounds", 8)
    assert result.returncode != 0
    state = json.loads((workspace / ".omx" / "prototype-run.json").read_text(encoding="utf-8-sig"))
    assert state["status"] == "FAILED"
    assert state["round"] == 2
    assert (workspace / "calls.txt").read_text() == "2"


def test_incomplete_matrix_report_exhausts_without_acceptance(workspace):
    write_state(workspace)
    result = run_script(workspace, SCRIPTS[1], "-CodexBin", stub(workspace, cases=35), "-MaxRounds", 1)
    assert result.returncode == 2, result.stdout + result.stderr
    state = json.loads((workspace / ".omx" / "prototype-run.json").read_text(encoding="utf-8-sig"))
    assert state["status"] == "EXHAUSTED"


def test_validate_only_does_not_launch_or_create_run_state(workspace):
    result = run_script(workspace, SCRIPTS[0], "-ValidateOnly")
    assert result.returncode == 0, result.stdout + result.stderr
    config = json.loads(result.stdout)
    assert config["model"] == "gpt-6.1-sol"
    assert config["validation"] == "PASS"
    assert not (workspace / ".omx" / "prototype-run.json").exists()


def test_visible_cmd_runner_can_be_started_checked_and_stopped(workspace):
    result = run_script(workspace, SCRIPTS[0], "-CodexBin", stub(workspace), "-MaxRounds", 1)
    assert result.returncode == 0, result.stdout + result.stderr
    state_path = workspace / ".omx" / "prototype-run.json"
    try:
        deadline = time.monotonic() + 15
        while time.monotonic() < deadline:
            state = json.loads(state_path.read_text(encoding="utf-8-sig"))
            if state["status"] not in ("STARTING", "RUNNING"):
                break
            time.sleep(0.1)
        assert state["status"] == "AWAITING_REVIEW", state
        assert state["pid"] > 0
        assert state["visible_console"] is True
        assert Path(state["runner_cmd_file"]).is_file()
        check = run_script(workspace, SCRIPTS[2])
        assert check.returncode == 0, check.stdout + check.stderr
        assert '"runner_process_exists": true' in check.stdout
        assert '"executing": false' in check.stdout
    finally:
        stopped = run_script(workspace, SCRIPTS[3])
    assert stopped.returncode == 0, stopped.stdout + stopped.stderr
    state = json.loads(state_path.read_text(encoding="utf-8-sig"))
    assert state["status"] == "STOPPED"


def test_check_is_read_only_and_stop_refuses_unrelated_process(workspace):
    write_state(workspace, pid=os.getpid(), worker_pid=os.getpid(), status="RUNNING")
    before = (workspace / ".omx" / "prototype-run.json").read_bytes()
    result = run_script(workspace, SCRIPTS[2])
    assert result.returncode == 0, result.stdout + result.stderr
    assert (workspace / ".omx" / "prototype-run.json").read_bytes() == before
    assert '"executing": false' in result.stdout
    result = run_script(workspace, SCRIPTS[3])
    assert result.returncode != 0
    assert (workspace / ".omx" / "prototype-run.json").read_bytes() == before
