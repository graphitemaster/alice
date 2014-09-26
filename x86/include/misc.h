#ifndef ALICE_X86_MISC_HDR
#define ALICE_X86_MISC_HDR

static inline void cli(void) {
    __asm__ __volatile__("cli");
}

static inline void sync_cli(void) {
    __sync_synchronize();
    cli();
}

static inline void sti(void) {
    __asm__ __volatile__("sti");
}

static inline void sync_sti(void) {
    __sync_synchronize();
    sti();
}

#endif
