/*
 * DEC1991COMPAT.DLL
 * -----------------
 * Source reconstruction of the compatibility layer used by the
 * December-1991 NT C/386 "universal retranslation" toolchain.
 *
 * Why this DLL exists:
 *   - Dec-1991 BASE.DLL calls use caller-cleanup/cdecl.
 *   - modern i386 Win32 fixed-argument APIs use stdcall.
 *   - several early NT structures/ABIs differ from released Win32.
 *
 * The DLL deliberately has no import library / CRT dependency.  It walks
 * the PEB, finds already-loaded KERNEL32.DLL / NTDLL.DLL, parses their PE
 * export directories, and resolves the current APIs itself.
 *
 * This source corresponds to the R2 compatibility layer.  Define
 * DEC1991_CORRECTED=1 for two small corrections found while reconstructing
 * the incremental binary patches:
 *
 *   1. R2's incremental GetFileTime adapter duplicated only 3 arguments.
 *      C1's retained fstat.c call site pushes 4, matching released Win32.
 *
 *   2. R2 translated WIN32_FIND_DATA for FindFirstFileA but its later
 *      FindNextFileA adapter did not perform the same +0x2c -> +0x24 shift.
 *
 * The default (DEC1991_CORRECTED=0) preserves R2 runtime behavior.
 */

#ifndef DEC1991_CORRECTED
#define DEC1991_CORRECTED 0
#endif

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            s32;
typedef void          *ptr;

#define CDECL    __cdecl
#define STDCALL  __stdcall
#define NOINLINE __declspec(noinline)

/* ------------------------------------------------------------------------- */
/* Minimal loader/export resolver: no Windows headers, no import libraries.   */
/* ------------------------------------------------------------------------- */

static u8 ascii_lower(u8 c) {
    return (c >= 'A' && c <= 'Z') ? (u8)(c + ('a' - 'A')) : c;
}

static int streq(const char *a, const char *b) {
    while (*a && *b) {
        if (*a++ != *b++) return 0;
    }
    return *a == *b;
}

static int module_name_eq(const u16 *w, u16 bytes, const char *a) {
    u32 n = bytes / 2;
    u32 i = 0;
    for (; i < n && a[i]; i++) {
        if (ascii_lower((u8)w[i]) != ascii_lower((u8)a[i])) return 0;
    }
    return i == n && a[i] == 0;
}

static ptr get_peb(void) {
    ptr p;
    __asm__("movl %%fs:0x30,%0" : "=r"(p));
    return p;
}

static ptr find_loaded_module(const char *name) {
    u8 *peb  = (u8 *)get_peb();
    u8 *ldr  = *(u8 **)(peb + 0x0c);
    u8 *head = ldr + 0x14;       /* PEB_LDR_DATA.InMemoryOrderModuleList */
    u8 *node = *(u8 **)head;

    while (node != head) {
        /* node points at LDR_DATA_TABLE_ENTRY.InMemoryOrderLinks. */
        ptr base = *(ptr *)(node + 0x10);   /* entry+0x18: DllBase */
        u16 len  = *(u16 *)(node + 0x24);   /* entry+0x2c: BaseDllName.Length */
        u16 *buf = *(u16 **)(node + 0x28);

        if (buf && module_name_eq(buf, len, name)) return base;
        node = *(u8 **)node;
    }
    return (ptr)0;
}

static ptr resolve_ordinal(ptr base, u32 ordinal, int depth);
static ptr resolve_name_depth(ptr base, const char *name, int depth);

static ptr resolve_forwarder(const char *fwd, int depth) {
    char mod[64];
    char fn[128];
    u32 i = 0, j = 0;
    int hasdot = 0;
    ptr mb;

    if (depth > 8) return (ptr)0;

    while (fwd[i] && fwd[i] != '.' && i < 55) {
        mod[i] = fwd[i];
        i++;
    }
    mod[i] = 0;
    if (fwd[i] != '.') return (ptr)0;
    i++;

    for (j = 0; mod[j]; j++) {
        if (mod[j] == '.') hasdot = 1;
    }
    if (!hasdot) {
        mod[j++] = '.';
        mod[j++] = 'd';
        mod[j++] = 'l';
        mod[j++] = 'l';
        mod[j] = 0;
    }

    j = 0;
    while (fwd[i] && j < 127) fn[j++] = fwd[i++];
    fn[j] = 0;

    mb = find_loaded_module(mod);
    if (!mb) return (ptr)0;

    if (fn[0] == '#') {
        u32 ord = 0;
        for (j = 1; fn[j] >= '0' && fn[j] <= '9'; j++) {
            ord = ord * 10 + (u32)(fn[j] - '0');
        }
        return resolve_ordinal(mb, ord, depth + 1);
    }

    return resolve_name_depth(mb, fn, depth + 1);
}

static ptr expdir(ptr base, u32 *rva, u32 *size) {
    u8 *b = (u8 *)base;
    u32 pe;
    u8 *opt;

    if (*(u16 *)b != 0x5a4d) return (ptr)0;
    pe = *(u32 *)(b + 0x3c);
    if (*(u32 *)(b + pe) != 0x00004550) return (ptr)0;

    opt = b + pe + 24;
    if (*(u16 *)opt != 0x10b) return (ptr)0;

    *rva  = *(u32 *)(opt + 96);
    *size = *(u32 *)(opt + 100);
    return *rva ? b + *rva : (ptr)0;
}

static ptr finish_export(ptr base, u32 frva, u32 erva, u32 esize, int depth) {
    if (frva >= erva && frva < erva + esize) {
        return resolve_forwarder((const char *)((u8 *)base + frva), depth + 1);
    }
    return (u8 *)base + frva;
}

static ptr resolve_name_depth(ptr base, const char *name, int depth) {
    u32 er, es, nn, i;
    u8 *ed;
    u32 *names, *funcs;
    u16 *ords;

    ed = (u8 *)expdir(base, &er, &es);
    if (!ed || depth > 8) return (ptr)0;

    nn    = *(u32 *)(ed + 24);
    funcs = (u32 *)((u8 *)base + *(u32 *)(ed + 28));
    names = (u32 *)((u8 *)base + *(u32 *)(ed + 32));
    ords  = (u16 *)((u8 *)base + *(u32 *)(ed + 36));

    for (i = 0; i < nn; i++) {
        if (streq((const char *)((u8 *)base + names[i]), name)) {
            return finish_export(base, funcs[ords[i]], er, es, depth);
        }
    }
    return (ptr)0;
}

static ptr resolve_ordinal(ptr base, u32 ordinal, int depth) {
    u32 er, es, first, nf;
    u8 *ed;
    u32 *funcs;

    ed = (u8 *)expdir(base, &er, &es);
    if (!ed || depth > 8) return (ptr)0;

    first = *(u32 *)(ed + 16);
    nf    = *(u32 *)(ed + 20);
    if (ordinal < first || ordinal >= first + nf) return (ptr)0;

    funcs = (u32 *)((u8 *)base + *(u32 *)(ed + 28));
    return finish_export(base, funcs[ordinal - first], er, es, depth);
}

static ptr resolve_os(const char *module, const char *name) {
    ptr b = find_loaded_module(module);
    return b ? resolve_name_depth(b, name, 0) : (ptr)0;
}

/* ------------------------------------------------------------------------- */
/* Generic old-cdecl -> modern-stdcall adapters.                              */
/* ------------------------------------------------------------------------- */

#define DECL0(n,osn) \
u32 CDECL compat_##n(void) { \
    typedef u32 (STDCALL *F)(void); static F f; \
    if (!f) f = (F)resolve_os("KERNEL32.DLL", osn); \
    return f ? f() : 0; \
}

#define DECL1(n,osn) \
u32 CDECL compat_##n(u32 a) { \
    typedef u32 (STDCALL *F)(u32); static F f; \
    if (!f) f = (F)resolve_os("KERNEL32.DLL", osn); \
    return f ? f(a) : 0; \
}

#define DECL2(n,osn) \
u32 CDECL compat_##n(u32 a,u32 b) { \
    typedef u32 (STDCALL *F)(u32,u32); static F f; \
    if (!f) f = (F)resolve_os("KERNEL32.DLL", osn); \
    return f ? f(a,b) : 0; \
}

#define DECL3(n,osn) \
u32 CDECL compat_##n(u32 a,u32 b,u32 c) { \
    typedef u32 (STDCALL *F)(u32,u32,u32); static F f; \
    if (!f) f = (F)resolve_os("KERNEL32.DLL", osn); \
    return f ? f(a,b,c) : 0; \
}

#define DECL4(n,osn) \
u32 CDECL compat_##n(u32 a,u32 b,u32 c,u32 d) { \
    typedef u32 (STDCALL *F)(u32,u32,u32,u32); static F f; \
    if (!f) f = (F)resolve_os("KERNEL32.DLL", osn); \
    return f ? f(a,b,c,d) : 0; \
}

#define DECL5(n,osn) \
u32 CDECL compat_##n(u32 a,u32 b,u32 c,u32 d,u32 e) { \
    typedef u32 (STDCALL *F)(u32,u32,u32,u32,u32); static F f; \
    if (!f) f = (F)resolve_os("KERNEL32.DLL", osn); \
    return f ? f(a,b,c,d,e) : 0; \
}

#define DECL7(n,osn) \
u32 CDECL compat_##n(u32 a,u32 b,u32 c,u32 d,u32 e,u32 f0,u32 g) { \
    typedef u32 (STDCALL *F)(u32,u32,u32,u32,u32,u32,u32); static F f; \
    if (!f) f = (F)resolve_os("KERNEL32.DLL", osn); \
    return f ? f(a,b,c,d,e,f0,g) : 0; \
}

/* Straight-through BASE.DLL compatibility exports. */
DECL1(GetFileAttributesA,       "GetFileAttributesA")
DECL0(GetLastError,             "GetLastError")
DECL1(CloseHandle,              "CloseHandle")
DECL1(ExitProcess,              "ExitProcess")
DECL1(GetFileType,              "GetFileType")
DECL1(GetStdHandle,             "GetStdHandle")
DECL7(DuplicateHandle,          "DuplicateHandle")
DECL0(GetCurrentProcess,        "GetCurrentProcess")
DECL2(SetStdHandle,             "SetStdHandle")
DECL0(GetCurrentProcessId,      "GetCurrentProcessId")
DECL7(CreateFileA,              "CreateFileA")
DECL1(SetEndOfFile,             "SetEndOfFile")
DECL4(SetFilePointer,           "SetFilePointer")
DECL2(SetEnvironmentVariableA,  "SetEnvironmentVariableA")
DECL5(ReadFile,                 "ReadFile")
DECL1(DeleteFileA,              "DeleteFileA")
DECL5(WriteFile,                "WriteFile")
DECL0(GetCommandLineA,          "GetCommandLineA")
DECL0(GetEnvironmentStrings,    "GetEnvironmentStringsA")
DECL0(GetVersion,               "GetVersion")
DECL1(UnhandledExceptionFilter, "UnhandledExceptionFilter")
DECL4(VirtualAlloc,             "VirtualAlloc")
DECL3(GetModuleFileNameA,       "GetModuleFileNameA")
DECL3(VirtualFree,              "VirtualFree")
DECL2(GetExitCodeProcess,       "GetExitCodeProcess")
DECL2(WaitForSingleObject,      "WaitForSingleObject")
DECL2(GetCurrentDirectoryA,     "GetCurrentDirectoryA")
DECL3(GetEnvironmentVariableA,  "GetEnvironmentVariableA")
DECL2(FileTimeToSystemTime,     "FileTimeToSystemTime")
DECL1(FindClose,                "FindClose")
DECL1(GetDriveTypeA,            "GetDriveTypeA")
DECL0(GetLogicalDrives,         "GetLogicalDrives")
DECL1(SetCurrentDirectoryA,     "SetCurrentDirectoryA")
DECL1(FlushFileBuffers,         "FlushFileBuffers")
DECL2(MoveFileA,                "MoveFileA")
DECL0(GetCurrentThread,         "GetCurrentThread")
DECL0(GetCurrentThreadId,       "GetCurrentThreadId")
DECL1(GetModuleHandleA,         "GetModuleHandleA")

/* These APIs return void in released Win32; the early callers ignore EAX. */
void CDECL compat_GetSystemTime(u32 p) {
    typedef void (STDCALL *F)(u32);
    static F f;
    if (!f) f = (F)resolve_os("KERNEL32.DLL", "GetSystemTime");
    if (f) f(p);
}

void CDECL compat_EnterCriticalSection(u32 p) {
    typedef void (STDCALL *F)(u32);
    static F f;
    if (!f) f = (F)resolve_os("KERNEL32.DLL", "EnterCriticalSection");
    if (f) f(p);
}

void CDECL compat_InitializeCriticalSection(u32 p) {
    typedef void (STDCALL *F)(u32);
    static F f;
    if (!f) f = (F)resolve_os("KERNEL32.DLL", "InitializeCriticalSection");
    if (f) f(p);
}

void CDECL compat_LeaveCriticalSection(u32 p) {
    typedef void (STDCALL *F)(u32);
    static F f;
    if (!f) f = (F)resolve_os("KERNEL32.DLL", "LeaveCriticalSection");
    if (f) f(p);
}

/* R2 binary behavior used three arguments here.  The corrected build uses
 * the four arguments proven by C1's retained fstat.c call site.
 */
#if DEC1991_CORRECTED
u32 CDECL compat_GetFileTime(u32 h,u32 create,u32 access,u32 write) {
    typedef u32 (STDCALL *F)(u32,u32,u32,u32);
    static F f;
    if (!f) f = (F)resolve_os("KERNEL32.DLL", "GetFileTime");
    return f ? f(h,create,access,write) : 0;
}
#else
u32 CDECL compat_GetFileTime(u32 a,u32 b,u32 c) {
    typedef u32 (STDCALL *F)(u32,u32,u32);
    static F f;
    if (!f) f = (F)resolve_os("KERNEL32.DLL", "GetFileTime");
    return f ? f(a,b,c) : 0;
}
#endif

/* ------------------------------------------------------------------------- */
/* Early structure-layout bridges.                                           */
/* ------------------------------------------------------------------------- */

/* Dec-1991 WIN32_FIND_DATAA has cFileName at +0x24.
 * Released Win32 has dwReserved0/dwReserved1 at +0x24/+0x28 and cFileName
 * at +0x2c.  The old tools provide a large enough buffer, so let modern
 * Kernel32 fill it, then collapse the 8-byte reserved gap in place.
 *
 * Modern bytes +0x2c .. +0x13f = 0x114 bytes (filename + alt filename tail).
 */
static void finddata_modern_to_1991(u32 p) {
    u8 *d = (u8 *)p;
    u32 i;
    if (!d) return;
    for (i = 0; i < 0x114; i++) d[0x24 + i] = d[0x2c + i];
}

u32 CDECL compat_FindFirstFileA(u32 pattern,u32 olddata) {
    typedef u32 (STDCALL *F)(u32,u32);
    static F f;
    u32 h;

    if (!f) f = (F)resolve_os("KERNEL32.DLL", "FindFirstFileA");
    if (!f) return 0xffffffffu;

    h = f(pattern, olddata);
    if (h != 0xffffffffu) finddata_modern_to_1991(olddata);
    return h;
}

#if DEC1991_CORRECTED
u32 CDECL compat_FindNextFileA(u32 h,u32 olddata) {
    typedef u32 (STDCALL *F)(u32,u32);
    static F f;
    u32 ok;

    if (!f) f = (F)resolve_os("KERNEL32.DLL", "FindNextFileA");
    if (!f) return 0;

    ok = f(h, olddata);
    if (ok) finddata_modern_to_1991(olddata);
    return ok;
}
#else
/* Preserve the R2 incremental patch exactly: direct adapter, no layout shift. */
DECL2(FindNextFileA, "FindNextFileA")
#endif

/* Early NT STARTUPINFOA is the released structure's prefix through
 * lpReserved2: 0x38 bytes.  Released i386 STARTUPINFOA is 0x44 bytes.
 */
void CDECL compat_GetStartupInfoA(u32 oldp) {
    typedef void (STDCALL *F)(u32);
    static F f;
    u8 n[0x44];
    u32 i;

    if (!f) f = (F)resolve_os("KERNEL32.DLL", "GetStartupInfoA");

    for (i = 0; i < 0x44; i++) n[i] = 0;
    *(u32 *)n = 0x44;

    if (f) f((u32)n);

    if (oldp) {
        for (i = 0; i < 0x38; i++) ((u8 *)oldp)[i] = n[i];
        *(u32 *)oldp = 0x38;
    }
}

u32 CDECL compat_CreateProcessA(
    u32 app,u32 cmd,u32 psa,u32 tsa,u32 inherit,u32 flags,
    u32 env,u32 cwd,u32 oldsi,u32 pi)
{
    typedef u32 (STDCALL *F)(
        u32,u32,u32,u32,u32,u32,u32,u32,u32,u32);
    static F f;
    u8 n[0x44];
    u32 i;

    if (!f) f = (F)resolve_os("KERNEL32.DLL", "CreateProcessA");

    for (i = 0; i < 0x44; i++) n[i] = 0;
    if (oldsi) {
        for (i = 0; i < 0x38; i++) n[i] = ((u8 *)oldsi)[i];
    }
    *(u32 *)n = 0x44;

    return f ? f(app,cmd,psa,tsa,inherit,flags,env,cwd,(u32)n,pi) : 0;
}

/* ------------------------------------------------------------------------- */
/* NTDLL compatibility.                                                      */
/* ------------------------------------------------------------------------- */

/* No live reference in the recovered compiler/linker text required the old
 * DbgPrint behavior.  Keep the harmless cdecl stub used by R2.
 */
u32 CDECL compat_DbgPrint(u32 fmt) {
    (void)fmt;
    return 0;
}

/* Dec-1991 CRT call form: RtlUnwind(TargetFrame,TargetIp,ExceptionRecord).
 * Released 32-bit NTDLL adds a fourth ReturnValue argument and uses stdcall.
 */
void CDECL compat_RtlUnwind(u32 frame,u32 ip,u32 er) {
    typedef void (STDCALL *F)(u32,u32,u32,u32);
    static F f;
    if (!f) f = (F)resolve_os("NTDLL.DLL", "RtlUnwind");
    if (f) f(frame, ip, er, 0);
}

/* setjmp / longjmp are in dec1991_setjmp.s because the exact register and
 * stack restoration semantics should not be entrusted to a C compiler.
 */

/* No CRT startup: this is the DLL entry point used directly by lld-link. */
int STDCALL compat_DllMain(u32 h,u32 reason,u32 reserved) {
    (void)h;
    (void)reason;
    (void)reserved;
    return 1;
}
