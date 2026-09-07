C3_386 modern Win32 build

C3_386-WIN32.EXE   Corrected modern PE32/i386 image.
C3_386COMPAT.DLL   cdecl-to-modern-Win32 ABI compatibility layer.
C23_386.ERR        Shared Phase 2/3 diagnostic catalogue.
C3_386_rebuilt.EXE Exact reconstruction of the historical input, for verification only.

Copy/rename C3_386-WIN32.EXE to C3_386.EXE for the converted compiler pipeline.
Runtime validated on 64-bit Windows 10 build 19045.6466 during the optimized phoon
build. The corrected image preserves .reloc VirtualSize 0x14C00 and no longer
contains the 64-KB RVA hole that native Windows rejected with error 5.
