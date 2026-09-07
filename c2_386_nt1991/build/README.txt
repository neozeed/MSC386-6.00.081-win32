C2_386-WIN32.EXE   - corrected modern PE32/i386 image
C2_386COMPAT.DLL   - ABI compatibility shim
C23_386.ERR        - original message catalogue

For use with the converted CL386 driver, copy/rename C2_386-WIN32.EXE to
C2_386.EXE in the test compiler directory. Keep the historical original safe.

Runtime validated on 64-bit Windows 10 build 19045.6466 as part of the complete
optimized phoon build. The corrected image preserves .reloc VirtualSize 0x2CA00;
shrinking it to the compact relocation payload caused native CreateProcess to
return ERROR_ACCESS_DENIED even though Wine accepted the image.
