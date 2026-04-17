# build_simple.ps1
Write-Host "Building Uraken..." -ForegroundColor Green

if (Test-Path "build") { Remove-Item -Recurse -Force build }
New-Item -ItemType Directory -Path "build" | Out-Null
Set-Location build

cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if ($LASTEXITCODE -ne 0) { exit 1 }

mingw32-make
if ($LASTEXITCODE -ne 0) { exit 1 }

if (Test-Path "..\libs\SFML\bin") { Copy-Item "..\libs\SFML\bin\*.dll" . }
if (Test-Path "..\assets") { Copy-Item -Recurse "..\assets" . }

Write-Host "Done! Run .\Uraken.exe" -ForegroundColor Green
Set-Location ..