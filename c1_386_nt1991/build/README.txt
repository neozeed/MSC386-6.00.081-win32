C1_386 modern Win32 conversion pair
===================================

Keep these files together:

  C1_386-WIN32.EXE
  C1_386COMPAT.DLL
  C1_386.ERR

For the historical driver, copy/rename C1_386-WIN32.EXE to C1_386.EXE.

This corrected image is runtime-validated on 64-bit Windows 10 build 19045.6466.
It participated in the complete CL386/C1/C2/C3 optimized build of phoon.  The
important native-Windows fix preserves the original 0x13800 .reloc VirtualSize
while the relocation data directory itself contains only the compact modern
HIGHLOW blocks. See ../analysis/windows10_loader_validation.md.
