# C3_386.EXE — December 1991 NT reverse/rebuild + Win32 conversion

This bundle contains a byte-reversible annotated reverse of the pre-release Windows NT C compiler Pass 3 executable and an experimental conversion for modern 32-bit Win32/WOW64.

## Key facts

- Original SHA-256: `337cbe52d9075b73948bf42512d3983b2effa3f9e23df8b2687d7e1acb6f8b23`
- PE timestamp: 11 December 1991
- Transitional PE32/i386, preferred ImageBase `0x00010000`
- Raw COFF symbol-table entries: 2,663
- Parsed primary symbol records: 1,888
- Named text symbols: 579 (550 external + 29 static)
- `.text` source-line records: 2,225
- COFF source contributions: 129
- Old relocation records: 7,067; 7,064 active and all validated
- Shared `C23_386.ERR`: byte-for-byte identical to the C2 copy

## Reversible reverse

`src/c3_386_nt1991_annotated.asm` is the authoritative annotated listing.  Its `db` directives preserve the original bytes; disassembly, original COFF names, source-line markers, resolved direct-call targets and diagnostic texts are comments.  `tools/rebuild_original.py` reconstructs the historical executable and verifies byte-for-byte.

`src/c3_386_nt1991_recovered_pseudocode.c` is a conservative structural decompilation for reading.  It is not intended to be byte-identical source.

## What C3 does

The surviving original names identify Pass 3 as the final post-optimizer/object-emission stage.  Major families include:

- object/OMF generation: `_init_obj`, `_eTHEADR`, `_eSEGDEF`, `_eFIXUPP`, `_eMODEND`, `_fin_obj`, `_put_object`
- final branch/code transforms: `_post_opt`, `_move_code`, `_branch_chain`, `_cross_jumps`, `_ExpandJMP`, `_peephole`, `_shorten_instr`
- debug information: `_emit_dbgsyms`, `_emit_proc_start`, `_emit_stack_locals`, `_emit_reg_vars`, `_emit_parameters`
- intermediate input: `_read_ail`, `_read_sil`, `_read_locsil`, `_read_globsil`, `_readproc`
- listing/disassembly: `_disasm`, `_disinstr`, `_print_line`, `_list_globals`

## Modern Win32 conversion

`build/C3_386-WIN32.EXE` preserves the historical `0x00010000` ImageBase, expands the shortened prototype optional header to canonical PE32 form, converts the old relocation array to 7,064 standard HIGHLOW relocations in 36 page blocks, preserves the original `.reloc` mapped extent, normalizes section semantics, and redirects both early import descriptors to `C3_386COMPAT.DLL`.

The shim handles the old caller-cleanup API convention, the old small STARTUPINFO layout, and the old three-argument `RtlUnwind`.  C3 does not need C2's custom setjmp/longjmp bridge.

**Runtime status:** the corrected build is **validated on native 64-bit Windows 10 (10.0.19045.6466)** and participated successfully in the complete optimized CL386/C1/C2/C3 build of `phoon`.  See `analysis/windows10_loader_validation.md` for the section-layout bug that Windows rejected with error 5 while Wine accepted it.

## Useful files

- `analysis/functions.tsv` — recovered text symbols
- `analysis/module_function_index.md` — functions grouped by original COFF source contribution
- `analysis/source_lines.tsv` — line table
- `analysis/diagnostic_call_refs.tsv` — direct C23 diagnostic calls
- `analysis/c2_c3_symbol_crosswalk.tsv` — same-name C2/C3 routines
- `analysis/win32_compatibility.md` — conversion details and caveats
- `analysis/windows10_loader_validation.md` — native Windows loader fix and Phoon regression test
- `analysis/ROUNDTRIP_OK.txt` — exact reconstruction proof
- `tools/modernize_c3_386.py` — reproducible modernizer
- `compat/` — source and build script for the compatibility DLL
