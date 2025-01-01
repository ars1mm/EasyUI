@echo off
setlocal enabledelayedexpansion

:: Default installation directory
set INSTALL_DIR=C:\Program Files\EasyUI

:: Parse command line arguments
if not "%1"=="" (
    set INSTALL_DIR=%1
)

echo Installing EasyUI to %INSTALL_DIR%...
echo.

:: Check for administrator privileges
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: This script requires administrator privileges.
    echo Please run this script as administrator.
    exit /b 1
)

:: Build the library first
call scripts\build_windows_libs.bat
if %errorlevel% neq 0 (
    echo Error: Build failed
    exit /b %errorlevel%
)

echo.
echo Creating installation directories...

:: Create installation directories
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"
if not exist "%INSTALL_DIR%\include" mkdir "%INSTALL_DIR%\include"
if not exist "%INSTALL_DIR%\lib" mkdir "%INSTALL_DIR%\lib"
if not exist "%INSTALL_DIR%\examples" mkdir "%INSTALL_DIR%\examples"

:: Copy files
echo Copying files...

:: Copy header files
xcopy /Y /Q "include\*.h" "%INSTALL_DIR%\include\"
xcopy /Y /Q "src\core\*.h" "%INSTALL_DIR%\include\core\"
xcopy /Y /Q "src\styles\*.h" "%INSTALL_DIR%\include\styles\"
xcopy /Y /Q "src\window\*.h" "%INSTALL_DIR%\include\window\"
xcopy /Y /Q "src\graphics\*.h" "%INSTALL_DIR%\include\graphics\"

:: Copy libraries
xcopy /Y /Q "libs\msvc\*.lib" "%INSTALL_DIR%\lib\"

:: Copy examples
xcopy /Y /Q "examples\*.*" "%INSTALL_DIR%\examples\"

:: Add to system PATH if not already present
echo Updating system PATH...
for /f "tokens=2*" %%a in ('reg query "HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment" /v Path ^| findstr /i "^Path"') do set CURRENT_PATH=%%b
echo %CURRENT_PATH% | findstr /i /c:"%INSTALL_DIR%\lib" >nul
if %errorlevel% neq 0 (
    setx /M PATH "%CURRENT_PATH%;%INSTALL_DIR%\lib"
    if %errorlevel% neq 0 (
        echo Warning: Failed to update system PATH
    ) else (
        echo System PATH updated successfully
    )
) else (
    echo %INSTALL_DIR%\lib already in system PATH
)

echo.
echo Installation completed successfully!
echo.
echo Installation directory: %INSTALL_DIR%
echo.
echo To use EasyUI in your projects:
echo 1. Include the header files from %INSTALL_DIR%\include
echo 2. Link against the library in %INSTALL_DIR%\lib
echo 3. Check out the examples in %INSTALL_DIR%\examples
echo.
echo Note: You may need to restart your development environment
echo      for the PATH changes to take effect.

exit /b 0
