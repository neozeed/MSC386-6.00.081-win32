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

- converts old section `PhysicalAddress` semantics to modern `VirtualSize`;
- represents `.bss` as virtual-only data;
- converts 2,184 old type-3 relocations into 12 standard HIGHLOW page blocks;
- redirects both old DLL descriptors to `CL386COMPAT.DLL`;
- leaves imported function names, compiler code, COFF symbols, line records, and debug payload intact.

The converted EXE and DLL both parse as ordinary PE32/i386 with GNU PE tooling. They have **not been executed on a Windows host in this environment**, so this is a structurally validated compatibility build rather than a claim of completed runtime testing. The remaining external runtime dependency is the compiler pass/tool set (`c1_386.exe`, `c2_386.exe`, `c3_386.exe`, linker/assembler as selected by the driver).
