// логіка ядра системи: ініціалізація, обробка, цикли

#include <stdint.h>

extern "C" void idt_init();
extern "C" void pic_remap(int offset1, int offset2);
extern "C" void outb(uint16_t port, uint8_t value);
extern "C" void isr_common_c(int vec, uint32_t *regs);

extern "C" void kmain() {
    volatile uint16_t* vga = (uint16_t*)0xB8000;
    const char *s = "Hallo Mann!";
    int i;
    for (i = 0; s[i]; ++i) vga[i] = (uint16_t)s[i] | (0x07 << 8);
    for (int j = i; j < 80; ++j) vga[j] = (uint16_t)' ' | (0x07 << 8);

    idt_init();

    pic_remap(0x20, 0x28);
    outb(0x21, 0x00);
    outb(0xA1, 0x00);

    asm volatile("sti");

    asm volatile("int $0x21");

    while (1) asm volatile("hlt");
}

/*extern "C" void kmain() {
    idt_init();
    volatile unsigned short* vga = (unsigned short*)0xB8000;
    const char *s = "Hallo Mann!";
    int i;
    for (i = 0; s[i]; ++i) vga[i] = (unsigned short)s[i] | (0x07 << 8);
    for (int j = i; j < 80; ++j) vga[j] = (unsigned short)' ' | (0x07 << 8);
    while (1) __asm__ volatile("hlt");
}*/
