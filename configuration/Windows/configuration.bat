@echo off

cmake --version >nul 2>&1

if %errorlevel%==0 (
    echo Configuration Successful!
) else (
    .\configuration\Windows\cmake-4.0.2-windows-x86_64.msi
)

pause
