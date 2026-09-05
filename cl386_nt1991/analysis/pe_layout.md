# CL386 1991 prototype PE/COFF layout

- COFF machine: `0x014c` (i386)
- Timestamp: `692413901` = 1991-12-11 01:11:41 UTC
- Optional header: PE32 `0x10b`, size `0xa8`
- Preferred image base: `0x00010000`
- Entry point RVA: `0x15926` (`mainCRTStartup`)
- Section alignment: `0x10000`; file alignment `0x200`
- COFF symbol table: file offset `0x141a8`, **1373 symbols**
- `.text` COFF line table: offset `0x1203c`, **1426 entries**

| Section | RVA | old SizeOfRawData | file offset | old PhysicalAddress | characteristics |
|---|---:|---:|---:|---:|---:|
| .text | 0x10000 | 0x8a00 | 0x400 | 0x0 | 0x60000020 |
| .bss | 0x20000 | 0xc00 | 0x0 | 0x0 | 0xc0000080 |
| .data | 0x30000 | 0x2600 | 0x8e00 | 0x0 | 0xc0000040 |
| .idata | 0x40000 | 0x400 | 0xb400 | 0x0 | 0xc0000040 |
| .reloc | 0x50000 | 0x6800 | 0xb800 | 0x0 | 0x40000040 |
| .debug | 0x60000 | 0x9600 | 0x12000 | 0x0 | 0x40000040 |

## Transitional relocation format

The base-relocation directory contains `0x88b` (2187) old records, each physically 12 bytes: `ULONG VirtualAddress; ULONG Value; USHORT Type; USHORT padding`. 2184 records are type 3 and 3 are zero terminator/padding records.

For a type-3 record, the DWORD at the source RVA equals `ImageBase + Value`; this was validated across the mapped records before conversion. `tools/modernize_pe.py` converts those records to current page-grouped `IMAGE_BASE_RELOCATION` HIGHLOW blocks.
