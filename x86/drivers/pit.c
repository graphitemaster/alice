#include <isr.h>
#include <irq.h>
#include <io.h>

static int           pit_hz    = 1000;
static volatile long pit_ticks = 0;

static void pit_handler(isr_reg_t regs) {
    ++pit_ticks;
}

void pit_init(void) {
    isr_register(IRQ0, &pit_handler);

    uint32_t di = 1193180 / pit_hz;
    uint8_t  lo = (uint8_t)(di & 0xFF);
    uint8_t  hi = (uint8_t)((di >> 8) & 0xFF);

    outb(0x43, 0x36); /* Change the PIT */
    outb(0x40, lo);
    outb(0x40, hi);
}
