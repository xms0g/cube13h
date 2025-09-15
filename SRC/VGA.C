#include "vga.h"
#include <malloc.h>
#include "mem.h"
// VGA Graphics Mode
#define VGA_MODE_13H 0x13
// VGA Text Mode
#define VGA_MODE_3H  0x3
#define VRAM_SIZE 64000u

static unsigned char far* vram;
static unsigned char far* offscreen;

static void _waitvretrace(void);
static void _initMode(int mode);

void vgaInit(void) {
    vram = (unsigned char far*)0xA0000000L;
    offscreen = (unsigned char far*)farmalloc(VRAM_SIZE);

    if (offscreen) {
        _memsetw(offscreen, 0, 32000);
        _initMode(VGA_MODE_13H);
    } 
}

void vgaExit(void) {
     farfree(offscreen);
    _initMode(VGA_MODE_3H);
}

void vgaClearOffscreen(char color) {
    int fill = (color << 8) | color;
    _memsetw(offscreen, fill, 32000);
}

void vgaPutPixel(int x, int y, char color) {
    offscreen[(y << 8) + (y << 6) + x] = color;
}

void vgaUpdateVram(void) {
    _waitvretrace();
    _memcpyw(vram, offscreen, 32000);
}

static void _waitvretrace(void) {
    asm { cli }
v1: 
    asm {
        mov dx, 0x03da 
        in al, dx      
        test al, 0x8   
        jnz v1
    }
v2:
    asm { 
        mov dx, 0x03da
        in al, dx
        test al, 0x8
        jz v2          
        sti
    }
}

static void _initMode(int mode) {
    asm {
        xor ah, ah    
        mov ax, mode
        int 0x10
    }
}
