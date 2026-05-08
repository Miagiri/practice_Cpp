. .\setup_env.ps1                          

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
Write-Host "Build done."