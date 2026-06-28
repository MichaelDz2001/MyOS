#ifndef HW_H
#define HW_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void isr_common_c(int vec, uint32_t *regs);
void timer_tick(void);
void pic_send_eoi(int irq);
uint8_t inb(uint16_t port);
void keyboard_handle_scancode(uint8_t sc);
void vga_putc(char c);

#ifdef __cplusplus
}
#endif

#endif
