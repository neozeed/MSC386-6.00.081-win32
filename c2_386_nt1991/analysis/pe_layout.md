# C2_386.EXE transitional PE layout

- SHA-256: `64aa0b3bbd0ef4d691515b7d56d62f6403f08c2af36b9712d13c7e847f7eae7a`
- PE timestamp: `692415336` (1991-12-11 per COFF timestamp)
- Machine: `0x014c` (i386)
- Optional-header magic: `0x010b` (PE32)
- ImageBase: `0x00010000`
- Entry RVA: `0x0004eada` (VA `0x0005eada`)
- COFF symbols: 3853
- .text line records: 2345
- Old relocation directory: RVA `0x000c0000`, record count `15190`
- Active relocation records: 15184; validation failures: 0

## Sections

- 1: `.text` RVA `0x00010000`, raw size `0x59600`, file `0x400`, old first field `0x0`, flags `0x60000020`
- 2: `.bss` RVA `0x00070000`, raw size `0x7200`, file `0x0`, old first field `0x0`, flags `0xc0000080`
- 3: `.data` RVA `0x00080000`, raw size `0x17a00`, file `0x59a00`, old first field `0x0`, flags `0xc0000040`
- 4: `.data` RVA `0x000a0000`, raw size `0x200`, file `0x71400`, old first field `0x0`, flags `0x40000040`
- 5: `.idata` RVA `0x000b0000`, raw size `0x400`, file `0x71600`, old first field `0x0`, flags `0xc0000040`
- 6: `.reloc` RVA `0x000c0000`, raw size `0x2ca00`, file `0x71a00`, old first field `0x0`, flags `0x40000040`
- 7: `.debug` RVA `0x000f0000`, raw size `0x18c00`, file `0x9e400`, old first field `0x0`, flags `0x40000040`

The relocation directory is not the modern page-block format. Its directory size field is a count of 12-byte records `(VirtualAddress, Value, Type, padding)`. Active type-3 records were validated by checking that the DWORD at each relocation RVA equals `ImageBase + Value`.
