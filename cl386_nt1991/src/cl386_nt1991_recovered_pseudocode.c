/*
 * CL386 1991 NT build: recovered high-confidence semantic pseudocode.
 *
 * This file is intentionally NOT claimed to be compilable original source.
 * The byte-authoritative reverse is src/cl386_nt1991_code.asm. Function names
 * come from the executable's retained COFF symbol table; semantics are aided by
 * the OS/2 CL386 CodeView build, where 154/155 recovered procedure names match.
 */

typedef unsigned long u32;

/* cc_main.c family: RVA 0x106b5 */
static void SetupErrors(void)
{
    char *p = path("cl386.err");
    if (!p) p = "";
    Comp_Errpath_runtime = give_path(p, "cl386.err");
    get_err();
}

/* get_err.c family: RVA 0x15fec. Same algorithm as the OS/2 driver. */
static char *get_message(char *p)
{
    char *retp, *cp;
    while (*p && *p != '"') ++p;
    if (!*p) return 0;
    cp = retp = ++p;
    while (*p && *p != '"') {
        /* DBCS lead-byte table handling is retained in the binary. */
        if ((unsigned char)*p >= 0x80 && DBCS_LEAD[(unsigned char)*p]) {
            *cp++ = *p++; *cp++ = *p++; continue;
        }
        if (*p == '\\') {
            ++p;
            if (*p == 'n') *p = '\n';
            else if (*p == 't') *p = '\t';
            else *cp++ = '\\';
        }
        *cp++ = *p++;
    }
    *cp=0; return retp;
}

static char *get_unsigned(char *p, u32 *v)
{
    u32 n=0;
    if (!SPECIAL_MODE && (*p<'0'||*p>'9')) n=0xffffffffUL;
    else while (*p>='0'&&*p<='9') n=n*10+(*p++-'0');
    *v=n; return p;
}

static void get_msg(void)
{
    /* NT .ERR has categories 2xxx and 4xxx, loaded into the same 32/21 slot
       tables as the OS/2 build. */
    while (getline(ERR_HANDLE, Errbuff, 0x80)) {
        u32 number; char *p=get_unsigned(Errbuff,&number);
        if (!number || number==0xffffffffUL) continue;
        unsigned idx=number%1000; char *msg=strdup(get_message(p));
        switch (number/1000) {
        case 2: if (idx<32) Error_msgs[idx]=msg; break;
        case 4: if (idx<21) Warning_msgs[idx]=msg; break;
        }
    }
}

static void get_err(void)
{
    ERR_HANDLE=open(Comp_Errpath_runtime,0);
    if (ERR_HANDLE==-1) {
        /* Fill all message slots with a generated cannot-open diagnostic. */
        install_error_file_fallback();
        return;
    }
    get_msg(); close(ERR_HANDLE);
}

/* error.c family: RVA 0x1569f / 0x15731 */
int cmderr(int n, ...)
{
    if (!errors_initialized) { SetupErrors(); errors_initialized=1; }
    /* prefixes command-line error with displayed number 2000+n, formats the
       corresponding Error_msgs[] entry, deletes temporaries and returns a
       compiler-driver status. See byte-exact listing for exceptional cases. */
    return recovered_cmderr_body(n /*, varargs */);
}
void cmdwarn(int n, ...)
{
    if (!errors_initialized) { SetupErrors(); errors_initialized=1; }
    /* displayed warning number is 4000+n; warning-as-error mode is retained. */
    recovered_cmdwarn_body(n /*, varargs */);
}

/* targetcode.c family: RVA 0x1368f */
static void help(void)
{
    /* Locates cl386.msg, opens it, and renders the option/help text. The same
       runtime-message architecture exists in the OS/2 build, but this NT MSG
       has a different option set. */
    recovered_help_reader_and_formatter();
}

/* NT static CRT, dosspawn.c: RVA 0x17762.
 * This exposes an ABI difference important for running it today.
 */
static int __dospawn(int mode, char *name, char *cmdline, char *env)
{
    EARLY_NT_STARTUPINFO si;   /* exactly 0x38 bytes in this binary */
    PROCESS_INFORMATION pi;
    zero(&si, 0x38);
    si.cb = 0x38;
    /* constructs the inherited CRT fd block, then: */
    int ok = CreateProcessA(name, cmdline, 0, 0, 1, 0, env, 0, &si, &pi);
    /* caller cleans all 10 arguments after the import call: early NT cdecl ABI */
    if (!ok) map_os_error(GetLastError());
    /* wait/return behavior depends on spawn mode */
    return recovered_wait_or_detach_logic(mode,&pi);
}

/* CRT exception helper around RVA 0x15bf6 calls the 1991 RtlUnwind form with
   THREE arguments: RtlUnwind(TargetFrame, TargetIp, ExceptionRecord). Modern
   32-bit RtlUnwind takes a fourth ReturnValue argument; CL386COMPAT adds NULL. */
