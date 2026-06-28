#ifndef PIC_H
#define PIC_H

#include <stdint.h>

extern "C" void pic_remap(int offset1, int offset2);
extern "C" void pic_init(int freq);
extern "C" void pic_send_eoi(int irq);

#endif
