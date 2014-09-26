.align 4

.macro ISR_NOERR index
    .global isr\index
    isr\index:
        cli
        push $0
        push $\index
        jmp isr_common
.endm

.macro ISR_ERROR index
    .global isr\index
    isr\index:
        cli
        push $\index
        jmp isr_common
.endm

ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7
ISR_ERROR 8
ISR_NOERR 9
ISR_ERROR 10
ISR_ERROR 11
ISR_ERROR 12
ISR_ERROR 13
ISR_ERROR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31

/* Kernel proper interrupt service routine handler */
.extern isr_handler

isr_common:
    pusha                       /* Push all registers */


    mov     %ds,        %ax
    push    %eax                /* Save data segment descrptor */

    mov     $0x10,      %ax
    mov     %ax,        %ds
    mov     %ax,        %es
    mov     %ax,        %fs

    call    isr_handler
    pop     %ebx                /* Restore original data segment descriptor */
    mov     %bx,        %ds
    mov     %bx,        %es
    mov     %bx,        %fs

    popa                        /* Restore registers */
    add     $8,         %esp    /* Cleanup error code and ISR # */
    iret                        /* pop CS, EIP, EFLAGS, SS and ESP */
