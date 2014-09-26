#ifndef ALICE_X86_IO_HDR
#define ALICE_X86_IO_HDR
#include <stdint.h>

static inline void outb(uint16_t port, char value) {
    __asm__ __volatile__("outb %1, %0" : : "dN" (port), "a"((uint8_t)value));
}

static inline char inb(uint16_t port) {
    volatile char load;
    __asm__ __volatile__("inb %1, %0" : "=a"(load) : "dN"(port));
    return load;
}

#endif
