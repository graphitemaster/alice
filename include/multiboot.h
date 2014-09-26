#ifndef ALICE_MULTIBOOT_HDR
#define ALICE_MULTIBOOT_HDR
#include <stdint.h>

typedef struct {
    uint32_t    flags;
    uint32_t    mem_lower;
    uint32_t    mem_upper;
    uint32_t    boot_device;
    uint32_t    cmdline;
    uint32_t    mods_count;
    uint32_t    mods_addr;
    uint32_t    num;
    uint32_t    size;
    uint32_t    addr;
    uint32_t    shndx;
    uint32_t    mmap_length;
    uint32_t    mmap_addr;
    uint32_t    drives_length;
    uint32_t    drives_addr;
    uint32_t    boot_loader_name;
    uint32_t    apm_table;
    uint32_t    vbe_control_info;
    uint32_t    vbe_mode_info;
    uint32_t    vbe_mode;
    uint32_t    vbe_interface_seg;
    uint32_t    vbe_interface_off;
    uint32_t    vbe_interface_len;
} __attribute__((packed)) multiboot_t;

#endif
