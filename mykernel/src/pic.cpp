//контролер переривів (PIC)

#include <stdint.h>
#include "include/pic.h"

extern "C" uint8_t inb(uint16_t port);
extern "C" void outb(uint16_t port, uint8_t val);

static inline void io_wait() {
    outb(0x80, 0);
}

extern "C" void pic_remap(int offset1, int offset2) {
    uint8_t a1 = inb(0x21);
    uint8_t a2 = inb(0xA1);

    outb(0x20, 0x11); io_wait();
    outb(0xA0, 0x11); io_wait();

    outb(0x21, (uint8_t)offset1); io_wait();
    outb(0xA1, (uint8_t)offset2); io_wait();

    outb(0x21, 0x04); io_wait();
    outb(0xA1, 0x02); io_wait();

    outb(0x21, 0x01); io_wait();
    outb(0xA1, 0x01); io_wait();

    outb(0x21, (uint8_t)(a1 & ~0x03));
    outb(0xA1, a2);
}

extern "C" void pic_init(int freq) {
    pic_remap(0x20, 0x28);
    outb(0x21, 0xFC);
    outb(0xA1, 0xFF);
}

extern "C" void pic_send_eoi(int irq) {
    if (irq < 0) return;
    if (irq >= 8) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
    io_wait();
}
