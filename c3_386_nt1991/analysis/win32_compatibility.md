# Modern Win32 compatibility analysis

## Result

A modernized PE32 image and a dedicated compatibility DLL are included in `build/`.
The conversion is structurally validated but **not runtime-certified**, because this environment has no Windows/Wine runtime.

## Transitional PE details

- Original SHA-256: `337cbe52d9075b73948bf42512d3983b2effa3f9e23df8b2687d7e1acb6f8b23`
- Original ImageBase: `0x00010000`
- Modernized ImageBase: `0x00400000`
- Old relocation records: 7,067
- Active type-3 relocation records: 7,064
- Inactive records: 3
- Validation failures: 0
- Modern HIGHLOW page blocks: 36
- Imported names: 25 (23 from `base.dll`, 2 from `ntdll.dll`)

Every active old relocation was accepted only after confirming that the DWORD at its relocation RVA equalled `old_ImageBase + relocation.Value`.  Those absolute values were then rebased and the old record array was replaced with standard PE `IMAGE_BASE_RELOCATION` page blocks.

## Why a compatibility DLL is required

The pre-release NT CRT calls the imported fixed-argument APIs with **caller cleanup**.  The compatibility DLL exports that old cdecl-shaped surface and then calls current 32-bit KERNEL32/NTDLL entry points with the contemporary stdcall ABI.

Two nontrivial structure/API differences were confirmed directly in C3:

1. The startup code reserves `0x3c` bytes around its `GetStartupInfoA` call and expects the old 0x38-byte STARTUPINFO prefix.  `C3_386COMPAT.DLL` obtains a current 0x44-byte x86 STARTUPINFOA and copies only the compatible prefix back.
2. `__global_unwind` pushes three arguments to `RtlUnwind`, calls the import thunk, then executes `add esp,0x0c`.  The shim accepts those three old arguments and calls the current four-argument form with a zero ReturnValue.

`DbgPrint` is intentionally a no-op because its variadic ABI is not required for normal compiler output and forwarding unknown varargs would be less safe than suppressing debug-only output.

## C3-specific simplification versus C2

C3 does **not** import the early `setjmp`/`longjmp` pair that C2 required, so its compatibility DLL does not need the experimental custom nonlocal-jump implementation.

## Suggested first Windows test

Put these together in one 32-bit-Windows/WOW64-accessible directory:

```
C3_386.EXE          <- copy/rename build/C3_386-WIN32.EXE
C3_386COMPAT.DLL
C23_386.ERR
```

For a complete compiler pipeline, use the previously modernized CL386/C1/C2 executables as well.  Keep the original historical binaries elsewhere so the expected historical filenames can be used by the converted driver.
