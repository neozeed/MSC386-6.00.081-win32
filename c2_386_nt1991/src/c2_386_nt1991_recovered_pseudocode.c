/*
 * C2_386.EXE -- conservative structural pseudocode, Dec-1991 Windows NT build.
 *
 * This is NOT the byte-authoritative reconstruction.  See the annotated ASM.
 * Names beginning with '_' are original COFF names unless explicitly marked.
 */

int _main(int argc, char **argv) {
    /* establishes an early-NT SEH frame around the pass-2 driver */
    return _real_main(argc, argv);
}

int _real_main(int argc, char **argv) {
    /* Exact local variable types remain under reconstruction. */
    initialize_pass2_state(argc, argv);       /* inferred grouping */
    process_compiler_intermediate_stream();   /* _dop2 family */
    _alloc_parms();
    finalize_outputs_and_statistics();        /* inferred grouping */
    return /* pass status */ 0;
}

/* Original named optimizer families recovered directly from COFF: */
void optimizer_outline(void) {
    _build_flow_graph();
    _filter_dead_code();
    _find_loops();
    _canonicalize_loops1();
    _canonicalize_loops2();

    _canontree();
    _hoisttree();

    _globalregs();
    _gather_gramregs_requirements();
    _build_allocation_ranges();
    _color_regs();
    _assign_regs();

    _regmap_init();
    _reg_build();
    _reg_alloc();
    _reg_assign();

    _emit();
}

/* Diagnostic implementation, names are original COFF symbols. */
void _error(unsigned n, ...) {
    unsigned full = 2000 + n;
    _message(2000, n, lookup_message(full), /* varargs */ 0);
    /* increments compiler error count and may escalate to fatal */
}

void _fatal(unsigned n, ...) {
    unsigned full = 1000 + n;
    /* obtains/prints C1xxx text, then terminates/nonlocally exits pass */
}

void _warning(unsigned level, unsigned n, ...) {
    unsigned full = 4000 + n;
    /* obeys warning level, warning-as-error options, then formats text */
}

/* Runtime message file helpers retained with their original names. */
int  _get_err(/* FILE*, number, ... */);
int  _get_msg(/* FILE*, number, ... */);
char *_get_message(/* quoted text parser; handles escaped newlines/tabs */);
int  _get_int(/* decimal message number parser */);
void _mark_pos(/* diagnostic-file position cache */);
long _nearest(/* nearest cached message position */);

/* Particularly useful original optimizer names include:
 * _globalregs, _color_regs, _allocate_trivially_colorable,
 * _allocate_tough_ones, _tree_reg_rewrite, _foreach_flow,
 * _build_flow_graph, _find_loops, _mark_loop_body,
 * _canonicalize_loops1, _canonicalize_loops2,
 * _canontree, _hoisttree, _emit, _emit_line,
 * _reg_alloc, _reg_assign, _reg_steal, _reg_restore,
 * _live_inreg, _flow, _do_enreg, _global_cse and related CSE routines.
 */
