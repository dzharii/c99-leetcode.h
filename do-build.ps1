<#
  windows-build-release.ps1
  Usage: powershell -ExecutionPolicy Bypass -File .\windows-build-release.ps1 [-Arch x64|x86|arm64]
  Works on Windows PowerShell 5.x and PowerShell 7.x
#>

[CmdletBinding()]
param(
  [ValidateSet('x64','x86','arm64')]
  [string]$Arch = 'x64'
)

$ErrorActionPreference = 'Stop'

function Find-VsDevCmd {
  $candidates = @()
  $vswhereDefault = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
  if (Test-Path $vswhereDefault) { $candidates += $vswhereDefault }
  $vswhereInPath = Get-Command vswhere.exe -ErrorAction SilentlyContinue
  if ($vswhereInPath) { $candidates += $vswhereInPath.Path }

  foreach ($vsw in $candidates | Select-Object -Unique) {
    try {
      $installPath = & $vsw -latest -products * `
        -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 `
        -property installationPath 2>$null
      if ($installPath) {
        $devCmd = Join-Path $installPath 'Common7\Tools\VsDevCmd.bat'
        if (Test-Path $devCmd) { return $devCmd }
      }
    } catch {}
  }

  foreach ($y in '2022','2019','2017') {
    foreach ($e in 'Community','Professional','Enterprise','BuildTools') {
      foreach ($root in 'C:\Program Files','C:\Program Files (x86)') {
        $devCmd = Join-Path $root "Microsoft Visual Studio\$y\$e\Common7\Tools\VsDevCmd.bat"
        if (Test-Path $devCmd) { return $devCmd }
      }
    }
  }

  return $null
}

function Import-VSDevEnvironment {
  param(
    [Parameter(Mandatory=$true)][string]$VsDevCmd,
    [Parameter(Mandatory=$true)][string]$Arch
  )
  $cmdLine = "call `"$VsDevCmd`" -arch=$Arch && set"
  $envDump = & cmd.exe /c $cmdLine 2>$null
  if (-not $envDump) { throw "VsDevCmd.bat failed or produced no environment. Path: $VsDevCmd" }

  foreach ($line in $envDump) {
    if ($line -match '^(.*?)=(.*)$') {
      $name  = $matches[1]
      $value = $matches[2]
      if ($name -and $name -notmatch '^\s+$') {
        Set-Item -Path ("Env:$name") -Value $value -Force
      }
    }
  }
}

function Get-CLStdSwitch {
  try { $help = (& cl /? 2>&1 | Out-String) } catch { return $null }
  if ($help -match '/std:c11') { return '/std:c11' }
  if ($help -match '/std:c17') { return '/std:c17' }
  return $null
}

function Start-Fresh {
  Write-Host "NOB, GO REBUILD BUILD YOURSELF AGAIN"
  if (Test-Path .\nob.exe) {  Remove-Item -Force .\nob.exe }
}

Start-Fresh


$clPath = Get-Command cl.exe -ErrorAction SilentlyContinue
if (-not $clPath) {
  $vsDev = Find-VsDevCmd
  if (-not $vsDev) { throw "Could not find VsDevCmd.bat. Install Visual Studio Build Tools or Visual Studio with C++ workload." }
  Import-VSDevEnvironment -VsDevCmd $vsDev -Arch $Arch
  $clPath = Get-Command cl.exe -ErrorAction SilentlyContinue
  if (-not $clPath) { throw "cl.exe still not on PATH after VsDevCmd. Installation appears broken." }
}

$here = Split-Path -Parent $MyInvocation.MyCommand.Path
Push-Location $here
try {
  if (-not (Test-Path 'nob.c')) { throw "nob.c not found. Run from the awwtools folder." }

  if (-not (Test-Path 'build')) { New-Item -ItemType Directory -Path 'build' | Out-Null }

  $stdSwitch = Get-CLStdSwitch
  $args = @('/nologo','/W4','/O2','/DNDEBUG','/Fo:build\')
  if ($stdSwitch) { $args += $stdSwitch }
  $args += @('/Fe:nob.exe','nob.c')

  & cl @args
  if ($LASTEXITCODE -ne 0) {
    if ($stdSwitch) {
      & cl '/nologo','/W4','/O2','/DNDEBUG','/Fo:build\','/Fe:nob.exe','nob.c'
      if ($LASTEXITCODE -ne 0) { throw "Failed to compile nob.c with cl." }
    } else {
      throw "Failed to compile nob.c with cl."
    }
  }

  & .\nob.exe
  if ($LASTEXITCODE -ne 0) { throw "nob.exe build step failed." }

  Write-Host "Success: built test executables in 'build' folder."
}
finally {
  Pop-Location
}

