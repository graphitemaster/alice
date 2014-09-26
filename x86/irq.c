#include <irq.h>
#include <isr.h>
#include <idt.h>
#include <io.h>

extern void irq0(void);
extern void irq1(void);
extern void irq2(void);
extern void irq3(void);
extern void irq4(void);
extern void irq5(void);
extern void irq6(void);
extern void irq7(void);
extern void irq8(void);
extern void irq9(void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);

extern isr_handle_t isr_handles[256];

void irq_handler(volatile isr_reg_t regs) {
    /* Send EOI */
    if (regs.intn >= 40)
        outb(0xA0, 0x20);

    /* Send reset */
    outb(0x20, 0x20);

    /* Call handler */
    if (isr_handles[regs.intn].handler)
        isr_handles[regs.intn].handler(regs);
}

void irq_init(void) {
    idt_set_gate(IRQ0,  (uint32_t)irq0,  0x08, 0x8E);
    idt_set_gate(IRQ1,  (uint32_t)irq1,  0x08, 0x8E);
    idt_set_gate(IRQ2,  (uint32_t)irq2,  0x08, 0x8E);
    idt_set_gate(IRQ3,  (uint32_t)irq3,  0x08, 0x8E);
    idt_set_gate(IRQ4,  (uint32_t)irq4,  0x08, 0x8E);
    idt_set_gate(IRQ5,  (uint32_t)irq5,  0x08, 0x8E);
    idt_set_gate(IRQ6,  (uint32_t)irq6,  0x08, 0x8E);
    idt_set_gate(IRQ7,  (uint32_t)irq7,  0x08, 0x8E);
    idt_set_gate(IRQ8,  (uint32_t)irq8,  0x08, 0x8E);
    idt_set_gate(IRQ9,  (uint32_t)irq9,  0x08, 0x8E);
    idt_set_gate(IRQ10, (uint32_t)irq10, 0x08, 0x8E);
    idt_set_gate(IRQ11, (uint32_t)irq11, 0x08, 0x8E);
    idt_set_gate(IRQ12, (uint32_t)irq12, 0x08, 0x8E);
    idt_set_gate(IRQ13, (uint32_t)irq13, 0x08, 0x8E);
    idt_set_gate(IRQ14, (uint32_t)irq14, 0x08, 0x8E);
    idt_set_gate(IRQ15, (uint32_t)irq15, 0x08, 0x8E);
}
