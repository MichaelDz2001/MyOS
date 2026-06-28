//апаратний таймер для переривів IRQ0

#include <stdint.h>
#include "include/pit.h"

extern "C" void outb(uint16_t port, uint8_t val);

static inline void io_wait() {
    outb(0x80, 0);
}

extern "C" void pit_init(int freq) {
    if (freq <= 0) return;
    
    const uint32_t PIT_BASE_FREQ = 1193182u;
    uint32_t divider = PIT_BASE_FREQ / (uint32_t)freq;
    if (divider == 0) divider = 1;
    if (divider > 0xFFFFu) divider = 0xFFFFu;

    outb(0x43, 0x34);
    io_wait();

    uint8_t lo = (uint8_t)(divider & 0xFF);
    uint8_t hi = (uint8_t)((divider >> 8) & 0xFF);

    outb(0x40, lo);
    io_wait();
    outb(0x40, hi);
    io_wait();
}
