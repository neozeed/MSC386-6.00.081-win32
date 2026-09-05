C1_386 modern Win32 conversion pair
===================================

Keep these files together:

  C1_386-WIN32.EXE
  C1_386COMPAT.DLL
  C1_386.ERR

C1_386 is compiler Pass 1, not normally a standalone user-facing compiler.
The useful test is to place it in the matching toolchain and have the
modernised CL386 driver invoke it with the original compiler pass arguments.

The EXE has been structurally converted and validated as PE32/i386, but this
bundle was produced in a non-Windows environment without Wine, so execution on
Windows has not been runtime-certified here.
