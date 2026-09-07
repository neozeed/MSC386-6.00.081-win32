# Modern Win32 compatibility notes

## What the original image is

`C2_386.EXE` is a December 1991 transitional PE32/i386 executable. It already has a recognizable PE import table, but its relocation directory is not the released PE page-block format.

The original image imports 22 names from `base.dll` and four from `ntdll.dll`: `DbgPrint`, `RtlUnwind`, `longjmp`, and `setjmp`.

## Conversion performed

`tools/modernize_c2_386.py` performs these narrow transformations:

1. Preserves the historical preferred ImageBase `0x00010000`.
2. Expands the shortened 0xA8/9-directory prototype optional header to canonical PE32 0xE0/16-directory form, explicitly zeroing the later directories including CLR.
3. Validates all 15,184 active type-3 relocations as `stored DWORD == ImageBase + relocation Value`.
4. Converts those sites into 108 normal PE `IMAGE_BASE_RELOCATION` page blocks using `IMAGE_REL_BASED_HIGHLOW` entries.
5. Keeps the relocation data-directory size at the compact modern byte count while preserving `.reloc` section VirtualSize at the original `0x2CA00` mapped extent.
6. Normalizes section `VirtualSize` fields and makes `.bss` virtual-only (`SizeOfRawData = 0`).
7. Points both old import descriptors at `C2_386COMPAT.DLL` without changing the compiler's IAT layout or code.

## ABI translation

The 1991 CRT calls imported fixed-argument APIs with caller cleanup (cdecl-style). Modern x86 Win32 API functions use stdcall-style callee cleanup. `C2_386COMPAT.DLL` therefore exports the old undecorated names with a cdecl surface and invokes current Kernel32 functions with the modern calling convention.

The shim also handles:

- `GetStartupInfoA`: C2's CRT allocates an old 0x38-byte STARTUPINFO prefix; the shim obtains a current structure and copies only the old prefix back.
- `RtlUnwind`: the early CRT calls a three-argument form; the shim calls the current four-argument form with a zero ReturnValue.
- `setjmp`/`longjmp`: the compiler imports these from the early `ntdll.dll`. The shim supplies a local x86 pair storing EBP, EBX, ESI, EDI, post-return ESP, return EIP, and the `FS:[0]` SEH chain in the caller-provided opaque jump buffer.
- `DbgPrint`: retained as a benign no-op compatibility export; no compiler-critical direct dependency was established during static analysis.

## Status

The corrected EXE parses as an ordinary PE32/i386 Windows 4.0 console executable and the compatibility DLL exports every required name.

Runtime testing on **64-bit Windows 10 build 19045.6466** is successful.  The earlier converter made `.reloc` VirtualSize equal to the compact relocation byte count (`0x7A5C`), which caused two 64-KB virtual holes before `.debug`; Wine accepted the image but native Windows rejected it at `CreateProcess` with error 5.  Restoring `.reloc` VirtualSize to `0x2CA00` fixed the loader failure.

C2 then participated successfully in the full optimized CL386/C1/C2/C3 compilation of the multi-file `phoon` program.  See `windows10_loader_validation.md`.

SHA-256 of corrected `build/C2_386-WIN32.EXE`: `162e57282ae686d184bcfc32e9638762ceebb10bd1e60480c1ca90572ba260be`.
