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
    [Alias('CodexCommand')][string]$CodexBin = 'C:\Users\11035\AppData\Local\OpenAI\Codex\bin\2e5e00daee91c61d\codex.exe'
)
$ErrorActionPreference = 'Stop'
$utf8 = [System.Text.UTF8Encoding]::new($false)
$OutputEncoding = $utf8
[Console]::OutputEncoding = $utf8
if (Test-Path variable:PSNativeCommandUseErrorActionPreference) { $PSNativeCommandUseErrorActionPreference = $false }
$root = (Resolve-Path -LiteralPath $Workspace).Path.TrimEnd('\', '/')
Set-Location -LiteralPath $root
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
$statePath = Join-Path $root '.omx/prototype-run.json'
$logPath = Join-Path $root '.omx/prototype-run.log'
$roundDir = Join-Path $root '.omx/state/tasks'
New-Item -ItemType Directory -Path $roundDir -Force | Out-Null
$workerStarted = [DateTime]::UtcNow
$workerRunId = $workerStarted.ToString('yyyyMMdd-HHmmss-fff')
function Update-State([hashtable]$Changes) {
    $current = Get-Content -LiteralPath $statePath -Raw -Encoding UTF8 | ConvertFrom-Json
    if (-not [string]::Equals([IO.Path]::GetFullPath($current.workspace).TrimEnd('\', '/'), $root, [StringComparison]::OrdinalIgnoreCase)) {
        throw 'Recorded workspace does not match this worker.'
    }
    foreach ($key in $Changes.Keys) { $current | Add-Member -NotePropertyName $key -NotePropertyValue $Changes[$key] -Force }
    $temporary = "$statePath.$([guid]::NewGuid().ToString('N')).tmp"
    [IO.File]::WriteAllText($temporary, ($current | ConvertTo-Json -Depth 8), $utf8)
    Move-Item -LiteralPath $temporary -Destination $statePath -Force
}
function Write-RunLog([string]$Message) {
    $entry = '[{0}] {1}' -f [DateTime]::UtcNow.ToString('o'), $Message
    [IO.File]::AppendAllText($logPath, $entry + [Environment]::NewLine, $utf8)
    Write-Host $entry
}
if (-not (Test-Path -LiteralPath $statePath)) { throw 'Start the runner before invoking its worker.' }
# Give start enough time to record the visible CMD PID before worker state changes.
for ($attempt = 0; $attempt -lt 20; $attempt++) {
    $startingState = Get-Content -LiteralPath $statePath -Raw -Encoding UTF8 | ConvertFrom-Json
    if ([int]$startingState.pid -gt 0) { break }
    Start-Sleep -Milliseconds 100
}
Update-State @{ status='RUNNING'; worker_pid=$PID; worker_started_at=$workerStarted.ToString('o') }
$errorsInARow = 0
try {
    for ($round = 1; $round -le $MaxRounds; $round++) {
        $lastPath = Join-Path $roundDir "prototype-$workerRunId-round-$round-last.txt"
        $roundLog = Join-Path $roundDir "prototype-$workerRunId-round-$round.log"
        $roundStarted = [DateTime]::UtcNow
        Update-State @{ round=$round; round_started_at=$roundStarted.ToString('o') }
        Write-RunLog "Round $round of $MaxRounds started."
        $taskText = [IO.File]::ReadAllText($taskPath, $utf8)
        if ($round -gt 1) {
            $taskText += "`n`nContinuation round $round. Inspect existing files, work/STATUS.md and previous run logs. Continue unfinished authorized work; preserve valid changes. Do not start nested persistent runners or initialize/commit/push Git."
        }
        $arguments = @('exec', '--ignore-user-config', '--skip-git-repo-check', '--dangerously-bypass-approvals-and-sandbox',
            '--model', $Model, '-c', 'model_reasoning_effort=xhigh', '--color', 'never', '--output-last-message', $lastPath, '-')
        $exitCode = 1
        $ErrorActionPreference = 'Continue'
        try {
            $taskText | & $CodexBin @arguments 2>&1 | Tee-Object -FilePath $roundLog | Tee-Object -FilePath $logPath -Append | ForEach-Object { Write-Host $_ }
            if ($null -ne $LASTEXITCODE) { $exitCode = [int]$LASTEXITCODE }
        } catch {
            Write-RunLog $_.Exception.Message
        } finally { $ErrorActionPreference = 'Stop' }
        Update-State @{ exit_code=$exitCode; round_finished_at=[DateTime]::UtcNow.ToString('o') }
        Write-RunLog "Round $round ended with exit code $exitCode."
        if ($exitCode -ne 0) {
            $errorsInARow++
            if ($errorsInARow -ge 2) {
                Update-State @{ status='FAILED'; ended_at=[DateTime]::UtcNow.ToString('o'); error='Two consecutive CLI failures.' }
                exit $exitCode
            }
            continue
        }
        $errorsInARow = 0
        if ((Test-Path -LiteralPath $reportPath) -and (Get-Item -LiteralPath $reportPath).LastWriteTimeUtc -ge $roundStarted) {
            try {
                $report = Get-Content -LiteralPath $reportPath -Raw -Encoding UTF8 | ConvertFrom-Json
                $ready = $report.status -eq 'READY_FOR_REVIEW'
                foreach ($key in $RequiredFields.Split(',')) { $ready = $ready -and ($report.$key -is [bool]) -and $report.$key }
                $ready = $ready -and ($report.$CountField -is [long] -or $report.$CountField -is [int]) -and $report.$CountField -ge $MinimumCount
                if ($ready) {
                    Update-State @{ status='AWAITING_REVIEW'; ended_at=[DateTime]::UtcNow.ToString('o') }
                    Write-RunLog 'Prototype evidence is ready for independent review; this is not final acceptance.'
                    exit 0
                }
            } catch { Write-RunLog "Readiness report is invalid: $($_.Exception.Message)" }
        }
    }
    Update-State @{ status='EXHAUSTED'; ended_at=[DateTime]::UtcNow.ToString('o') }
    Write-RunLog 'Round budget exhausted; work remains subject to review.'
    exit 2
} catch {
    Update-State @{ status='FAILED'; ended_at=[DateTime]::UtcNow.ToString('o'); error=$_.Exception.Message }
    Write-RunLog $_.Exception.Message
    exit 1
}
