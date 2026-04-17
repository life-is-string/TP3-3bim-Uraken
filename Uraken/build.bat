@echo off
echo ========================================
echo    Building Uraken Project
echo ========================================
echo.

powershell -ExecutionPolicy Bypass -File build.ps1

echo ========================================
echo    Build successful! Starting game...
echo ========================================
cd build
start "" "Uraken.exe"
cd ..