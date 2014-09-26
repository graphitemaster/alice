.set MB_MAGIC,    0x1BADB002
.set MB_FLAGS,    0x7 # page align, memory info, graphics
.set MB_CHECKSUM, -(MB_MAGIC + MB_FLAGS)

.section .boot
.align 4
.int MB_MAGIC
.int MB_FLAGS
.int MB_CHECKSUM
.int 0x00000000 /* header_addr */
.int 0x00000000 /* load_addr */
.int 0x00000000 /* load_end_addr */
.int 0x00000000 /* bss_end_addr */
.int 0x00000000 /* entry_addr */

/* Request linear graphic mode */
.int 0x00000000 /* linear */
.byte 0
.byte 0
.byte 32

/* Our stack resides in .bss */
.section .stack, "aw", @nobits
alice_stack_bottom:
.skip 16384 /* 16KiB */
alice_stack_top:

.section .text
.global alice_start
.type alice_start, @function

alice_start:
    mov     $alice_stack_top, %esp
    pushl   %esp
    pushl   %ebx

    cli
    call    alice_main

    cli
alice_hang:
    hlt
    jmp alice_hang
