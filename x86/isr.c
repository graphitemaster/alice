#include <io.h>
#include <irq.h>
#include <isr.h>
#include <tss.h>
#include <misc.h>
#include <string.h>

isr_handle_t isr_handles[256];

void isr_register(uint8_t number, isr_handler_t handler) {
    isr_handle_t *handle;

    /* Disable interrupts when changing interrupt handler */
    sync_cli();
    handle          = &isr_handles[number];
    handle->handler = handler;
    handle->number  = number;
    sync_sti();
}

static void isr_ack(int isr) {
    if (isr >= IRQ0 && isr <= IRQ15) {
        if (isr >= 40)
            outb(0xA0, 0x20);
        outb(0x20, 0x20);
    }
}

void isr_handler(volatile isr_reg_t regs) {
    isr_ack(regs.intn);
    isr_handle_t *handle = &isr_handles[regs.intn];
    if (handle->handler)
        handle->handler(regs);
}

void isr_init(void) {
    /* Clear interrupt handlers */
    memset(&isr_handles, 0, sizeof(isr_handle_t) * 256);
    tss_init();
}
