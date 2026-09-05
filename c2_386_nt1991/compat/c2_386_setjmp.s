/* Minimal x86 cdecl setjmp/longjmp pair for the C2_386 compatibility DLL.
 * The compiler treats jmp_buf as opaque. We store seven DWORDs:
 *   EBP, EBX, ESI, EDI, post-RET ESP, return EIP, FS:[0] SEH chain.
 */
.text
.globl _compat_setjmp
_compat_setjmp:
    movl 4(%esp), %eax
    movl %ebp, 0(%eax)
    movl %ebx, 4(%eax)
    movl %esi, 8(%eax)
    movl %edi, 12(%eax)
    leal 4(%esp), %edx
    movl %edx, 16(%eax)
    movl 0(%esp), %edx
    movl %edx, 20(%eax)
    movl %fs:0, %edx
    movl %edx, 24(%eax)
    xorl %eax, %eax
    ret

.globl _compat_longjmp
_compat_longjmp:
    movl 4(%esp), %edx
    movl 8(%esp), %eax
    testl %eax, %eax
    jne 1f
    incl %eax
1:
    movl 24(%edx), %ecx
    movl %ecx, %fs:0
    movl 0(%edx), %ebp
    movl 4(%edx), %ebx
    movl 8(%edx), %esi
    movl 12(%edx), %edi
    movl 16(%edx), %esp
    jmp *20(%edx)
