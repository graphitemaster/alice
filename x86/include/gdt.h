#ifndef ALICE_X86_GDT_HDR
#define ALICE_X86_GDT_HDR
#include <stdint.h>

void gdt_set_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void gdt_init(void);

#endif
