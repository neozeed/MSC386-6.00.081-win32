# C2_386.EXE — December 1991 Windows NT reverse/rebuild bundle

This bundle contains a conservative, byte-reversible reverse of the supplied
Microsoft C/386 Pass 2 compiler image and an experimental modern Win32 adaptation.

## Strong recovered evidence

- PE32/i386 transitional image, timestamped 11 December 1991.
- 3,853 COFF symbol-table entries including auxiliaries.
- 1,439 externally named `.text` symbols plus 21 additional named static text symbols.
- 2,345 original `.text` source-line records.
- 153 COFF source/object contributions.
- Original names expose the optimizer directly: `_globalregs`, `_color_regs`,
  `_assign_regs`, `_build_flow_graph`, `_find_loops`, `_canontree`, `_hoisttree`,
  `_reg_alloc`, `_reg_assign`, `_live_inreg`, `_emit`, `_main`, `_real_main`, etc.
- The diagnostics subsystem retains its original names: `_error`, `_fatal`,
  `_warning`, `_message`, `_format`, `_do_format`, `_get_err`, `_get_msg`,
  `_get_message`, `_get_int`, `_mark_pos`, and `_nearest`.
- `C23_386.ERR` parses to 71 supplied Pass-2/Pass-3 diagnostics. 57 direct calls to
  `_error`, `_fatal`, or `_warning` were identified; where an immediate message
  number is recoverable, the assembly listing annotates the actual C1xxx/C2xxx/C4xxx text.

## Reversible listing

`src/c2_386_nt1991_annotated.asm` uses `db` directives as the authoritative byte
representation and puts decoded x86, COFF symbols, source-line information, and
message text in comments. This avoids silently changing Microsoft's 1991 instruction
encoding or embedded data.

`tools/assemble_listing.py` reconstructs the `.text` bytes directly from that listing.
`tools/rebuild_original.py` inserts them into a preserved image template.
The resulting executable is byte-for-byte identical to the supplied file; see
`analysis/ROUNDTRIP_OK.txt`.

## Modern Win32 build

`build/C2_386-WIN32.EXE` converts the old relocation representation to modern
page-based HIGHLOW relocations, rebases the image to 0x00400000, normalizes old
section semantics, and redirects the old BASE/NTDLL import surfaces to
`build/C2_386COMPAT.DLL`.

The compatibility DLL translates caller-cleanup 1991 API calls to current Win32,
translates the old STARTUPINFO and RtlUnwind forms, and supplies a local x86
setjmp/longjmp pair because C2 imports those from early NTDLL.

This pair is structurally validated but was not runtime-tested because the analysis
environment has no Windows or Wine installation. See `analysis/win32_compatibility.md`.

## Useful files

- `src/c2_386_nt1991_annotated.asm` — byte-authoritative annotated listing.
- `src/c2_386_nt1991_recovered_pseudocode.c` — conservative architectural pseudocode.
- `analysis/functions.tsv` — named text symbols with RVA/VA and source contribution.
- `analysis/module_function_index.md` — functions grouped by source contribution.
- `analysis/source_lines.tsv` — retained COFF source line information.
- `analysis/diagnostic_call_refs.tsv` — mapped diagnostic call sites.
- `analysis/error_catalog.tsv` — parsed C23_386.ERR catalogue.
- `analysis/imports.tsv` — original early-NT imports.
- `analysis/old_relocations.tsv` — all transitional relocation records and validation.
- `tools/modernize_c2_386.py` — reproducible Win32 conversion.
- `compat/` — source and build script for C2_386COMPAT.DLL.
