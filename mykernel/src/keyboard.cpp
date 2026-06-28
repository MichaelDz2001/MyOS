#include <stdint.h>

extern "C" void keyboard_handle_scancode(uint8_t sc);

static const char sc_map[128] = {
    0, 27,'1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',0,
    '\\','z','x','c','v','b','n','m',',','.','/',0,'*',0, ' ',
};

extern "C" void keyboard_handle_scancode(uint8_t sc) {
    if (sc & 0x80) return;
    if (sc < sizeof(sc_map) && sc_map[sc]) {
        extern void vga_putc(char);
        vga_putc(sc_map[sc]);
    }
}
