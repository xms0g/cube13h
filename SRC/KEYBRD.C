#include "keybrd.h"

#define IRQ_PORT    0x20
#define KBC_IRQ     0x09
#define KBC_PORT    0x60
#define KBC_SCP     0x61
#define KBC_BREAK   0x80
#define SCP_KBC_DIS 0x80

static volatile unsigned char keys[256];

static void interrupt (*old_irq)();

static void interrupt kbc_irq_handler() {
    unsigned char code, val = 1;
    
    asm {
        cli
        in al, KBC_PORT
        mov code, al
        and al, KBC_BREAK
        jz PRESSED
        mov val, 0
        mov al, code
        sub al, KBC_BREAK
        mov code, al
    }
PRESSED:   
    keys[code] = val;
    
    asm {
        in al, KBC_SCP
        mov ah, al
        or al, SCP_KBC_DIS
        out KBC_SCP, al
        mov al, ah
        out KBC_SCP, al
        mov al, 0x20
        out IRQ_PORT, al
        sti
    }
}

/*
https://wiki.osdev.org/Interrupt_Vector_Table
+-----------+-----------+
|  Segment  |  Offset   |
+-----------+-----------+
4           2           0 
*/
void kbInit(void) {
    asm {
        push bx
        push es
        mov  bx, KBC_IRQ * 4                             //calculates the offset within the interrupt vector table for IRQ 9 (keyboard controller interrupt)
        xor  ax, ax
        mov  es, ax                                      //set up the segment register es to point to the beginning of the interrupt vector table.
        cli
        mov  ax, es:[bx]                                 //loads the old interrupt handler address for IRQ 9
        mov  word ptr old_irq, ax                        //stores the low word (offset) of the old interrupt handler in the variable old_irq.
        mov  ax, es:[bx + 2]                             //loads the segment of the old interrupt handler into the ax register.
        mov  word ptr old_irq[2], ax                     //stores the high word (segment) of the old interrupt handler in the variable old_irq.
        mov  word ptr es:[bx], offset kbc_irq_handler    //replaces the old interrupt handler address with the address of kbc_irq_handler.
        mov  es:[bx + 2], cs                             //replaces the old segment of the interrupt handler with the code segment (cs) of the current code.
        sti
        pop  es
        pop  bx
    }
}

void kbExit(void) {
    asm { 
        push bx
        push es
        mov  bx, KBC_IRQ * 4
        xor  ax, ax
        mov  es, ax
        cli
        mov  ax, word ptr old_irq
        mov  es:[bx], ax
        mov  ax, word ptr old_irq[2]
        mov  es:[bx + 2], ax
        sti
        pop  es
        pop  bx
    }
}

int kbHit(KeyCode key) {
    if (key < 0 || key >= 256) {
        return 0;
    }

    return keys[key];
}