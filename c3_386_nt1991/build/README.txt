C3_386 modern-Win32 experiment

C3_386-WIN32.EXE   Modernized/rebased transitional PE image.
C3_386COMPAT.DLL   cdecl-to-modern-Win32 ABI compatibility layer.
C23_386.ERR         Shared Phase 2/3 diagnostic catalogue.
C3_386_rebuilt.EXE Exact reconstruction of the historical input, for verification only.

To let CL386/C2 invoke the converted last pass, copy C3_386-WIN32.EXE as C3_386.EXE in a clean test directory together with C3_386COMPAT.DLL and C23_386.ERR.
The modernized pair is structurally validated but has not been executed in this Linux environment.
