December 1991 NT C/386 toolchain — universal retranslation R2
===================================================================

R2 keeps the proven R1 universal translation and adds one narrowly-scoped
C3_386 repair for the /Fa long-double listing failure.

What was happening
------------------
C3's statically-linked CRT contains __cfltcvt_tab with six callbacks.
__cfltcvt_init initializes entries 0..4, but entry 5 remains __fptrap.

printf/output.c uses entry 5 specifically for the 12-byte long-double path.
C3's own assembly listing contains a "%.32Le" formatter, so an extended
floating-point constant reaches that uninitialized callback and produces:

    runtime error R6002
    - floating point not loaded

This is not an overall x87 failure. It is an incomplete long-double-to-text
formatter hookup in this December-1991 C3 build.

R2 repair
---------
The generic modernizer detects the exact C3 code/data signatures. Only for C3
it adds a small .c3fp code section and redirects __cfltcvt_tab[5] to an
adapter:

    12-byte historical long double
             |
             v
       C3's own ___ldtod
             |
             v
         8-byte double
             |
             v
       C3's own __cfltcvt

The exact hexadecimal DT payload emitted by C3 is untouched. The decimal
comment is formatted after conversion to double, so it can lose precision
relative to a true 80-bit decimal formatter, but /Fa no longer depends on the
missing historical callback.

Static verification
-------------------
  C3 .c3fp RVA: 0xb0000
  __cfltcvt_tab[5] value: 0xc0000
  wrapper CALL targets: 0x27e4a, 0x287ba
  callback slot still has HIGHLOW relocation: yes

The workaround is C3-specific, while modernize_dec1991_pe.py remains generic:
it activates this repair by exact signatures, not by filename. A newly linked
SIMPLE.EXE will simply receive the ordinary PE modernization.

Suggested first test
--------------------

    cl386 /c /Faastro.asm astro.c

If that completes, inspect astro.asm and then rebuild Phoon normally.

Keep R1 / the previous known-good binaries until R2 has passed your runtime
test.
