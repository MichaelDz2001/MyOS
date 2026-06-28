// загальна обробка переривів (між асемблерними stub'ами та ядром системи)

#include <stdint.h>
#include "isr_common.h"
#include "pic.h"
#include "pit.h"

extern "C" void isr_common_c(int vec, uint32_t *regs) {
    (void)regs;

    if (vec == 0x20) {
        timer_tick();
        pic_send_eoi(0);
        return;
    }

    if (vec == 0x21) {
       uint8_t sc = inb(0x60);
       keyboard_handle_scancode(sc);
       pic_send_eoi(1);
       return;
    }

    if (vec < 32) {
       const char hex[] = "123456789ABCDEF";
       vga_putc('E'); vga_putc('X'); vga_putc(':');
       vga_putc(hex[(vec >> 4) & 0xF]);
       vga_putc(hex[vec & 0xF]);
       for (;;) asm volatile("hlt");
    }

    if (vec >= 0x20 && vec <= 0x2F) {
        int irq = vec - 0x20;
        pic_send_eoi(irq);
    }
}
