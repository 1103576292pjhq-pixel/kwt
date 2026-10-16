[CmdletBinding()]
param([string]$Workspace = (Split-Path $PSScriptRoot -Parent))
$ErrorActionPreference = 'Stop'
$root = (Resolve-Path -LiteralPath $Workspace).Path.TrimEnd('\', '/')
$statePath = Join-Path $root '.omx/prototype-run.json'
if (-not (Test-Path -LiteralPath $statePath)) { throw 'No run record for this workspace.' }
$state = Get-Content -LiteralPath $statePath -Raw -Encoding UTF8 | ConvertFrom-Json
if ($state.engine -ne 'codex-cli' -or -not [string]::Equals([IO.Path]::GetFullPath($state.workspace).TrimEnd('\', '/'), $root, [StringComparison]::OrdinalIgnoreCase)) { throw 'Recorded workspace/engine does not match.' }
$runnerId = [int]$state.pid
if ($runnerId -le 0 -or $runnerId -eq $PID) { throw 'Recorded PID is invalid; refusing to stop.' }
$process = Get-CimInstance Win32_Process -Filter "ProcessId=$runnerId"
if ($process) {
    if (-not $state.runner_cmd_file) { throw 'Runner command file is missing; refusing unrelated process.' }
    $runnerPath = [IO.Path]::GetFullPath($state.runner_cmd_file)
    if (-not $runnerPath.StartsWith($root + [IO.Path]::DirectorySeparatorChar, [StringComparison]::OrdinalIgnoreCase) -or
        $process.Name -ne 'cmd.exe' -or $process.CommandLine.IndexOf($runnerPath, [StringComparison]::OrdinalIgnoreCase) -lt 0) {
        throw 'PID does not match this workspace CMD runner; refusing unrelated process.'
    }
    & taskkill.exe /PID $runnerId /T /F
    if ($LASTEXITCODE -ne 0) { throw 'Stopping the verified process tree failed.' }
}
$state | Add-Member -NotePropertyName status -NotePropertyValue 'STOPPED' -Force
$state | Add-Member -NotePropertyName ended_at -NotePropertyValue ([DateTime]::UtcNow.ToString('o')) -Force
$temporary = "$statePath.$([guid]::NewGuid().ToString('N')).tmp"
[IO.File]::WriteAllText($temporary, ($state | ConvertTo-Json -Depth 8), [Text.UTF8Encoding]::new($false))
Move-Item -LiteralPath $temporary -Destination $statePath -Force
$state | ConvertTo-Json -Depth 8
