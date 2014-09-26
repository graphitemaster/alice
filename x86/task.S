.global task_readip
.global task_switch

task_readip:
    pop %eax
    jmp *%eax

task_switch:
    mov     $0x23,  %ax
    mov     %ax,    %ds
    mov     %ax,    %es
    mov     %ax,    %fs
    mov     %esp,   %eax
    push    $0x23
    push    %eax
    pushf
    pop     %eax
    or      $0x200, %eax
    push    %eax
    push    $0x1B
    push    $task_iret
    iret

task_iret:
    ret
