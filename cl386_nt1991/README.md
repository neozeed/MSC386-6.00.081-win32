# CL386 (December 1991 Windows NT) reversible reverse + Win32 compatibility build

This bundle analyzes the uploaded 1991 NT `CL386.EXE`, aligns it with the previously reversed OS/2 CL386, provides a byte-authoritative annotated `.text` listing, and provides a modern-PE conversion plus an ABI compatibility DLL.

## Headline results

- Prototype/transitional **PE32/i386**, not NE; COFF timestamp 1991-12-11.
- Retains **1373 COFF symbols** and **0x592 (1426) text line records**.
- **154/155** named procedures from the OS/2 reverse match by name.
- Original imports: 36 functions from `base.dll`, 2 from `ntdll.dll`.
- Old relocation representation: 2187 records; 2,184 active type-3 relocations.
- Modernized EXE: `build/CL386-WIN32.EXE`, paired with `build/CL386COMPAT.DLL`.
- Original reversible source: `src/cl386_nt1991_code.asm`.

## Reversibility

`tools/rebuild_original.py` parses every `db` byte from the annotated assembly and inserts the reconstructed 0x8a00-byte text section into an otherwise byte-preserved template.

Original SHA-256: `0c28c9222c55783a8c9cfc2f11a61c987f03f86f23d73fbc05744453871d8730`

## Important runtime caveat

The compatibility pair is structurally validated as modern PE32, but this environment has no Windows/Wine runtime, so it has not yet been launch-tested. CL386 is a driver: useful compilation also requires its external pass executables such as `c1_386.exe`, `c2_386.exe`, `c3_386.exe` and whatever linker/assembler path the chosen options invoke.

## Files

- `src/cl386_nt1991_code.asm` — full byte-exact, annotated i386 listing.
- `src/cl386_nt1991_recovered_pseudocode.c` — high-confidence semantic reconstruction of important routines.
- `analysis/function_crosswalk_os2_to_nt.tsv` — all OS/2 procedure names aligned to NT RVAs.
- `analysis/os2_alignment.md` — why the earlier reverse is such a useful baseline.
- `analysis/pe_layout.md` — prototype PE and old relocation analysis.
- `analysis/compatibility_notes.md` — calling convention/structure ABI issues and the shim design.
- `analysis/message_diffs.md` — exact differences between OS/2 and NT message/error files.
- `compat/cl386_compat.c` / `.def` — source for the compatibility DLL.
- `tools/modernize_pe.py` — deterministic prototype-PE -> modern-PE converter.
- `build/CL386-WIN32.EXE` + `build/CL386COMPAT.DLL` — pair to test together on modern 32-bit Win32/WOW64.
