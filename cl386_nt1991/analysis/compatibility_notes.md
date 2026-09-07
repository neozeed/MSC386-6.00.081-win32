# Modern Win32 compatibility strategy

## Why import renaming alone is insufficient

The 1991 executable calls fixed-argument `base.dll` APIs using a caller-cleanup convention. Example: `__dospawn` pushes ten `CreateProcessA` arguments, calls the import thunk, and then executes `add esp, 0x28`. Current 32-bit Win32 `WINAPI` calls use callee cleanup for fixed-argument APIs. A raw forwarder would therefore corrupt the stack.

The old CRT also uses a 0x38-byte `STARTUPINFO` prefix. `__dospawn` zeroes 14 DWORDs and writes `cb=0x38`; the startup code allocates only 0x3c bytes before calling `GetStartupInfoA`. Current i386 `STARTUPINFOA` is 0x44 bytes, so direct use risks stack overwrite.

The old exception helper calls `RtlUnwind` with three arguments. The modern routine has four.

## What CL386COMPAT.DLL does

- exports all 36 `base.dll` names using the **cdecl/caller-cleanup interface CL386 expects**;
- resolves current OS exports directly from loaded PE export tables (no CRT/import library dependency);
- internally calls current fixed-argument Kernel32 functions using stdcall;
- maps old `GetEnvironmentStrings` to `GetEnvironmentStringsA`;
- translates the 0x38-byte early STARTUPINFO prefix to/from a modern 0x44-byte i386 STARTUPINFOA;
- translates old 3-argument `RtlUnwind` to the modern 4-argument form with a NULL ReturnValue;
- exports a harmless `DbgPrint` stub because this executable imports it but has no reference to its thunk in `.text`.

## What CL386-WIN32.EXE changes

- expands the shortened 0xA8/9-directory prototype optional header to canonical PE32 0xE0/16-directory form;
- preserves the historical `0x00010000` ImageBase;
- converts old section `PhysicalAddress` semantics to modern `VirtualSize`;
- represents `.bss` as virtual-only data;
- converts 2,184 old type-3 relocations into 12 standard HIGHLOW page blocks while preserving the original `.reloc` mapped extent;
- redirects both old DLL descriptors to `CL386COMPAT.DLL`;
- leaves imported function names, compiler code, COFF symbols, line records, and debug payload intact.

The corrected EXE and DLL parse as ordinary PE32/i386 and are **runtime-validated on 64-bit Windows 10 build 19045.6466**. CL386 and the corrected C1/C2/C3 passes successfully compiled the multi-file `phoon` program.

The native-Windows test also exposed a converter bug in the pass executables: compacting relocation data had incorrectly shrunk `.reloc` VirtualSize and introduced 64-KB RVA holes. Wine accepted those images while Windows rejected them at `CreateProcess` with error 5. CL386 did not fail only because its relocation section remained inside one alignment unit. `tools/modernize_pe.py` now preserves the original relocation mapped extent and asserts section adjacency for consistency. See `windows10_loader_validation.md`.
