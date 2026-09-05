/*
 * C1_386.EXE (Dec 1991 Windows NT build) — recovered semantic pseudocode
 *
 * This is a readable guide, NOT the reversible source.  The exact reversible form is
 * c1_386_nt1991_annotated.asm, whose db directives reproduce the original .text bytes.
 *
 * Remarkably, this image retains a 3,161-entry COFF symbol table and old COFF line
 * records.  Names below such as _main, MAIN_COMPILE, get_err, get_msg, get_message,
 * get_int, _error, _fatal and _warning are original binary symbols, not inventions.
 */

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

/* main.c */
int _main(int argc, char **argv, char **envp)
{
    /* CRT has already built argc/argv/envp.  The front-end initializes global
       compiler state and delegates the actual pass to MAIN_COMPILE(). */
    return MAIN_COMPILE(/* global/argv driven state */);
}

/* Common\\error.c — original static symbol names are retained in COFF. */
static char *get_message(char *p)
{
    char *start, *dst;
    while (*p != '"') ++p;
    start = dst = ++p;
    while (*p != '"') {
        if (*p == '\\') {
            ++p;
            if (*p == 'n') *p = '\n';
            else if (*p == 't') *p = '\t';
            else *dst++ = '\\';
        }
        *dst++ = *p++;
    }
    *dst = 0;
    return start;
}

/* Original symbol is get_int; OS/2 reverse called the equivalent get_unsigned. */
static char *get_int(unsigned *out, char *p)
{
    unsigned v = 0;
    while (isdigit_table[(unsigned char)*p]) {
        v = v * 10 + (*p - '0');
        ++p;
    }
    *out = v;
    return p;
}

/* get_err/get_msg/nearest/mark_pos implement lazy access to C1_386.ERR.
   The same 20-entry message-number/file-position cache observed in the OS/2
   binary is visible here, now with the compiler's original static names. */
static char *get_err(unsigned id)
{
    if (error_file_not_open)
        open_error_file(/* compiler-selected C1_386.ERR path */);
    if (error_file_unavailable)
        return fallback_text;
    return get_msg(/* scratch */, id);
}

static char *get_msg(char *scratch, unsigned id)
{
    /* nearest(id) selects an exact/near cached file position; the routine then
       scans records, parses their numeric identifiers with get_int(), caches
       useful positions with mark_pos(), and returns get_message(record). */
    return lookup_record_in_error_file(scratch, id);
}

void _error(unsigned n, ...)
{
    /* Binary adds 2000 to the low internal number before get_err()/message(). */
    emit_compiler_diagnostic(2000 + n, /* varargs */);
    ++compiler_error_count;
}

void _fatal(unsigned n, ...)
{
    emit_compiler_diagnostic(1000 + n, /* varargs */);
    terminate_compilation();
}

void _warning(unsigned n, ...)
{
    /* Warning-level suppression/checking precedes formatting. */
    if (warning_enabled(n))
        emit_compiler_diagnostic(4000 + n, /* varargs */);
}

/* _message is the central formatted-diagnostic path; _format/_do_format are
   subordinate formatters.  The exact call graph and all 428 recovered immediate
   diagnostic IDs are in diagnostic_call_refs.tsv and the annotated assembly. */

/* Representative original compiler symbols preserved by COFF:
 *   TYPE_CHECK, BUILD_BINARY, BUILD_UNARY, BUILD_CAST, RESULT_TYPE
 *   ENTERSYMBOL, TYPESYMBOL, GET_SYMBOL, LOOK_SYMBOL
 *   DEFINEESU, REFERENCEESU, LEAVESU, LEAVEENUM
 *   INLINE_ASSEMBLER, ASM_YYPARSE, ASM_YYLEX, ASSEMBLE
 *   INTRINSIC, FUNCTION, DEINTRINSIC
 *   PREPROCESS, DIRECTIVE, GET_KEYWORD, IS_KEYWORD
 *   plus hundreds more listed in analysis/functions.tsv and module_function_index.md.
 */
