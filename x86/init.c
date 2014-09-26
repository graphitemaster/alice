#include <gdt.h>
#include <idt.h>
#include <pic.h>
#include <isr.h>
#include <sys.h>
#include <pit.h>

#include <misc.h>

void arch_init(void) {
    sync_cli();

    gdt_init(); /* Global descriptor table */
    idt_init(); /* Interrupt descriptor table */
    pic_init(); /* Programmable interrupt controller*/
    isr_init(); /* Interrupt service routines and interrupt requests */
    sys_init(); /* System calls */
    pit_init(); /* Programmable interval timer */
}
