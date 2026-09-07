# Modern Win32 conversion notes

The Dec-1991 C1 image is already recognisably PE32/i386, but it predates the final PE/Win32 ABI in several important ways.

## Converted image

`build/C1_386-WIN32.EXE` retains the compiler code and data but normalises the loader-facing representation:

* historical preferred ImageBase `0x00010000` is preserved;
* all **6646** active old type-3 absolute relocation sites were verified (`stored DWORD == ImageBase + relocation.Value`);
* the old 12-byte relocation records were converted to modern page-grouped `IMAGE_BASE_RELOCATION` / `IMAGE_REL_BASED_HIGHLOW` entries;
* the shortened 0xA8/9-directory prototype optional header is expanded to canonical 0xE0/16-directory PE32 form;
* obsolete COFF executable characteristics and zero `PhysicalAddress`/modern `VirtualSize` fields were normalised;
* the compact relocation directory is kept, but `.reloc` VirtualSize remains the original `0x13800` mapping extent so no 64-KB RVA hole is created before `.debug`;
* `base.dll` and `ntdll.dll` descriptors are redirected to `C1_386COMPAT.DLL` while keeping every imported function name unchanged.

## Why a compatibility DLL is needed

The compiler's early NT CRT calls fixed-argument BASE APIs using **caller cleanup (cdecl)**. Modern i386 Win32 fixed-argument APIs are `WINAPI`/stdcall, so direct forwarding would unbalance ESP. The shim exports cdecl wrappers and internally calls the current stdcall functions.

Two concrete ABI translations are also required:

* `GetStartupInfoA`: this CRT allocates only `0x3c` bytes around the call and expects the early startup-info prefix (0x38 meaningful bytes). The shim asks modern Kernel32 for a 0x44-byte x86 `STARTUPINFOA` and copies only the old prefix back.
* `RtlUnwind`: the binary pushes three arguments and then does `add esp, 0x0c`; the current routine has a fourth `ReturnValue` argument. The shim supplies zero for it.

`DbgPrint` is imported but no direct call to its import thunk was found in the compiler text; the shim therefore provides a harmless compatibility stub.

## Validation status

The corrected EXE parses as a normal PE32/i386 console executable with **6646 HIGHLOW relocations**, and the DLL parses as a PE32/i386 DLL exporting all **30 imported names**.

It is also **runtime-certified on 64-bit Windows 10 build 19045.6466** as part of the complete compiler pipeline.  The first converted C1 image was rejected by native Windows with `Access is denied` / error 5 because shrinking `.reloc` VirtualSize to the compact relocation payload created a 64-KB virtual hole before `.debug`; Wine had accepted that malformed mapping.  Preserving the original `.reloc` mapped extent fixed the native loader failure.

The complete CL386/C1/C2/C3 toolchain then compiled and linked the multi-file `phoon` program successfully, and the resulting executable ran correctly.  See `windows10_loader_validation.md`.

SHA-256:

* original C1: `9bfb785e5b08298be94f44256812378c094e0abd0a69e66f8d1ce2ba3745b933`
* corrected modernised C1: `df9d1fc72958712276d66b4d19529690ca4712a7540f5099e39800f99ba80ed7`
* compatibility DLL: `7fddb6709d5132dca78bbaaae4545643cc9adff0b403854c483feaf624357b61`
