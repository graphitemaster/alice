/* Debugging serial output driver */
#include <io.h>

#define PORT 0x3F8 /* COM1 */

void serial_init(void) {
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x80);
    outb(PORT + 0, 0x03);
    outb(PORT + 1, 0x00);
    outb(PORT + 3, 0x03);
    outb(PORT + 2, 0xC7);
    outb(PORT + 4, 0x0B);
}

int serial_transmit_empty(void) {
    return inb(PORT + 5) & 0x20;
}

void serial_write(const char ch) {
    while (serial_transmit_empty() == 0)
        ;
    outb(PORT, ch);
}

void serial_writev(const char *string) {
    while (*string)
        serial_write(*(string++));
}
