# Runtime message-file comparison

They are related but **not byte-identical**. The shared format and numbering strongly support common driver lineage.

## CL386.ERR unified diff

```diff
--- OS2/CL386.ERR
+++ NT1991/CL386.ERR
@@ -1,17 +1,18 @@
 				/* error messages */
 
 2001	"too many symbols predefined with /D"
+2002	"conflict in memory-model specification"
 2003	"missing source file name"
 2008	"limit of %s exceeded at '%s'"
 2011	"only one floating-point option allowed"
 2012	"too many linker flags on command line"
+2013	"incomplete model specification"
 2016	"'%s' and '%s' are incompatible"
 2018	"cannot open linker response file"
 2019	"cannot overwrite the source/object file, '%s'"
 2020	"%s option requires extended keywords to be enabled (/Ze)"
 2021	"invalid numerical argument '%s'"
 2022	"cannot open help file, '%s'"
-2023	"invalid model specification - small model only"
 2027	"could not execute '%s'"
 2028	"too many open files, cannot redirect '%s'"
 2030	"INTERNAL COMPILER ERROR in '%s'\n\t\tContact Microsoft Product Support Services"
@@ -22,12 +23,14 @@
 
 4001	"listing overrides assembly output"
 4002	"ignoring unknown flag '%s'"
+4003	"different processors selected for code generation"
 4005	"could not locate '%s';\nPlease enter new file name (full path) or Ctrl-C to quit: "
 4007	"/C ignored (must also specify /P or /E or /EP)"
+4009	"threshold only for far/huge data, ignored"
 4011	"preprocessing overrides source listing"
 4012	"function declarations override source listing"
 4013	"combined listing overrides object listing"
 4014	"invalid value '%d' for '%s'; default '%d' is used"
+4018	".DEF files supported in protected mode only"
 4019	"string too long; truncated to '%d' characters"
-4020	"'%s' : missing argument, option ignored"
 4000	"UNKNOWN COMMAND LINE WARNING\n\t\tContact Microsoft Product Support Services"
```

## CL386.MSG unified diff

```diff
--- OS2/CL386.MSG
+++ NT1991/CL386.MSG
@@ -5,9 +5,7 @@
 /O enable optimization (same as /Ot)
 /Oa ignore aliasing
 /Od disable optimizations
-/Oe automatic register allocation
-/Og enable global optimization
-/Oi enable intrinsic inlining
+/Oi enable intrinsic functions
 /Ol enable loop optimizations
 /On disable "unsafe" optimizations
 /Op enable precision optimizations
@@ -17,15 +15,11 @@
 /Ow assume aliasing in function calls
 /Ox max. optimization (/Oegilt /Gs)
 -CODE GENERATION-
-/G3 80386 instructions (default)
-/G4 optimize for 486
 /Gm put strings in constant segment
 /Gc Pascal style function calls
+/Gd C calling convention
 /Gs no stack checking
-/Gt[number] data size threshold
 /Gw Windows entry sequence
-/Gz stdcall returns (default)
-/Gd cdecl returns
 -OUTPUT FILES-
 /Fa[assembly listing file]
 /Fb[bound executable file]
@@ -34,22 +28,19 @@
 /Fl[object listing file]
 /Fm[map file]
 /Fo<object file>
-/Fr[source browser info file]
-/FR[extended source browser info file]
 /Fs[source listing file]
-/Fa /Fs mixed assembly and source
 -PREPROCESSOR-
 /C don't strip comments
 /D<name>[=text] define macro
 /E preprocess to stdout
 /EP same as /E but no #line
 /I<name> add #include path
-/P preprocess to file, no #line
+/P preprocess to file
 /U<name> remove predefined macro
 /u remove all predefined macros
 /X ignore "standard places"
 -LANGUAGE-
-/Za disable non ansi extensions
+/Za disable extensions
 /Zd line number information
 /Ze enable extensions (default)
 /Zg generate declarations
@@ -59,8 +50,6 @@
 /Zs syntax check only
 -FLOATING POINT-
 /FPa calls with altmath
-/FPc calls with emulator
-/FPc87 calls with 8087 library
 /FPi inline with emulator (default)
 /FPi87 inline with 8087
 -SOURCE LISTING-
@@ -73,7 +62,6 @@
 /c compile only, no link
 /H<number> external name length
 /J default char type is unsigned
-/qc use quick compile feature
 /Tc<file> compile file without .c
 /V<string> set version string
 /W<number> warning level
@@ -83,11 +71,7 @@
 /Fx[MASM's cross-reference file] 
 -LINKING-
 /F <hex_number> stack size (hex. bytes)
-/Lc link compatibility mode executable
-/Lr link compatibility mode executable
-/Lp link protect mode executable
 /link [linker_options_and_libraries]
 /ML link C runtime as part of DLL
 /MD use C runtime as DLL
 /MT support multi-thread
-
```
