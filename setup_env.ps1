# setup_env.ps1 — настройка окружения MSVC x64 + LLVM
# Запуск: . .\setup_env.ps1  (с точкой — чтобы переменные остались в сеансе)

$msvc_base = "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.43.34808"
$sdk_base  = "C:\Program Files (x86)\Windows Kits\10"

$env:Path    = "C:\Program Files\LLVM\bin;$msvc_base\bin\Hostx64\x64;$env:Path"
$env:INCLUDE = "$msvc_base\include;$sdk_base\Include\10.0.22621.0\ucrt;$sdk_base\Include\10.0.22621.0\um;$sdk_base\Include\10.0.22621.0\shared"
$env:LIB     = "$msvc_base\lib\x64;$sdk_base\Lib\10.0.22621.0\ucrt\x64;$sdk_base\Lib\10.0.22621.0\um\x64"

Write-Host "MSVC x64 + LLVM: cl.exe, link.exe, lib.exe, clang-format готовы" -ForegroundColor Green
