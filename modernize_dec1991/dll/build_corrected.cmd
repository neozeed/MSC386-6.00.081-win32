@echo off
setlocal
rem Same source, with the two source-reconstruction corrections enabled:
rem   GetFileTime uses 4 args; FindNextFileA translates WIN32_FIND_DATA too.
clang --target=i686-pc-windows-msvc -Oz -ffreestanding -fno-stack-protector -fno-builtin -DDEC1991_CORRECTED=1 -c dec1991_compat.c -o dec1991_compat.obj || exit /b 1
clang --target=i686-pc-windows-msvc -c dec1991_setjmp.s -o dec1991_setjmp.obj || exit /b 1
lld-link /dll /machine:x86 /nodefaultlib /safeseh:no /entry:compat_DllMain@12 /def:dec1991_compat.def /out:DEC1991COMPAT-CORRECTED.DLL dec1991_compat.obj dec1991_setjmp.obj || exit /b 1
echo Built DEC1991COMPAT-CORRECTED.DLL.
