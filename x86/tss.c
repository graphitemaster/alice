#include <stdint.h>
#include <string.h>
#include <gdt.h>

typedef struct {
    uint32_t prevtss;
    uint32_t esp0;      /* Stack pointer to load when kernel mode change */
    uint32_t ss0;       /* Stack segmeent to laod when kernel mode change */
    uint32_t esp1;      /* Unused */
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomap_base;
} __attribute__((packed)) tss_entry_t;

static tss_entry_t tss_entry;

/* Task segment selector flush in tss_flush.S */
extern void tss_flush(void);

static void tss_write(uint32_t num, uint16_t ss0, uint32_t esp0) {
    uint32_t base = (uint32_t)&tss_entry;
    uint32_t limit = base + sizeof(tss_entry);
    gdt_set_gate(num, base, limit, 0xE9, 0x00);
    memset(&tss_entry, 0, sizeof(tss_entry));
    tss_entry.ss0  = ss0;
    tss_entry.esp0 = esp0;
    tss_entry.cs   = 0x0B;
    tss_entry.ss   = 0x13;
    tss_entry.ds   = 0x13;
    tss_entry.es   = 0x13;
    tss_entry.fs   = 0x13;
    tss_entry.gs   = 0x13;
}

void tss_init(void) {
    tss_write(5, 0x10, 0x00);
    tss_flush();
}
