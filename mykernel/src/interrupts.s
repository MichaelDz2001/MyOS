; створення низькорівневих stub'ів і регістрація в IDT

BITS 32
global idt_load
global idt_descriptor
extern isr_common

section .data
idt_descriptor:
    dw 0
    dd 0

section .text
%macro ISR_STUB 1
global isr_stub_%1
isr_stub_%1:
    cli
    pushfd
    pushad
    lea eax, [esp]
    push eax
    push dword %1
    call isr_common
    add esp, 8
    popad
    popfd
    sti
    iret
%endmacro

%assign i 0
%rep 48
    ISR_STUB i
%assign i i+1
%endrep

idt_load:
    lidt [idt_descriptor]

    ret
