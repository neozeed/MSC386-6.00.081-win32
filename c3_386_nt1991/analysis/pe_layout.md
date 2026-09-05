# C3_386.EXE transitional PE layout

- SHA-256: `337cbe52d9075b73948bf42512d3983b2effa3f9e23df8b2687d7e1acb6f8b23`
- PE timestamp: `692415421` (1991-12-11 per COFF timestamp)
- Machine: `0x014c` (i386)
- Optional-header magic: `0x010b` (PE32)
- ImageBase: `0x00010000`
- Entry RVA: `0x00028ece` (VA `0x00038ece`)
- COFF symbols: 2663
- .text line records: 2225
- Old relocation directory: RVA `0x00070000`, record count `7067`
- Active relocation records: 7064; validation failures: 0

## Sections

- 1: `.text` RVA `0x00010000`, raw size `0x1d600`, file `0x400`, old first field `0x0`, flags `0x60000020`
- 2: `.bss` RVA `0x00030000`, raw size `0x5200`, file `0x0`, old first field `0x0`, flags `0xc0000080`
- 3: `.data` RVA `0x00040000`, raw size `0x5a00`, file `0x1da00`, old first field `0x0`, flags `0xc0000040`
- 4: `.data` RVA `0x00050000`, raw size `0x200`, file `0x23400`, old first field `0x0`, flags `0x40000040`
- 5: `.idata` RVA `0x00060000`, raw size `0x400`, file `0x23600`, old first field `0x0`, flags `0xc0000040`
- 6: `.reloc` RVA `0x00070000`, raw size `0x14c00`, file `0x23a00`, old first field `0x0`, flags `0x40000040`
- 7: `.debug` RVA `0x00090000`, raw size `0x11600`, file `0x38600`, old first field `0x0`, flags `0x40000040`

The relocation directory is not the modern page-block format. Its directory size field is a count of 12-byte records `(VirtualAddress, Value, Type, padding)`. Active type-3 records were validated by checking that the DWORD at each relocation RVA equals `ImageBase + Value`.
