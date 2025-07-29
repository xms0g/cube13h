#include "VGA.H"
#include <malloc.h>
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
        asm {
            push es
            les di, offscreen
            mov ax, 0x00
            mov cx, 32000
            rep stosw
            pop es
        }  
        _initMode(VGA_MODE_13H);
    } 
}

void vgaExit(void) {
     farfree(offscreen);
    _initMode(VGA_MODE_3H);
}

void vgaClearOffscreen(char color) {
    int fill = (color << 8) | color;
    
    asm {
        push es
        les di, offscreen
        mov ax, fill
        mov cx, 32000
        rep stosw
        pop es
    }  
}

void vgaPutPixel(int x, int y, char color) {
    offscreen[(y << 8) + (y << 6) + x] = color;
}

void vgaUpdateVram(void) {
    _waitvretrace();
    
    asm {
        push ds
        push es
        les di, vram
        lds si, offscreen
        mov cx, 32000
        rep movsw
        pop es
        pop ds
    }
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
