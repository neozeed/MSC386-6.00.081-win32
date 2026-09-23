/*
 * 24-byte December-1991 i386 jmp_buf.
 *
 * Layout:
 *   +00 EBP
 *   +04 EBX
 *   +08 ESI
 *   +0c EDI
 *   +10 saved post-return ESP
 *   +14 saved return EIP
 *
 * The earlier experimental compatibility shim incorrectly added a seventh
 * DWORD at +18 for FS:[0].  In COFF.EXE that overwrote FirstArchive; retained
 * C2 symbols independently prove its jmp_buf objects are exactly 0x18 bytes.
 */

        .text

        .globl _compat_setjmp
        .p2align 2
_compat_setjmp:
        movl    4(%esp), %eax
        movl    %ebp, 0(%eax)
        movl    %ebx, 4(%eax)
        movl    %esi, 8(%eax)
        movl    %edi, 12(%eax)
        leal    4(%esp), %edx
        movl    %edx, 16(%eax)
        movl    (%esp), %edx
        movl    %edx, 20(%eax)
        xorl    %eax, %eax
        ret

        .globl _compat_longjmp
        .p2align 2
_compat_longjmp:
        movl    4(%esp), %edx
        movl    8(%esp), %eax
        testl   %eax, %eax
        jne     1f
        incl    %eax
1:
        movl    0(%edx), %ebp
        movl    4(%edx), %ebx
        movl    8(%edx), %esi
        movl    12(%edx), %edi
        movl    16(%edx), %esp
        jmp     *20(%edx)
