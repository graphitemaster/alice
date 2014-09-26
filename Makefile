CC     ?= clang
LD     ?= ld
CFLAGS  = -nostdlib -ffreestanding -std=c99 -Iinclude
LDFLAGS = -nostdlib
QEMU    = qemu-system-i386
SILENT  = @
ECHO    = echo

# Kernel stdlib source
KLIBC_SRCS = \
    klibc/string.c

ALICE_SRCS = \
    alice.c \
    loader/elf.c

include x86/include.mk

# Objects
KLIBC_OBJS = $(KLIBC_SRCS:.c=.o)
ALICE_OBJS = $(ALICE_SRCS:.c=.o)
ARCH_OBJS  = $(ARCH_SRCS:.c=.o) $(ARCH_DRIVER_SRCS:.c=.o) $(ARCH_ASMS:.S=.o)

# Banners
ifeq ($(SILENT), @)
	BANNER_SRC = \
		$(SILENT) case $< in \
			*klibc*) \
				$(ECHO) "[klibc]  $<" \
				;; \
			*) \
				$(ECHO) "[kernel] $<" \
				;; \
		esac
else
	BANNER_SRC =
endif

LIBCBIN = klibc.a
KERNBIN = kernel.bin

.PHONY: test

%.o:%.c
	$(BANNER_SRC)
	$(SILENT) $(CC) -c $(CFLAGS) $(ARCH_CFLAGS) $< -o $@

%.o:%.S
	$(BANNER_SRC)
	$(SILENT) $(AS) $(ARCH_AFLAGS) $< -o $@

$(KERNBIN): $(LIBCBIN) $(ALICE_OBJS) $(ARCH_OBJS)
	$(SILENT) $(LD) $(LDFLAGS) $(ARCH_LDFLAGS) $(ALICE_OBJS) $(ARCH_OBJS) $< -o $@

$(LIBCBIN): $(KLIBC_OBJS)
	$(SILENT) ar rcs $@ $^

test: $(KERNBIN)
	$(SILENT) $(ECHO) "Running"
	$(SILENT) $(QEMU) -kernel $(KERNBIN) -serial stdio -display sdl

clean:
	rm -f $(KLIBC_OBJS) $(ALICE_OBJS) $(ARCH_OBJS)
	rm -f $(LIBCBIN) $(KERNBIN)
