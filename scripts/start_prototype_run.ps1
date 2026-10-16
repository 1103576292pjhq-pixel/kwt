[CmdletBinding()]
param(
    [string]$Workspace = (Split-Path $PSScriptRoot -Parent),
    [string]$TaskFile = 'work/prototype_task.md',
    [string]$ReadinessFile = 'work/prototype_status.json',
    [string]$RequiredFields = 'numeric,dot64,ffn1',
    [string]$CountField = 'full_matrix_cases',
    [ValidateRange(1, 1000000)][int]$MinimumCount = 36,
    [ValidateRange(1, 100)][int]$MaxRounds = 8,
    [string]$Model = 'gpt-6.1-sol',
    [string]$CodexBin = 'C:\Users\11035\AppData\Local\OpenAI\Codex\bin\2e5e00daee91c61d\codex.exe',
    [switch]$ValidateOnly
)
$ErrorActionPreference = 'Stop'
$utf8 = [System.Text.UTF8Encoding]::new($false)
$root = (Resolve-Path -LiteralPath $Workspace).Path.TrimEnd('\', '/')
if (-not [IO.Path]::IsPathRooted($TaskFile)) { $TaskFile = Join-Path $root $TaskFile }
$taskPath = (Resolve-Path -LiteralPath $TaskFile).Path
if (-not [IO.Path]::IsPathRooted($ReadinessFile)) { $ReadinessFile = Join-Path $root $ReadinessFile }
$reportPath = [IO.Path]::GetFullPath($ReadinessFile)
if (-not $reportPath.StartsWith($root + [IO.Path]::DirectorySeparatorChar, [StringComparison]::OrdinalIgnoreCase)) {
    throw 'ReadinessFile must be within the selected workspace.'
}
if ($RequiredFields -notmatch '^[A-Za-z_][A-Za-z0-9_]*(,[A-Za-z_][A-Za-z0-9_]*)*$' -or
    $CountField -notmatch '^[A-Za-z_][A-Za-z0-9_]*$' -or
    @($RequiredFields.Split(',') | Select-Object -Unique).Count -ne $RequiredFields.Split(',').Count) {
    throw 'Readiness fields must be unique comma-separated identifiers.'
}
if (-not $taskPath.StartsWith($root + [IO.Path]::DirectorySeparatorChar, [StringComparison]::OrdinalIgnoreCase)) {
    throw 'TaskFile must be within the selected workspace.'
}
if ($root -match '[%"\r\n]' -or $taskPath -match '[%"\r\n]' -or $reportPath -match '[%"\r\n]' -or $Model -notmatch '^[a-zA-Z0-9_.-]+$') {
    throw 'Paths/model contain unsupported CMD characters.'
}
$statePath = Join-Path $root '.omx/prototype-run.json'
if (Test-Path -LiteralPath $statePath) {
    $oldState = Get-Content -LiteralPath $statePath -Raw -Encoding UTF8 | ConvertFrom-Json
    if ($oldState.status -in @('STARTING', 'RUNNING')) {
        throw 'An active or unfinished lane exists. Check or stop this workspace before starting another.'
    }
}
$worker = Join-Path $root 'scripts/run_prototype_worker.ps1'
if (-not (Test-Path -LiteralPath $worker)) { throw 'Worker script is missing.' }
$pwshPath = (Get-Command pwsh.exe -ErrorAction Stop).Source
$codexPath = (Get-Command $CodexBin -ErrorAction Stop).Source
if ($ValidateOnly) {
    [ordered]@{ workspace=$root; task_file=$taskPath; model=$Model; rounds=$MaxRounds;
        readiness_file=$reportPath; required_fields=$RequiredFields; count_field=$CountField; minimum_count=$MinimumCount; validation='PASS' } | ConvertTo-Json
    exit 0
}
$taskDir = Join-Path $root '.omx/state/tasks'
New-Item -ItemType Directory -Path $taskDir -Force | Out-Null
$runId = [DateTime]::UtcNow.ToString('yyyyMMdd-HHmmss-fff')
$runnerPath = Join-Path $taskDir "prototype-runner-$runId.cmd"
$lines = @('@echo off', 'chcp 65001 >nul', 'title KWT Prototype - Codex CLI',
    "cd /d `"$root`"", 'echo KWT Prototype Codex CLI Runner',
    "echo Workspace: $root", "echo Task file: $taskPath", "echo Model: $Model", "echo Rounds: $MaxRounds",
    "`"$pwshPath`" -NoLogo -NoProfile -File `"$worker`" -Workspace `"$root`" -TaskFile `"$taskPath`" -MaxRounds $MaxRounds -Model $Model -CodexBin `"$codexPath`" -ReadinessFile `"$reportPath`" -RequiredFields `"$RequiredFields`" -CountField $CountField -MinimumCount $MinimumCount",
    'echo Worker exit code: %errorlevel%', "echo State: $statePath")
[IO.File]::WriteAllText($runnerPath, (($lines -join "`r`n") + "`r`n"), $utf8)
$initialState = [ordered]@{ engine='codex-cli'; runner='cmd.exe'; visible_console=$true; runner_cmd_file=$runnerPath;
    pid=0; workspace=$root; task_file=$taskPath; model=$Model; rounds=$MaxRounds; round=0;
    readiness_file=$reportPath; required_fields=$RequiredFields; count_field=$CountField; minimum_count=$MinimumCount;
    run_id=$runId; status='STARTING'; started_at=[DateTime]::UtcNow.ToString('o') }
if (Test-Path -LiteralPath $statePath) {
    $historyDir = Join-Path $root ".omx/history/$runId"
    New-Item -ItemType Directory -Path $historyDir -Force | Out-Null
    Copy-Item -LiteralPath $statePath -Destination (Join-Path $historyDir 'previous-run.json')
    $previousLog = Join-Path $root '.omx/prototype-run.log'
    if (Test-Path -LiteralPath $previousLog) {
        Copy-Item -LiteralPath $previousLog -Destination (Join-Path $historyDir 'previous-run.log')
        [IO.File]::WriteAllText($previousLog, '', $utf8)
    }
}
$temporary = "$statePath.$([guid]::NewGuid().ToString('N')).tmp"
[IO.File]::WriteAllText($temporary, ($initialState | ConvertTo-Json -Depth 8), $utf8)
Move-Item -LiteralPath $temporary -Destination $statePath -Force
try {
    $process = Start-Process -FilePath $env:ComSpec -ArgumentList "/d /k `"`"$runnerPath`"`"" -WorkingDirectory $root -WindowStyle Normal -PassThru
    $current = Get-Content -LiteralPath $statePath -Raw -Encoding UTF8 | ConvertFrom-Json
    $current.pid = $process.Id
    $temporary = "$statePath.$([guid]::NewGuid().ToString('N')).tmp"
    [IO.File]::WriteAllText($temporary, ($current | ConvertTo-Json -Depth 8), $utf8)
    Move-Item -LiteralPath $temporary -Destination $statePath -Force
    $current | ConvertTo-Json -Depth 8
} catch {
    $initialState.status = 'FAILED'
    $initialState.error = $_.Exception.Message
    [IO.File]::WriteAllText($statePath, ($initialState | ConvertTo-Json -Depth 8), $utf8)
    throw
}
