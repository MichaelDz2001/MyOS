// формування таблиць переривів і дескриптора

#include <stdint.h>
#include <string.h>
#include "include/idt.h"
#include "include/pic.h"
#include "include/pit.h"

#ifdef __cplusplus
extern "C" {
#endif

static IDTEntry idt[256];
static IDTPtr idtp;

void set_idt_entry(int n, void (*handler)(void), uint16_t selector, uint8_t type_attr) {
    uint32_t addr = (uint32_t)handler;
    idt[n].offset_low = (uint16_t)(addr & 0xFFFF);
    idt[n].selector = selector;
    idt[n].zero = 0;
    idt[n].type_attr = type_attr;
    idt[n].offset_high = (uint16_t)((addr >> 16) & 0xFFFF);
}

void idt_init(void) {
    memset(idt, 0, sizeof(idt));

    const uint16_t CODE_SELECTOR = 0x08;
    const uint8_t INTERRUPT_GATE = 0x8E;

    set_idt_entry(0,  isr_stub_0,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(1,  isr_stub_1,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(2,  isr_stub_2,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(3,  isr_stub_3,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(4,  isr_stub_4,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(5,  isr_stub_5,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(6,  isr_stub_6,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(7,  isr_stub_7,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(8,  isr_stub_8,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(9,  isr_stub_9,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(10,  isr_stub_10,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(11,  isr_stub_11,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(12,  isr_stub_12,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(13,  isr_stub_13,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(14,  isr_stub_14,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(15,  isr_stub_15,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(16,  isr_stub_16,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(17,  isr_stub_17,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(18,  isr_stub_18,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(19,  isr_stub_19,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(20,  isr_stub_20,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(21,  isr_stub_21,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(22,  isr_stub_22,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(23,  isr_stub_23,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(24,  isr_stub_24,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(25,  isr_stub_25,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(26,  isr_stub_26,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(27,  isr_stub_27,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(28,  isr_stub_28,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(29,  isr_stub_29,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(30,  isr_stub_30,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(31,  isr_stub_31,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(32,  isr_stub_32,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(33,  isr_stub_33,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(34,  isr_stub_34,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(35,  isr_stub_35,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(36,  isr_stub_36,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(37,  isr_stub_37,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(38,  isr_stub_38,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(39,  isr_stub_39,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(40,  isr_stub_40,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(41,  isr_stub_41,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(42,  isr_stub_42,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(43,  isr_stub_43,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(44,  isr_stub_44,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(45,  isr_stub_45,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(46,  isr_stub_46,  CODE_SELECTOR, INTERRUPT_GATE);
    set_idt_entry(47,  isr_stub_47,  CODE_SELECTOR, INTERRUPT_GATE);

    idtp.limit = (uint16_t)(sizeof(idt) - 1);
    idtp.base = (uint32_t)&idt;

    memcpy(&idt_descriptor, &idtp, sizeof(idtp));

    idt_load();

    pic_init(60);

    pit_init(60);
    asm volatile("sti");
}

#ifdef __cplusplus
}
#endif
