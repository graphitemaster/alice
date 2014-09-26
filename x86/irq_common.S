.macro IRQ ident byte
    .global irq\ident
    .type irq\ident, @function
    irq\ident:
        cli
        push $0x00
        push $\byte
        jmp irq_common
.endm

IRQ 0,  32
IRQ 1,  33
IRQ 2,  34
IRQ 3,  35
IRQ 4,  36
IRQ 5,  37
IRQ 6,  38
IRQ 7,  39
IRQ 8,  40
IRQ 9,  41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

/* Kernel proper interrupt request handler */
.extern irq_handler

irq_common:
    pusha                       /* Push all registers */


    mov     %ds,        %ax
    push    %eax                /* Save data segment descrptor */

    mov     $0x10,      %ax
    mov     %ax,        %ds
    mov     %ax,        %es
    mov     %ax,        %fs

    call    irq_handler

    pop     %ebx                /* Restore original data segment descriptor */
    mov     %bx,        %ds
    mov     %bx,        %es
    mov     %bx,        %fs

    popa                        /* Restore registers */
    add     $8,         %esp    /* Cleanup error code and ISR # */

    sti                         /* Interrupts */
    iret                        /* pop CS, EIP, EFLAGS, SS and ESP */
