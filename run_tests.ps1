# Uso: .\run_tests.ps1 hackerrank\01-solve-me-first
param([Parameter(Mandatory)][string]$Challenge)

$dir = Resolve-Path $Challenge
$exe = Join-Path $env:TEMP "hr_solution.exe"

if (-not (Get-Command g++ -ErrorAction SilentlyContinue)) {
  Write-Error "g++ nao encontrado. Instale MinGW/MSYS2 (ex: winget install MSYS2.MSYS2) e adicione ao PATH."
  exit 2
}

g++ -std=c++17 -w -o $exe (Join-Path $dir "solution.cpp")
if ($LASTEXITCODE -ne 0) { Write-Error "Falha na compilacao"; exit 1 }

$fail = 0
$hrOut = Join-Path $env:TEMP "hr_output_path.txt"
Get-ChildItem (Join-Path $dir "tests") -Filter *.in | Sort-Object Name | ForEach-Object {
  $expected = (Get-Content ($_.FullName -replace '\.in$', '.out') -Raw).Trim()
  $outFile = Join-Path $env:TEMP "hr_out.txt"
  Remove-Item $hrOut -ErrorAction SilentlyContinue
  $env:OUTPUT_PATH = $hrOut
  Start-Process $exe -RedirectStandardInput $_.FullName -RedirectStandardOutput $outFile -NoNewWindow -Wait
  # Desafios que escrevem em OUTPUT_PATH (template novo do HackerRank) ou em stdout
  $src = if ((Test-Path $hrOut) -and (Get-Item $hrOut).Length -gt 0) { $hrOut } else { $outFile }
  $actual = "$(Get-Content $src -Raw)".Trim()
  if ($actual -eq $expected) { Write-Host "PASS $($_.BaseName)" -ForegroundColor Green }
  else { Write-Host "FAIL $($_.BaseName): esperado '$expected', obtido '$actual'" -ForegroundColor Red; $fail++ }
}
exit $fail
