#ifndef ALICE_X86_ISR_HDR
#define ALICE_X86_ISR_HDR
#include <stdint.h>

typedef struct {
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t intn;
    uint32_t errn;
    uint32_t eip;
    uint32_t cs;
    uint32_t cflags;
    uint32_t uesp;
    uint32_t ss;
} isr_reg_t;

typedef struct isr_handle_s isr_handle_t;

/* Interrupt handler callback type */
typedef void (*isr_handler_t)(isr_reg_t);

struct isr_handle_s {
    isr_handler_t handler;
    uint8_t       number;
};

/* Faults, traps and exceptions */
typedef enum {
    ISR_INT_DIVIDEBYZERO,
    ISR_INT_DEBUG,
    ISR_INT_NMI,
    ISR_INT_BREAKPOINT,
    ISR_INT_OVERFLOW,
    ISR_INT_OUTOFBOUNDS,
    ISR_INT_INVALIDOPCODE,
    ISR_INT_NOCOPROCESSOR,
    ISR_INT_DOUBLEFAULT,
    ISR_INT_SEGMENTOVERRUN,
    ISR_INT_BADTSS,
    ISR_INT_SEGMENTNOTPRESENT,
    ISR_INT_STACKFAULT,
    ISR_INT_PROTECTIONFAULT,
    ISR_INT_PAGEFAULT,
    ISR_INT_UNKNOWN,
    ISR_INT_COPROCESSORFAULT,
    ISR_INT_ALIGNMENTCHECK,
    ISR_INT_MACHINECHECK
} isr_int_t;

void isr_register(uint8_t number, isr_handler_t handler);
void isr_init(void);

#endif
