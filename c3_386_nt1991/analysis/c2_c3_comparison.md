# C2/C3 relationship

`C23_386(1).ERR` is byte-for-byte identical to the C2 copy previously supplied.

- C23_386.ERR SHA-256: `8052e0126d291950ea9b09f44c6ef7dfc333cc36e9a8968c529900d8d7ec85d1`
- C2 recovered named text symbols: 1460
- C3 recovered named text symbols: 579
- Exact shared symbol names: 200

The overlap includes the shared CRT/diagnostic machinery and several compiler-side support routines.  C3's unique named families make its role especially clear: OMF/object emission (`_eSEGDEF`, `_eFIXUPP`, `_eMODEND`, `_put_object`), post-optimization/branch rewriting (`_post_opt`, `_branch_chain`, `_cross_jumps`, `_peephole`, `_ExpandJMP`), debug-symbol emission (`_emit_dbgsyms`, `_emit_proc_start`, `_emit_stack_locals`), compiler-intermediate input (`_read_ail`, `_read_sil`, `_read_locsil`, `_read_globsil`), and source/object listing/disassembly (`_disasm`, `_print_line`, `_list_globals`).

See `c2_c3_symbol_crosswalk.tsv` for exact same-name RVA pairs.
