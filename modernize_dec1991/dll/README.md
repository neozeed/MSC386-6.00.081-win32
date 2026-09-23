# DEC1991COMPAT.DLL source

This is the source reconstruction for the common compatibility DLL shipped
with the "universal retranslation R2" December-1991 NT C/386 toolchain.

It is descended from the original `CL386COMPAT.DLL` source and incorporates
the later LINK/COFF/CVTOMF/compiler compatibility work in one maintainable
project.

## Files

- `dec1991_compat.c` — PE export resolver and all Win32/early-NT ABI bridges.
- `dec1991_setjmp.s` — exact 24-byte 1991 `jmp_buf` setjmp/longjmp.
- `dec1991_compat.def` — all 51 exports used by the universal toolchain.
- `build_r2_exact.cmd` — rebuild with R2's runtime behavior.
- `build_corrected.cmd` — same source with two small latent adapter fixes.
- `R2_BINARY_SHA256.txt` — identifies the exact DLL that shipped in R2.

No Windows SDK or CRT is needed. LLVM clang + lld-link is sufficient.

## Why caller-cleanup wrappers exist

The December-1991 BASE.DLL ABI used by these binaries is cdecl/caller-cleanup.
Released 32-bit Win32 Kernel32 fixed-argument APIs are stdcall. The wrapper
functions therefore receive the old cdecl call and invoke the modern stdcall
target through a correctly typed function pointer.

## Special compatibility cases

### STARTUPINFOA

The early structure is 0x38 bytes. Released i386 STARTUPINFOA is 0x44 bytes.
`GetStartupInfoA` and `CreateProcessA` translate through a temporary 0x44-byte
structure.

### WIN32_FIND_DATAA

The old tools expect `cFileName` at +0x24. Released Win32 places it at +0x2c,
after two reserved DWORDs. R2 translated the returned data for FindFirstFileA.

### RtlUnwind

The old CRT passes three arguments. Released i386 NTDLL uses a four-argument
stdcall form. The bridge supplies a zero ReturnValue.

### setjmp/longjmp

The historical buffer is 0x18 bytes: EBP, EBX, ESI, EDI, ESP, EIP. The earlier
experimental seventh FS:[0] DWORD caused the COFF linker crash by overwriting
the adjacent `FirstArchive` global.

## Two source-reconstruction findings

While turning the incrementally patched R2 binary back into maintainable
source, two latent R2 adapter inconsistencies became visible:

1. The R2 GetFileTime patch duplicated three arguments, but retained C1
   `fstat.c` code pushes four.
2. FindFirstFileA performs the old/new WIN32_FIND_DATA layout translation;
   R2's later FindNextFileA patch does not.

`build_r2_exact.cmd` deliberately preserves those R2 behaviors.

`build_corrected.cmd` defines `DEC1991_CORRECTED=1` and corrects both. It is
provided separately so the source for R2 is not silently changed.

The R2 C3 `/Fa` floating-point repair is *not* in this DLL; it lives in
`modernize_dec1991_pe.py` and patches C3's missing sixth `__cfltcvt_tab`
callback inside C3 itself.
