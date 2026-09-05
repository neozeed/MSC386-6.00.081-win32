/*
 * C3_386.EXE -- conservative structural decompilation, Dec-1991 Windows NT build.
 *
 * This file is for understanding, not byte reproduction.  Original COFF names
 * are retained verbatim.  See c3_386_nt1991_annotated.asm for the authoritative
 * byte-preserving reconstruction.
 */

int _main(int argc, char **argv)
{
    /* main.c.  The exact option-variable names/types are still being recovered. */
    initialize_compiler_globals();                    /* inferred grouping */
    parse_environment_and_command_line(argc, argv);  /* _getenv, _unconcat, _crack_cmd */

    /* Open the compiler intermediate streams, source/listing streams and object output. */
    open_requested_files();                           /* _fopen/_freopen + _fatal C1013/C1032/C1036/C1037 */
    _init_operand();
    _asm_init();
    _init_locsymtab();
    _read_globsil();
    _init_obj();

    /* Phase-3 reads C2's intermediate representation and reconstructs procedures. */
    for (;;) {
        _read_locsil();
        _clear_reg_flag();
        if (!_readproc())
            break;

        /* Post-optimizer / final machine-code transforms. */
        _post_opt();
        _calc_offsets(/* procedure */);

        /* Depending on options, emit listing/disassembly/debug/object records. */
        _GetSourceLine(/* ... */);
        _decode(/* ... */);
        _disasm(/* ... */);
        _emit_dbgsyms(/* ... */);
    }

    _final();
    _fin_obj();
    _fin_asm();
    _fin_mingle();
    _fin_list();
    return /* compiler status */ 0;
}

void _final(void)
{
    /* main.c finalization: flush remaining object/listing/debug state and
       report final diagnostics.  Exact branches are in the annotated ASM. */
}

/* OMF object writer (original names from omf.c / omf_ms.c). */
void object_emission_outline(void)
{
    _init_obj();
    _eTHEADR();
    _eCOMENT();
    _eLNAME();
    _eSEGDEF();
    _eEXTDEF();
    _ePUBDEF();
    _eLINNUM();
    _eFIXUPP();
    _eMODEND();
    _fin_obj();
}

/* Final post-optimizer / branch-layout machinery (original symbols). */
void post_optimizer_outline(void)
{
    _post_opt();
    _move_code();
    _sp_indep_opts();
    _sp_dep_opts();
    _calc_offsets();
    _br_size();
    _branch_chain();
    _cross_jumps();
    _dead_code();
    _ExpandJMP();
    _peephole();
    _shorten_instr();
}

/* Debug-symbol emission (original symbols). */
void debug_emission_outline(void)
{
    _emit_dbgsyms();
    _emit_proc_start();
    _emit_block();
    _emit_stack_locals();
    _emit_reg_vars();
    _emit_parameters();
    _emit_local_autos();
    _emit_local_statics();
    _emit_end();
}

/* Shared C23_386.ERR subsystem; these names survive in the COFF table. */
void _error(unsigned n, ...);      /* message number 2000+n */
void _fatal(unsigned n, ...);      /* message number 1000+n */
void _warning(unsigned level, unsigned n, ...); /* message number 4000+n */
void _message(/* ... */);
void _do_format(/* ... */);
int  _get_err(/* ... */);
int  get_msg(/* ... */);
int  get_int(/* ... */);
char *get_message(/* ... */);
long nearest(/* ... */);
void mark_pos(/* ... */);

/* Representative C3-specific diagnostics recovered at direct call sites:
 * C1039: unrecoverable heap overflow in Pass 3
 * C4063: function too large for post-optimizer
 * C4065: recoverable heap overflow in post-optimizer - some optimizations may be missed
 * C2427: jump referencing label is out of range
 * C4301: loss of debugging information caused by optimization
 */
