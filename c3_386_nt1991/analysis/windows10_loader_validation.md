# Windows 10 loader compatibility and runtime validation

Date validated: 2026-09-06
Host reported by `ver`: Microsoft Windows 10.0.19045.6466, 64-bit

## Symptom

The first modernized CL386 driver executed successfully under both Wine and real
Windows 10, but C1_386, C2_386 and C3_386 behaved differently:

```text
CL386.EXE   -> starts normally
C1_386.EXE  -> Access is denied. (CreateProcess error 5)
C2_386.EXE  -> Access is denied. (CreateProcess error 5)
C3_386.EXE  -> Access is denied. (CreateProcess error 5)
```

Wine accepted all four, which initially hid the native-Windows loader problem.
Because error 5 was returned before any compiler-pass output, the failure was at
image mapping / process creation rather than inside compiler code or the ABI shim.

## Root cause

These December-1991 prototype PE images use `SectionAlignment = 0x10000` (64 KB).
The old relocation format stores 12-byte records.  The modernizers correctly
converted them to compact standard `IMAGE_BASE_RELOCATION` / HIGHLOW page blocks
and correctly changed the relocation *data-directory size* to the compact byte
count.  However, the first C1/C2/C3 scripts also changed the `.reloc` *section
VirtualSize* to that compact size.

That was wrong.  It shortened the mapped section enough to create 64-KB-aligned
virtual holes before `.debug`:

```text
C1  .reloc RVA 0x90000, compact VS 0x03560 -> next mapped RVA 0xA0000
    .debug actually begins                         at 0xB0000

C2  .reloc RVA 0xC0000, compact VS 0x07A5C -> next mapped RVA 0xD0000
    .debug actually begins                         at 0xF0000

C3  .reloc RVA 0x70000, compact VS 0x03878 -> next mapped RVA 0x80000
    .debug actually begins                         at 0x90000
```

CL386 escaped because its compact relocation data still occupied the same single
64-KB mapping quantum as its original relocation section.

The corrected converters therefore keep two separate notions:

* relocation **data-directory Size** = compact modern relocation bytes;
* `.reloc` **section VirtualSize** = original mapped allocation.

Correct section extents are:

```text
CL386  .reloc VirtualSize = 0x06800
C1     .reloc VirtualSize = 0x13800
C2     .reloc VirtualSize = 0x2CA00
C3     .reloc VirtualSize = 0x14C00
```

The modernization scripts now assert that each mapped section begins exactly at
the previous section's end after `SectionAlignment` rounding, and that the final
aligned section end equals `SizeOfImage`.

## Other loader cleanup retained

The successful build also keeps the historical preferred image base `0x00010000`
and expands the shortened prototype PE32 optional header from `0xA8` bytes / 9
data directories to the canonical `0xE0` bytes / 16 directories.  Directories
9..15 are explicitly zero, including the CLR runtime directory.

That header expansion also removes a misleading `file(1)` / libmagic result that
called the old executables “Mono/.Net assembly”.  They were never CLR images; a
parser assuming the later full directory array was reading bytes from the old
section table where the nonexistent CLR directory would normally reside.

## Full compiler validation

After the `.reloc` VirtualSize fix, the complete pre-release compiler pipeline was
used successfully on the Windows 10 machine.  A multi-file build of `phoon` ran:

```text
cl386 /u /w /G3 /O /c astro.c
cl386 /u /w /G3 /O /c date_p.c
cl386 /u /w /G3 /O /c phoon.c
```

The historical Microsoft 32-bit linker then linked the generated objects, warning
that it was converting OMF to COFF, and the resulting `phoon-6.00.081.exe` ran
successfully and printed its lunar-phase display.

This is therefore more than a launch test: CL386, C1, C2 and C3 all participated
in a real optimized multi-translation-unit compilation on native Windows 10/WOW64.

## This bundle

Validated modern executable: `C3_386-WIN32.EXE`

SHA-256: `1700daf68cd7ab32b875b9899bece1f59020280fe461084d14efed7ec7b5507b`
