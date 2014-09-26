ARCH_SRCS = \
    x86/gdt.c \
    x86/idt.c \
    x86/init.c \
    x86/irq.c \
    x86/isr.c \
    x86/pic.c \
    x86/sys.c \
    x86/tss.c

ARCH_DRIVER_SRCS = \
    x86/drivers/crtc.c \
    x86/drivers/pit.c \
    x86/drivers/serial.c

ARCH_ASMS = \
    x86/boot.S \
    x86/gdt_flush.S \
    x86/idt_flush.S \
    x86/irq_common.S \
    x86/isr_common.S \
    x86/tss_flush.S \
    x86/task.S

ARCH_LDFLAGS = -melf_i386 -Tx86/link.ld
ARCH_CFLAGS  = -m32 -Ix86/include
ARCH_AFLAGS  = --32
