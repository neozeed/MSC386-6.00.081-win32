#!/bin/sh
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
OUT=${1:-"$HERE/../build/C1_386COMPAT.DLL"}
OBJ=${TMPDIR:-/tmp}/c1_386_compat.$$.obj
trap 'rm -f "$OBJ"' EXIT
clang --target=i686-pc-windows-msvc -O2 -ffreestanding -fno-stack-protector -c "$HERE/c1_386_compat.c" -o "$OBJ"
lld-link /dll /machine:x86 /entry:compat_DllMain@12 /def:"$HERE/c1_386_compat.def" /out:"$OUT" /nodefaultlib /subsystem:windows "$OBJ"
echo "built $OUT"
