# Dec-1991 C1 PE/COFF layout

* Timestamp: `692413927` (11 Dec 1991 in the COFF header)
* Machine: `0x014C` i386
* Sections: **8**
* ImageBase: `0x00010000`
* Entry RVA: `0x2CCC0`
* COFF symbol pointer/count: `0x41756` / **3161**
* `.text` line records: **2095**
* Old relocation-directory second DWORD: **6655** records, not modern byte size.

## Sections

* `.text` RVA `0x10000`, raw `0x400`, raw size `0x22800`, old first header field `0x0`
* `.bss` RVA `0x40000`, raw `0x0`, raw size `0x7E00`, old first header field `0x0`
* `.data` RVA `0x50000`, raw `0x22C00`, raw size `0x5E00`, old first header field `0x0`
* `.data` RVA `0x60000`, raw `0x28A00`, raw size `0x200`, old first header field `0x0`
* `ASMYYSEG` RVA `0x70000`, raw `0x28C00`, raw size `0x1E00`, old first header field `0x0`
* `.idata` RVA `0x80000`, raw `0x2AA00`, raw size `0x400`, old first header field `0x0`
* `.reloc` RVA `0x90000`, raw `0x2AE00`, raw size `0x13800`, old first header field `0x0`
* `.debug` RVA `0xB0000`, raw `0x3E600`, raw size `0x13E00`, old first header field `0x0`