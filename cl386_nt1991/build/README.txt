CL386-WIN32.EXE + CL386COMPAT.DLL
=================================

Corrected modern PE32/i386 conversion of the December-1991 NT compiler driver.
Runtime validated on 64-bit Windows 10 build 19045.6466 with corrected C1/C2/C3
passes; the complete toolchain successfully compiled and linked phoon.

The EXE retains ImageBase 0x00010000, uses a canonical 0xE0 PE32 optional header,
standard HIGHLOW relocations, and the original 0x6800 .reloc mapped extent.
See ../analysis/windows10_loader_validation.md.
