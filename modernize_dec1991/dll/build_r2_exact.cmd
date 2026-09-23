@echo off
setlocal
rem LLVM clang + lld-link; no Windows SDK, CRT, or import libraries required.
clang --target=i686-pc-windows-msvc -Oz -ffreestanding -fno-stack-protector -fno-builtin -DDEC1991_CORRECTED=0 -c dec1991_compat.c -o dec1991_compat.obj || exit /b 1
clang --target=i686-pc-windows-msvc -c dec1991_setjmp.s -o dec1991_setjmp.obj || exit /b 1
lld-link /dll /machine:x86 /nodefaultlib /safeseh:no /entry:compat_DllMain@12 /def:dec1991_compat.def /out:DEC1991COMPAT.DLL dec1991_compat.obj dec1991_setjmp.obj || exit /b 1
echo Built DEC1991COMPAT.DLL in R2-compatible mode.
