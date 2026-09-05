/* C2_386 Dec-1991 NT -> modern 32-bit Win32 compatibility DLL.
 *
 * The pre-release NT compiler imports BASE.DLL APIs using caller-cleanup
 * (cdecl). Modern Win32 fixed-argument APIs are stdcall. This shim preserves
 * the 1991 call surface and resolves current KERNEL32/NTDLL exports directly.
 *
 * setjmp/longjmp are supplied by c2_386_setjmp.s because modern 32-bit NTDLL
 * does not provide the old imported pair with this 1991 ABI.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void *ptr;
#define CDECL __cdecl
#define STDCALL __stdcall

static u8 lower_ascii(u8 c){return (c>='A'&&c<='Z')?(u8)(c+32):c;}
static int streq(const char*a,const char*b){while(*a&&*b){if(*a++!=*b++)return 0;}return *a==*b;}
static int mod_eq(const u16*w,u16 bytes,const char*a){u32 n=bytes/2,i=0;for(;i<n&&a[i];i++)if(lower_ascii((u8)w[i])!=lower_ascii((u8)a[i]))return 0;return i==n&&!a[i];}
static ptr get_peb(void){ptr p;__asm__("movl %%fs:0x30,%0":"=r"(p));return p;}
static ptr find_module(const char*name){
 u8*peb=(u8*)get_peb(),*ldr=*(u8**)(peb+0x0c),*head=ldr+0x14,*node=*(u8**)head;
 while(node!=head){ptr base=*(ptr*)(node+0x10);u16 len=*(u16*)(node+0x24);u16*buf=*(u16**)(node+0x28);if(buf&&mod_eq(buf,len,name))return base;node=*(u8**)node;}return 0;
}
static ptr resolve_ord(ptr,u32,int);static ptr resolve_name_d(ptr,const char*,int);
static ptr expdir(ptr base,u32*rva,u32*size){u8*b=(u8*)base;if(*(u16*)b!=0x5a4d)return 0;u32 pe=*(u32*)(b+0x3c);if(*(u32*)(b+pe)!=0x4550)return 0;u8*o=b+pe+24;if(*(u16*)o!=0x10b)return 0;*rva=*(u32*)(o+96);*size=*(u32*)(o+100);return *rva?b+*rva:0;}
static ptr resolve_fwd(const char*f,int depth){char mod[64],fn[128];u32 i=0,j=0;int dot=0;if(depth>8)return 0;while(f[i]&&f[i]!='.'&&i<55){mod[i]=f[i];i++;}mod[i]=0;if(f[i]!='.')return 0;i++;for(j=0;mod[j];j++)if(mod[j]=='.')dot=1;if(!dot){mod[j++]='.';mod[j++]='d';mod[j++]='l';mod[j++]='l';mod[j]=0;}j=0;while(f[i]&&j<127)fn[j++]=f[i++];fn[j]=0;ptr mb=find_module(mod);if(!mb)return 0;if(fn[0]=='#'){u32 n=0;for(j=1;fn[j]>='0'&&fn[j]<='9';j++)n=n*10+fn[j]-'0';return resolve_ord(mb,n,depth+1);}return resolve_name_d(mb,fn,depth+1);}
static ptr finish(ptr base,u32 fr,u32 er,u32 es,int d){if(fr>=er&&fr<er+es)return resolve_fwd((char*)((u8*)base+fr),d+1);return (u8*)base+fr;}
static ptr resolve_name_d(ptr base,const char*name,int depth){u32 er,es;u8*ed=(u8*)expdir(base,&er,&es);if(!ed||depth>8)return 0;u32 nn=*(u32*)(ed+24),*names=(u32*)((u8*)base+*(u32*)(ed+32)),*funcs=(u32*)((u8*)base+*(u32*)(ed+28));u16*ords=(u16*)((u8*)base+*(u32*)(ed+36));for(u32 i=0;i<nn;i++)if(streq((char*)((u8*)base+names[i]),name))return finish(base,funcs[ords[i]],er,es,depth);return 0;}
static ptr resolve_ord(ptr base,u32 ord,int depth){u32 er,es;u8*ed=(u8*)expdir(base,&er,&es);if(!ed||depth>8)return 0;u32 first=*(u32*)(ed+16),nf=*(u32*)(ed+20);if(ord<first||ord>=first+nf)return 0;u32*funcs=(u32*)((u8*)base+*(u32*)(ed+28));return finish(base,funcs[ord-first],er,es,depth);}
static ptr resolve_os(const char*m,const char*n){ptr b=find_module(m);return b?resolve_name_d(b,n,0):0;}

#define D0(n,os) u32 CDECL compat_##n(void){typedef u32(STDCALL*F)(void);static F f;if(!f)f=(F)resolve_os("KERNEL32.DLL",os);return f?f():0;}
#define D1(n,os) u32 CDECL compat_##n(u32 a){typedef u32(STDCALL*F)(u32);static F f;if(!f)f=(F)resolve_os("KERNEL32.DLL",os);return f?f(a):0;}
#define D2(n,os) u32 CDECL compat_##n(u32 a,u32 b){typedef u32(STDCALL*F)(u32,u32);static F f;if(!f)f=(F)resolve_os("KERNEL32.DLL",os);return f?f(a,b):0;}
#define D3(n,os) u32 CDECL compat_##n(u32 a,u32 b,u32 c){typedef u32(STDCALL*F)(u32,u32,u32);static F f;if(!f)f=(F)resolve_os("KERNEL32.DLL",os);return f?f(a,b,c):0;}
#define D4(n,os) u32 CDECL compat_##n(u32 a,u32 b,u32 c,u32 d){typedef u32(STDCALL*F)(u32,u32,u32,u32);static F f;if(!f)f=(F)resolve_os("KERNEL32.DLL",os);return f?f(a,b,c,d):0;}
#define D5(n,os) u32 CDECL compat_##n(u32 a,u32 b,u32 c,u32 d,u32 e){typedef u32(STDCALL*F)(u32,u32,u32,u32,u32);static F f;if(!f)f=(F)resolve_os("KERNEL32.DLL",os);return f?f(a,b,c,d,e):0;}
#define D7(n,os) u32 CDECL compat_##n(u32 a,u32 b,u32 c,u32 d,u32 e,u32 f0,u32 g){typedef u32(STDCALL*F)(u32,u32,u32,u32,u32,u32,u32);static F f;if(!f)f=(F)resolve_os("KERNEL32.DLL",os);return f?f(a,b,c,d,e,f0,g):0;}

D1(CloseHandle,"CloseHandle")
D0(GetLastError,"GetLastError")
D1(ExitProcess,"ExitProcess")
D1(GetFileType,"GetFileType")
D1(GetStdHandle,"GetStdHandle")
D0(GetCommandLineA,"GetCommandLineA")
D0(GetEnvironmentStrings,"GetEnvironmentStringsA")
D0(GetVersion,"GetVersion")
D1(UnhandledExceptionFilter,"UnhandledExceptionFilter")
D5(WriteFile,"WriteFile")
D2(SetStdHandle,"SetStdHandle")
D1(FlushFileBuffers,"FlushFileBuffers")
D4(VirtualAlloc,"VirtualAlloc")
D4(SetFilePointer,"SetFilePointer")
D5(ReadFile,"ReadFile")
D3(GetModuleFileNameA,"GetModuleFileNameA")
D1(DeleteFileA,"DeleteFileA")
D7(CreateFileA,"CreateFileA")
D1(GetFileAttributesA,"GetFileAttributesA")
D1(SetEndOfFile,"SetEndOfFile")
D3(VirtualFree,"VirtualFree")

/* 1991 CRT passes a 0x38-byte STARTUPINFO prefix. Current x86 Win32 uses 0x44. */
void CDECL compat_GetStartupInfoA(u32 oldp){typedef void(STDCALL*F)(u32);static F f;u8 n[0x44];u32 i;if(!f)f=(F)resolve_os("KERNEL32.DLL","GetStartupInfoA");for(i=0;i<0x44;i++)n[i]=0;*(u32*)n=0x44;if(f)f((u32)n);if(oldp){for(i=0;i<0x38;i++)((u8*)oldp)[i]=n[i];*(u32*)oldp=0x38;}}

/* Imported for diagnostics; no compatibility-critical dependence was found. */
u32 CDECL compat_DbgPrint(u32 fmt){(void)fmt;return 0;}

/* Early CRT invokes RtlUnwind(TargetFrame, TargetIp, ExceptionRecord): 3 args. */
void CDECL compat_RtlUnwind(u32 frame,u32 ip,u32 er){typedef void(STDCALL*F)(u32,u32,u32,u32);static F f;if(!f)f=(F)resolve_os("NTDLL.DLL","RtlUnwind");if(f)f(frame,ip,er,0);}

int STDCALL compat_DllMain(u32 h,u32 reason,u32 reserved){(void)h;(void)reason;(void)reserved;return 1;}
