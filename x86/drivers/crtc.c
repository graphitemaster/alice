#include <io.h>
#include <stdint.h>

static uint16_t *crtc_ram      = (uint16_t*)0xB8000;
static uint8_t   crtc_cursor_x = 0;
static uint8_t   crtc_cursor_y = 0;

#define PORT 0x3D4 /* Command port */

static void crtc_cursor_move(void) {
    uint16_t location = crtc_cursor_y * 80 + crtc_cursor_x;
    outb(PORT, 14);
    outb(PORT + 1, location >> 8);
    outb(PORT, 15);
    outb(PORT + 1, location);
}

static void crtc_scroll(void) {
    unsigned char attribute = (0 << 4) | (15 & 0x0F); /* white on black */
    uint16_t      blanking  = 0x20 | (attribute << 8);

    if (crtc_cursor_y >= 25) {
        /* Move up a line */
        for (int i = 0; i < 24 * 80; i++)
            crtc_ram[i] = crtc_ram[i + 80];
        for (int i = 24 * 80; i < 25 * 80; i++)
            crtc_ram[i] = blanking;

        crtc_cursor_y = 24;
    }
}

void crtc_write(char ch) {
    unsigned char bg        = 0;
    unsigned char fg        = 15;
    unsigned char ab        = (bg << 4) | (fg & 0x0F);
    uint16_t      attribute = ab << 8;
    uint16_t     *location;

    /* Handle backspace */
    if (ch == 0x08 && crtc_cursor_x)
        crtc_cursor_x--;

    /* Handle tab */
    if (ch == 0x09)
        crtc_cursor_x = (crtc_cursor_x + 8) & ~7;

    /* Carrige return */
    if (ch == '\r')
        crtc_cursor_x = 0;

    if (ch == '\n') {
        crtc_cursor_x = 0;
        crtc_cursor_y++;
    }

    /* All other printable characters */
    if (ch >= ' ') {
        location    = crtc_ram + (crtc_cursor_y * 80 + crtc_cursor_x);
        location[0] = ch | attribute;
        crtc_cursor_x++;
    }

    /* Move forward */
    if (crtc_cursor_x >= 80) {
        crtc_cursor_x = 0;
        crtc_cursor_y++;
    }

    crtc_scroll();
    crtc_cursor_move();
}

void crtc_writev(const char *string) {
    while (*string)
        crtc_write(*string++);
}

void crtc_clear(void) {
    uint8_t  ab       = (0 << 4) | (15 & 0x0F);
    uint16_t blanking = 0x20 | (ab << 8);

    for (int i = 0; i < 80 * 25; i++)
        crtc_ram[i] = blanking;

    crtc_cursor_x = 0;
    crtc_cursor_y = 0;

    crtc_cursor_move();
}
