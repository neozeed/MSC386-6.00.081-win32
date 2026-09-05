# Modern Win32 conversion notes

The Dec-1991 C1 image is already recognisably PE32/i386, but it predates the final PE/Win32 ABI in several important ways.

## Converted image

`build/C1_386-WIN32.EXE` retains the compiler code and data but normalises the loader-facing representation:

* preferred ImageBase moved from `0x00010000` to `0x00400000`;
* all **6646** active old type-3 absolute relocation sites were verified (`stored DWORD == old ImageBase + relocation.Value`) and adjusted by the base delta;
* the old 12-byte relocation records were converted to modern page-grouped `IMAGE_BASE_RELOCATION` / `IMAGE_REL_BASED_HIGHLOW` entries;
* obsolete COFF executable characteristics and zero `PhysicalAddress`/modern `VirtualSize` fields were normalised;
* `base.dll` and `ntdll.dll` descriptors are redirected to `C1_386COMPAT.DLL` while keeping every imported function name unchanged.

## Why a compatibility DLL is needed

The compiler's early NT CRT calls fixed-argument BASE APIs using **caller cleanup (cdecl)**. Modern i386 Win32 fixed-argument APIs are `WINAPI`/stdcall, so direct forwarding would unbalance ESP. The shim exports cdecl wrappers and internally calls the current stdcall functions.

Two concrete ABI translations are also required:

* `GetStartupInfoA`: this CRT allocates only `0x3c` bytes around the call and expects the early startup-info prefix (0x38 meaningful bytes). The shim asks modern Kernel32 for a 0x44-byte x86 `STARTUPINFOA` and copies only the old prefix back.
* `RtlUnwind`: the binary pushes three arguments and then does `add esp, 0x0c`; the current routine has a fourth `ReturnValue` argument. The shim supplies zero for it.

`DbgPrint` is imported but no direct call to its import thunk was found in the compiler text; the shim therefore provides a harmless compatibility stub.

## Validation status

The converted EXE parses as a normal PE32/i386 console executable with **6646 HIGHLOW relocations**, and the DLL parses as a PE32/i386 DLL exporting all **30 imported names** (duplicates across the two original descriptors collapse to the same export set where applicable).

This environment does **not** contain Windows/Wine, so actual process execution has not been runtime-certified here. Put `C1_386-WIN32.EXE`, `C1_386COMPAT.DLL`, and `C1_386.ERR` together. C1 is normally invoked by the compiler driver and expects its compiler intermediate/input conventions; using the modernised CL386 driver with the rest of the matching pass executables is the meaningful integration test.

SHA-256:

* original C1: `9bfb785e5b08298be94f44256812378c094e0abd0a69e66f8d1ce2ba3745b933`
* modernised C1: `f624d0b1527ca62eedf1152d300855c6427dc76c5320b978067b2748937a69bd`
* compatibility DLL: `7fddb6709d5132dca78bbaaae4545643cc9adff0b403854c483feaf624357b61`
