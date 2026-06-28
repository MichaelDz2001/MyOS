#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    extern volatile uint64_t ticks;
    void timer_tick(void);

#ifdef __cplusplus
}
#endif

#endif
