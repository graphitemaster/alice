#include <stdint.h>

typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

static gdt_entry_t gdt_entries[6];
static gdt_ptr_t   gdt_ptr;

/* Global descriptor table flush in gdt_flush.S */
extern void gdt_flush(uint32_t);

void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;
    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = ((limit >> 16) & 0xF) | ((gran & 0x0F) << 4);
    gdt_entries[num].access      = access;
}

void gdt_init(void) {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 6) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;
    gdt_set_gate(0, 0, 0,       0,    0);   /* Empty segment */
    gdt_set_gate(1, 0, 0xFFFFF, 0x98, 0xC); /* KCode segment */
    gdt_set_gate(2, 0, 0xFFFFF, 0x92, 0xC); /* KData segment */
    gdt_set_gate(3, 0, 0xFFFFF, 0xF8, 0xC); /* UCode segment */
    gdt_set_gate(4, 0, 0xFFFFF, 0xF2, 0xC); /* UData segment */
    gdt_flush((uint32_t)&gdt_ptr);
}
