//таймер

#include <stdint.h>
#include "include/isr_common.h"
#include "include/timer.h"

extern "C" {
    volatile uint64_t ticks = 0;
}

extern "C" void timer_tick(void) {
    ticks++;

    const uint32_t UPDATE_PERIOD = 60;
    uint32_t local_cnt = 0;
    if (++local_cnt >= UPDATE_PERIOD) {
        local_cnt = 0;

        uint64_t t = ticks;
        const char hex[] = "0123456789ABCDEF";
        vga_putc('.');
        for (int i = 0; i < 4; i++) {
            vga_putc(hex[t & 0xF]);
            t >>= 4;
        }
    }
}
