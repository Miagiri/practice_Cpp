@echo off 
for /f "usebackq tokens=*" %%i in (`""%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"" -latest -property installationPath`) do set VS_ROOT=%%i
call "%VS_ROOT%\VC\Auxiliary\Build\vcvarsall.bat" x64
set PATH=%PATH%;C:\Program Files\Far Manager
start "" Far.exe
