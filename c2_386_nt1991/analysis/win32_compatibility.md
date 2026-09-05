# Modern Win32 compatibility notes

## What the original image is

`C2_386.EXE` is a December 1991 transitional PE32/i386 executable. It already has a recognizable PE import table, but its relocation directory is not the released PE page-block format.

The original image imports 22 names from `base.dll` and four from `ntdll.dll`: `DbgPrint`, `RtlUnwind`, `longjmp`, and `setjmp`.

## Conversion performed

`tools/modernize_c2_386.py` performs these narrow transformations:

1. Changes preferred ImageBase from `0x00010000` to `0x00400000`.
2. Validates every active old relocation before changing it. There are 15,190 records, of which 15,184 are active type 3; all active entries validate as `stored DWORD == old ImageBase + relocation Value`.
3. Rebases each validated absolute DWORD by the ImageBase delta.
4. Converts those sites into 108 normal PE `IMAGE_BASE_RELOCATION` page blocks using `IMAGE_REL_BASED_HIGHLOW` entries.
5. Normalizes section `VirtualSize` fields and makes `.bss` virtual-only (`SizeOfRawData = 0`).
6. Points both old import descriptors at `C2_386COMPAT.DLL` without changing the compiler's IAT layout or code.

## ABI translation

The 1991 CRT calls imported fixed-argument APIs with caller cleanup (cdecl-style). Modern x86 Win32 API functions use stdcall-style callee cleanup. `C2_386COMPAT.DLL` therefore exports the old undecorated names with a cdecl surface and invokes current Kernel32 functions with the modern calling convention.

The shim also handles:

- `GetStartupInfoA`: C2's CRT allocates an old 0x38-byte STARTUPINFO prefix; the shim obtains a current structure and copies only the old prefix back.
- `RtlUnwind`: the early CRT calls a three-argument form; the shim calls the current four-argument form with a zero ReturnValue.
- `setjmp`/`longjmp`: the compiler imports these from the early `ntdll.dll`. The shim supplies a local x86 pair storing EBP, EBX, ESI, EDI, post-return ESP, return EIP, and the `FS:[0]` SEH chain in the caller-provided opaque jump buffer.
- `DbgPrint`: retained as a benign no-op compatibility export; no compiler-critical direct dependency was established during static analysis.

## Status

The generated EXE parses as an ordinary PE32/i386 Windows 4.0 console executable, and its relocation table parses as modern HIGHLOW blocks. The compatibility DLL is a normal PE32 DLL and exports every name required by the converted executable.

There is no Windows/Wine runtime in the analysis environment, so **runtime execution has not been certified**. The setjmp/longjmp bridge is the most important item to exercise on Windows because it participates in compiler recovery/error paths.
