@echo off
rem Requires LLVM clang + lld-link in PATH.
clang --target=i686-pc-windows-msvc -Oz -ffreestanding -fno-stack-protector -fno-builtin -c cl386_compat.c -o cl386_compat.obj
lld-link /dll /machine:x86 /nodefaultlib /entry:compat_DllMain@12 /def:cl386_compat.def /out:CL386COMPAT.DLL cl386_compat.obj
