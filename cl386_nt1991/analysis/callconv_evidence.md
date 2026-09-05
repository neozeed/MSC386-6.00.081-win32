# Concrete compatibility evidence from the 1991 binary

## `CreateProcessA` / early `STARTUPINFO`

`__dospawn` at RVA `0x17762` reserves a local structure, clears exactly 14 DWORDs (`0x38` bytes), and stores `0x38` in its first DWORD. It then pushes ten `CreateProcessA` arguments and, after returning through the import thunk, executes `add esp, 0x28`.

This establishes two properties directly from the binary:

1. the startup structure used by this CRT is 56 bytes; and
2. the imported fixed-argument API is expected to use caller cleanup.

## `GetStartupInfoA`

The CRT startup helper near RVA `0x15a4a` reserves only `0x3c` bytes and passes the local buffer to the imported `GetStartupInfoA`. It later uses the DWORD at structure offset `0x34`, which corresponds to the inherited-CRT-data pointer in the common prefix of the old and current structure layouts.

A current i386 `STARTUPINFOA` is `0x44` bytes, so direct forwarding would write beyond that old local buffer.

## `RtlUnwind`

The exception helper near RVA `0x15bf6` pushes three arguments before calling the `RtlUnwind` import and then executes `add esp, 0x0c`. The compatibility DLL adapts this to the current four-argument routine by supplying a NULL fourth `ReturnValue` argument.
