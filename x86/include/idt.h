#ifndef ALICE_X86_IDT_HDR
#define ALICE_X86_IDT_HDR
#include <stdint.h>

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void idt_init(void);

#endif
