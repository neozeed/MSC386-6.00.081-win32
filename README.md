# Microsoft C/386 6.00.081 for modern Win32

A recovered and modernized **December 1991 pre-release Windows NT build of the Microsoft 386 C Compiler**, converted to run on modern 32-bit Win32 / WOW64 while preserving the original compiler machinery.

This repository contains reversible analysis and working modern-Windows conversions of:

```text
CL386.EXE   compiler driver
C1_386.EXE  C front end
C2_386.EXE  optimizer / code generator
C3_386.EXE  final code / OMF object generation
```

These are not reimplementations of the compiler.

The actual 1991 compiler code is still doing the compiling.

## It works

The converted compiler has been tested successfully on:

```text
Windows 10 x64
10.0.19045.6466
```

under WOW64, as well as under Wine.

As a regression test, the complete compiler was used to build the multi-file `phoon` program with optimization enabled:

```text
C:\cl386-research\proj\phoon>nmake

Microsoft (R) Program Maintenance Utility Version 1.40

    cl386 /u /w /G3 /O /c astro.c

Microsoft (R) Microsoft 386 C Compiler. Version 6.00.081
Copyright (c) Microsoft Corp 1984-1991. All rights reserved.

astro.c

    cl386 /u /w /G3 /O /c date_p.c
    cl386 /u /w /G3 /O /c phoon.c

    link -out:phoon-6.00.081.exe astro.obj date_p.obj phoon.obj \
         libc.lib kernel32.lib oldnames.lib

Microsoft (R) 32-Bit Executable Linker Version 1.00
Copyright (C) Microsoft Corp 1992-93. All rights reserved.

astro.obj : warning LNK4033: converting object format from OMF to COFF
```

The resulting executable runs correctly:

```text
                 .----
             .--'
          .-'   .
       .-'@   @@@
      /@@@  @@@@
    ./    o @@@
   /@@  o   @@
  /@@@@   .
  |@@@@@
 /@@@@@  O  `    Last Quarter +
 | @@@@    --
 |@ @@@
 |       @@
 \  . @
  |      @@
  \     @@@@
   \  o  @@
    `\     .
      \
       `-.   o
          `-.   /
             `--.
                 `----
```

So the working path is genuinely:

```text
              December 1991 compiler

                       C source
                          |
                          v
                     CL386.EXE
                          |
             +------------+------------+
             |            |            |
             v            v            v
         C1_386.EXE -> C2_386.EXE -> C3_386.EXE
                                      |
                                      v
                                  OMF .OBJ
                                      |
                                      v
                              historical LINK
                                      |
                                      v
                                  Win32 EXE
```

## What is this compiler?

`6.00.081` appears to come from the very early Windows NT development period, the December 1991 Pre-Release.

The files are timestamped **11 December 1991**, long before the July 1993 release of Windows NT 3.1.

Although recognizably PE/i386 executables, they use several prototype or transitional conventions which differ from the final Win32 ABI.

Among the surviving information in the binaries are:

- COFF symbol tables
- original source filenames
- COFF source line records
- internal compiler function names
- diagnostic message references
- early NT import tables
- an early relocation representation

This makes them unusually interesting artifacts for studying both the Microsoft C compiler and the development of Windows NT itself.

## Why didn't they run on modern Windows?

The original binaries target a very early NT userspace.

They import functions from early versions of:

```text
BASE.DLL
NTDLL.DLL
```

and expect structures, calling conventions and APIs which no longer exactly match current Win32.

The conversions in this repository therefore preserve the original compiler code while adapting the executable container and providing small compatibility DLLs for the obsolete NT interfaces.

Among other things, the conversion:

- converts the prototype relocation representation to normal PE `HIGHLOW` relocations;
- expands the shortened prototype PE optional header into canonical PE32 form;
- preserves the original `0x00010000` image base;
- normalizes section metadata;
- redirects obsolete early-NT imports through compatibility DLLs;
- translates several early API structures/calling conventions to current Win32.

### The Wine vs Windows loader bug

During development, the converted compiler initially worked perfectly under Wine but failed on actual Windows 10:

```text
--- CL386.EXE ---

Microsoft (R) Microsoft 386 C Compiler. Version 6.00.081

--- C1_386.EXE ---

Access is denied.
exit code: 5

--- C2_386.EXE ---

Access is denied.
exit code: 5

--- C3_386.EXE ---

Access is denied.
exit code: 5
```

This turned out to be a particularly interesting PE compatibility problem.

The 1991 executables use:

```text
SectionAlignment = 0x10000
```

During conversion, their enormous prototype relocation tables had been replaced by much smaller standard PE relocation blocks.

The relocation **directory size** correctly became smaller, but the `.reloc` section's **VirtualSize** was also accidentally reduced to the compact payload size.

That introduced 64-KB holes between mapped sections.

Wine tolerated those images.

The Windows NT image loader did not, rejecting C1/C2/C3 during `CreateProcess` with `ERROR_ACCESS_DENIED` before their entry points were ever reached.

CL386 happened to work because its relocation section still occupied only one 64-KB mapping quantum, hiding the bug.

The corrected converters preserve the original mapped `.reloc` extent while using the smaller modern relocation data internally.

After that correction, the entire compiler pipeline runs natively on Windows 10.

See the `analysis/windows10_loader_validation.md` file in each component directory for the detailed investigation.

## Repository layout

Each compiler component has its own self-contained research/rebuild tree:

```text
cl386_nt1991/
c1_386_nt1991/
c2_386_nt1991/
c3_386_nt1991/
```

Typical contents are:

```text
analysis/    PE analysis, symbols, cross-references and research notes
build/       modern Win32 executable and compatibility DLL
compat/      source for the Win32 compatibility layer
parts/       extracted binary components
reference/   preserved reference material
src/         reversible annotated assembly / recovered pseudocode
tools/       reconstruction and PE modernization tools
```

Each directory has its own README describing that pass in considerably more detail.

## Reversible analysis

An important goal of this project was to distinguish between:

1. what is actually known from the binary;
2. what has been inferred during reverse engineering.

The annotated assembly listings therefore retain the original machine-code bytes as authoritative `db` data, with decoded instructions, symbols, source information and annotations represented as comments.

The supplied rebuild tools can reconstruct the historical executable from this representation and verify it against the original hash.

The recovered C-like files are intended as **semantic pseudocode for study**, not claims to possess Microsoft's original C source.

## Modern Win32 builds

The `build/` directory for each component contains its converted executable and corresponding compatibility DLL.

For example:

```text
CL386-WIN32.EXE
CL386COMPAT.DLL

C1_386-WIN32.EXE
C1_386COMPAT.DLL

C2_386-WIN32.EXE
C2_386COMPAT.DLL

C3_386-WIN32.EXE
C3_386COMPAT.DLL
```

These remain 32-bit i386 programs and therefore depend on the operating system providing Win32/WOW64 support.

The compiler's output is also historically interesting: C3 generates Microsoft-style **OMF object files**. An early Microsoft NT linker can convert those objects to COFF while producing a Win32 executable.

## Why?

Mostly because it existed.

These binaries sit at an unusual point in history:

```text
16-bit Microsoft development tools
             |
             v
      386 native compiler
             |
             v
    prototype Windows NT
             |
             v
       modern Win32
```

Being able to examine the binaries is useful.

Being able to reconstruct them byte-for-byte is better.

Being able to run the actual December 1991 compiler pipeline on a current Windows machine and compile real programs with it is considerably more fun.

## Status

Current status:

```text
CL386    modern Win32 conversion working
C1_386   modern Win32 conversion working
C2_386   modern Win32 conversion working
C3_386   modern Win32 conversion working

Wine     working
Windows 10 x64 / WOW64     working

multi-file compilation      working
optimization (/O)           working
OMF output                   working
link to runnable Win32 EXE   working
```

There are undoubtedly still unexplored code paths and compatibility edge cases. This is an archaeological/research project rather than an attempt to turn Microsoft C/386 6.00.081 into a supported contemporary compiler.

Issues, additional test cases and historical information are welcome.

## Historical and copyright note

This repository is intended for **software preservation, interoperability and historical research**.

Microsoft, Windows, Windows NT and Microsoft C are trademarks or products of Microsoft Corporation.

The historical Microsoft binaries and other original Microsoft material remain the property of their respective copyright holder. Nothing in this repository should be interpreted as granting rights to Microsoft copyrighted material.

The reverse-engineering notes, compatibility code and reconstruction tooling are provided for research into these historical executables.

This project is not affiliated with or endorsed by Microsoft.

---

*Microsoft C/386 6.00.081 — December 1991 software, still compiling C on Windows more than three decades later.*
