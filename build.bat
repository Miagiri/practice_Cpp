@echo off
for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath`) do set VS_ROOT=%%i

call "%VS_ROOT%\VC\Auxiliary\Build\vcvarsall.bat" x64

cl /c /Fo:linear-collections\c_version\search_l1.obj /W4 /permissive- /Od /Zi /MDd /fsanitize=address /analyze linear-collections\c_version\search_l1.c
if errorlevel 1 exit /b 1
link linear-collections\c_version\search_l1.obj /OUT:linear-collections\c_version\search_l1.exe /DEBUG
if errorlevel 1 exit /b 1

cl /c /Fo:linear-collections\cpp_version\search_l1.obj /std:c++latest /W4 /permissive- /EHsc /Od /Zi /MDd /fsanitize=address /analyze linear-collections\cpp_version\search_l1.cpp
if errorlevel 1 exit /b 1
link linear-collections\cpp_version\search_l1.obj /OUT:linear-collections\cpp_version\search_l1.exe /DEBUG
if errorlevel 1 exit /b 1

cl /c /Fo:linear-collections\c_version\sort_l2.obj /W4 /permissive- /Od /Zi /MDd /fsanitize=address /analyze linear-collections\c_version\sort_l2.c
if errorlevel 1 exit /b 1
link linear-collections\c_version\sort_l2.obj /OUT:linear-collections\c_version\sort_l2.exe /DEBUG
if errorlevel 1 exit /b 1

cl /c /Fo:linear-collections\cpp_version\sort_l2.obj /std:c++latest /W4 /permissive- /EHsc /Od /Zi /MDd /fsanitize=address /analyze linear-collections\cpp_version\sort_l2.cpp
if errorlevel 1 exit /b 1
link linear-collections\cpp_version\sort_l2.obj /OUT:linear-collections\cpp_version\sort_l2.exe /DEBUG
if errorlevel 1 exit /b 1

cl /c /Fo:linear-collections\c_version\search_l3.obj /W4 /permissive- /Od /Zi /MDd /fsanitize=address /analyze linear-collections\c_version\search_l3.c
if errorlevel 1 exit /b 1
link linear-collections\c_version\search_l3.obj /OUT:linear-collections\c_version\search_l3.exe /DEBUG
if errorlevel 1 exit /b 1

cl /c /Fo:linear-collections\cpp_version\search_l3.obj /std:c++latest /W4 /permissive- /EHsc /Od /Zi /MDd /fsanitize=address /analyze linear-collections\cpp_version\search_l3.cpp
if errorlevel 1 exit /b 1
link linear-collections\cpp_version\search_l3.obj /OUT:linear-collections\cpp_version\search_l3.exe /DEBUG
if errorlevel 1 exit /b 1

cl /c /Fo:linear-collections\c_version\sort_l4.obj /W4 /permissive- /Od /Zi /MDd /fsanitize=address /analyze linear-collections\c_version\sort_l4.c
if errorlevel 1 exit /b 1
link linear-collections\c_version\sort_l4.obj /OUT:linear-collections\c_version\sort_l4.exe /DEBUG
if errorlevel 1 exit /b 1

cl /c /Fo:linear-collections\cpp_version\sort_l4.obj /std:c++latest /W4 /permissive- /EHsc /Od /Zi /MDd /fsanitize=address /analyze linear-collections\cpp_version\sort_l4.cpp
if errorlevel 1 exit /b 1
link linear-collections\cpp_version\sort_l4.obj  /OUT:linear-collections\cpp_version\sort_l4.exe /DEBUG
if errorlevel 1 exit /b 1

cl /c /Fo:linear-collections\c_version\search_l5.obj /W4 /permissive- /Od /Zi /MDd /fsanitize=address /analyze linear-collections\c_version\search_l5.c
if errorlevel 1 exit /b 1
link linear-collections\c_version\search_l5.obj /OUT:linear-collections\c_version\search_l5.exe /DEBUG
if errorlevel 1 exit /b 1

cl /c /Fo:linear-collections\cpp_version\search_l5.obj /std:c++latest /W4 /permissive- /EHsc /Od /Zi /MDd /fsanitize=address /analyze linear-collections\cpp_version\search_l5.cpp
if errorlevel 1 exit /b 1
link linear-collections\cpp_version\search_l5.obj /OUT:linear-collections\cpp_version\search_l5.exe /DEBUG
if errorlevel 1 exit /b 1

echo Build done