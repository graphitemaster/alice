#include <multiboot.h>
#include <elf.h>

void arch_init(void);
void crtc_clear(void);
void crtc_writev(const char *string);
void serial_writev(const char *string);
void task_switch(void);
uint32_t task_readip(void);

void alice_main(multiboot_t *multiboot, uint32_t stack) {
    Elf32 alice_elf = elf_parse_kernel(multiboot, &alice_elf);

    arch_init();
    crtc_clear();

    crtc_writev("Welcome to Alice");
}
