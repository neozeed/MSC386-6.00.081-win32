C2_386-WIN32.EXE   - modernized PE32/i386 image
C2_386COMPAT.DLL   - ABI compatibility shim
C23_386.ERR        - original message catalogue

For use with a converted CL386 driver, copy/rename C2_386-WIN32.EXE to
C2_386.EXE in the test compiler directory. Keep the historical original safe.

This conversion is structurally validated but has not been executed on Windows
in the build environment. It requires an x86/WOW64-capable Windows runtime.
