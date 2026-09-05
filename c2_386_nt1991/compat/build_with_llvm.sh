#!/bin/sh
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
OUT=${1:-"$HERE/../build/C2_386COMPAT.DLL"}
C_OBJ=${TMPDIR:-/tmp}/c2_386_compat.$$.obj
S_OBJ=${TMPDIR:-/tmp}/c2_386_setjmp.$$.obj
trap 'rm -f "$C_OBJ" "$S_OBJ"' EXIT
clang --target=i686-pc-windows-msvc -O2 -ffreestanding -fno-stack-protector -c "$HERE/c2_386_compat.c" -o "$C_OBJ"
clang --target=i686-pc-windows-msvc -c "$HERE/c2_386_setjmp.s" -o "$S_OBJ"
lld-link /dll /machine:x86 /entry:compat_DllMain@12 /def:"$HERE/c2_386_compat.def" /out:"$OUT" /nodefaultlib /subsystem:windows /safeseh:no "$C_OBJ" "$S_OBJ"
echo "built $OUT"
