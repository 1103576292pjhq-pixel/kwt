[CmdletBinding()]
param([string]$Workspace = (Split-Path $PSScriptRoot -Parent), [ValidateRange(1, 100)][int]$Tail = 15)
$ErrorActionPreference = 'Stop'
$root = (Resolve-Path -LiteralPath $Workspace).Path.TrimEnd('\', '/')
$statePath = Join-Path $root '.omx/prototype-run.json'
if (-not (Test-Path -LiteralPath $statePath)) { Write-Output 'No run record for this workspace.'; exit 0 }
$state = Get-Content -LiteralPath $statePath -Raw -Encoding UTF8 | ConvertFrom-Json
if (-not [string]::Equals([IO.Path]::GetFullPath($state.workspace).TrimEnd('\', '/'), $root, [StringComparison]::OrdinalIgnoreCase)) { throw 'Recorded workspace does not match.' }
$runnerAlive = $null -ne (Get-Process -Id ([int]$state.pid) -ErrorAction SilentlyContinue)
$workerAlive = $false
if ($state.worker_pid) { $workerAlive = $null -ne (Get-Process -Id ([int]$state.worker_pid) -ErrorAction SilentlyContinue) }
$runnerIdentity = $false
$workerIdentity = $false
if ($runnerAlive -and $state.runner_cmd_file) {
    $runnerInfo = Get-CimInstance Win32_Process -Filter "ProcessId=$([int]$state.pid)" -ErrorAction SilentlyContinue
    $runnerIdentity = $null -ne $runnerInfo -and $runnerInfo.Name -eq 'cmd.exe' -and
        $runnerInfo.CommandLine -and $runnerInfo.CommandLine.IndexOf([string]$state.runner_cmd_file, [StringComparison]::OrdinalIgnoreCase) -ge 0
}
if ($workerAlive -and $runnerIdentity) {
    $workerInfo = Get-CimInstance Win32_Process -Filter "ProcessId=$([int]$state.worker_pid)" -ErrorAction SilentlyContinue
    $workerPath = Join-Path $root 'scripts/run_prototype_worker.ps1'
    $workerIdentity = $null -ne $workerInfo -and $workerInfo.Name -in @('pwsh.exe', 'powershell.exe') -and
        $workerInfo.ParentProcessId -eq [int]$state.pid -and $workerInfo.CommandLine -and
        $workerInfo.CommandLine.IndexOf($workerPath, [StringComparison]::OrdinalIgnoreCase) -ge 0 -and
        $workerInfo.CommandLine.IndexOf($root, [StringComparison]::OrdinalIgnoreCase) -ge 0
}
$logPath = Join-Path $root '.omx/prototype-run.log'
if ($state.worker_started_at -and $state.round) {
    $workerStamp = ([datetime]$state.worker_started_at).ToUniversalTime().ToString('yyyyMMdd-HHmmss-fff')
    $roundLog = Join-Path $root ".omx/state/tasks/prototype-$workerStamp-round-$($state.round).log"
    if (Test-Path -LiteralPath $roundLog) { $logPath = $roundLog }
}
[ordered]@{ state=$state; runner_process_exists=$runnerAlive; worker_process_exists=$workerAlive;
    runner_identity_matches=[bool]$runnerIdentity; worker_identity_matches=[bool]$workerIdentity;
    executing=($state.status -eq 'RUNNING' -and $workerIdentity); progress_log_source=$logPath } | ConvertTo-Json -Depth 10
if (Test-Path -LiteralPath $logPath) { Get-Content -LiteralPath $logPath -Encoding UTF8 -Tail $Tail }
