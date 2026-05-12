@echo off
for /f "usebackq tokens=*" %%i in (`"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -property installationPath`) do set VS_ROOT=%%i

call "%VS_ROOT%\VC\Auxiliary\Build\vcvarsall.bat" x64

cl /c /W4 /analyze /Zi /MD linear-collections\c_version\search_l1.c
link search_l1.obj /OUT:linear-collections\c_version\search_l1.exe /DEBUG

cl /c /W4 /analyze /Zi /MD /EHsc /std:c++latest linear-collections\cpp_version\search_l1.cpp
link search_l1.obj /OUT:linear-collections\cpp_version\search_l1.exe /DEBUG

cl /c /W4 /analyze /Zi /MD linear-collections\c_version\sort_l2.c
link sort_l2.obj /OUT:linear-collections\c_version\sort_l2.exe /DEBUG

cl /c /W4 /analyze /Zi /MD /EHsc /std:c++latest linear-collections\cpp_version\sort_l2.cpp
link sort_l2.obj /OUT:linear-collections\cpp_version\sort_l2.exe /DEBUG

cl /c /W4 /analyze /Zi /MD linear-collections\c_version\search_l3.c
link search_l3.obj /OUT:linear-collections\c_version\search_l3.exe /DEBUG

cl /c /W4 /analyze /Zi /MD /EHsc /std:c++latest linear-collections\cpp_version\search_l3.cpp
link search_l3.obj /OUT:linear-collections\cpp_version\search_l3.exe /DEBUG

cl /c /W4 /analyze /Zi /MD linear-collections\c_version\sort_l4.c
link sort_l4.obj /OUT:linear-collections\c_version\sort_l4.exe /DEBUG

cl /c /W4 /analyze /Zi /MD /EHsc /std:c++latest linear-collections\cpp_version\sort_l4.cpp
link sort_l4.obj /OUT:linear-collections\cpp_version\sort_l4.exe /DEBUG

cl /c /W4 /analyze /Zi /MD linear-collections\c_version\search_l5.c
link search_l5.obj /OUT:linear-collections\c_version\search_l5.exe /DEBUG

cl /c /W4 /analyze /Zi /MD /EHsc /std:c++latest linear-collections\cpp_version\search_l5.cpp
link search_l5.obj /OUT:linear-collections\cpp_version\search_l5.exe /DEBUG

echo Build done