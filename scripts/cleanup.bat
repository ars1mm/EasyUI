@echo off
echo Cleaning up build files...

:: Remove build directory and object files
if exist build rmdir /s /q build
if exist *.o del /f /q *.o

:: Remove CMake generated files
if exist CMakeFiles rmdir /s /q CMakeFiles
if exist CMakeCache.txt del /f /q CMakeCache.txt
if exist cmake_install.cmake del /f /q cmake_install.cmake

:: Remove generated files
if exist include\easyui_platform.h del /f /q include\easyui_platform.h
if exist easyui.pc del /f /q easyui.pc

:: Clean test build files, Visual Studio files, and CMake files recursively in tests
if exist tests\CMakeFiles rmdir /s /q tests\CMakeFiles
del /s /f /q tests\*.o 2>nul
del /s /f /q tests\*.vcxproj 2>nul
del /s /f /q tests\*.vcxproj.filters 2>nul
del /s /f /q tests\*.vcxproj.user 2>nul
del /s /f /q tests\*.sln 2>nul
del /s /f /q tests\*.suo 2>nul
del /s /f /q tests\*.user 2>nul
del /s /f /q tests\*.sdf 2>nul
del /s /f /q tests\*.db 2>nul
del /s /f /q tests\CMakeCache.txt 2>nul
del /s /f /q tests\cmake_install.cmake 2>nul
del /s /f /q tests\CTestTestfile.cmake 2>nul
del /s /f /q tests\EasyUIConfig*.cmake 2>nul
del /s /f /q tests\*.cmake 2>nul
for /d /r tests\ %%d in (Debug Release x64 x86 .vs CMakeFiles) do @if exist "%%d" rmdir /s /q "%%d"

:: Remove Visual Studio files in root
if exist *.sln del /f /q *.sln
if exist *.vcxproj del /f /q *.vcxproj
if exist *.vcxproj.* del /f /q *.vcxproj.*
if exist .vs rmdir /s /q .vs
if exist Debug rmdir /s /q Debug
if exist Release rmdir /s /q Release
if exist x64 rmdir /s /q x64
if exist x86 rmdir /s /q x86
if exist *.suo del /f /q *.suo
if exist *.user del /f /q *.user
if exist *.sdf del /f /q *.sdf
if exist *.db del /f /q *.db

echo Cleanup complete!
