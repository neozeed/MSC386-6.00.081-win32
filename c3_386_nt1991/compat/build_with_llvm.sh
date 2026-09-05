#!/bin/sh
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
OUT=${1:-"$HERE/../build/C3_386COMPAT.DLL"}
OBJ=${TMPDIR:-/tmp}/c3_386_compat.$$.obj
trap 'rm -f "$OBJ"' EXIT
clang --target=i686-pc-windows-msvc -O2 -ffreestanding -fno-stack-protector -c "$HERE/c3_386_compat.c" -o "$OBJ"
lld-link /dll /machine:x86 /entry:compat_DllMain@12 /def:"$HERE/c3_386_compat.def" /out:"$OUT" /implib:"$HERE/../build/C3_386COMPAT.lib" /nodefaultlib /subsystem:windows /safeseh:no "$OBJ"
echo "built $OUT"
