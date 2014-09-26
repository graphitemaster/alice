#include <multiboot.h>
#include <string.h>
#include <elf.h>

Elf32 elf_parse_kernel(multiboot_t *multiboot, Elf32 *elf) {
    Elf32_Shdr *shdr = (Elf32_Shdr*)multiboot->addr;
    Elf32_Word shstrtab = shdr[multiboot->shndx].sh_addr;
    for (uint32_t i = 0; i < multiboot->num; i++) {
        const char *name = &((const char *)shdr[i].sh_name)[shstrtab];
        if (!strcmp(name, ".strtab")) {
            elf->strtab   = (const char *)shdr[i].sh_addr;
            elf->strtabsz = shdr[i].sh_size;
        }
        if (!strcmp(name, ".symtab")) {
            elf->symtab   = (Elf32_Sym*)shdr[i].sh_addr;
            elf->symtabsz = shdr[i].sh_size;
        }
    }
    return *elf;
}
