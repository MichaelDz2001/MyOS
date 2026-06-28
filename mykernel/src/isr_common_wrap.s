BITS 32
global isr_common
extern isr_common_c

section .text
isr_common:
    mov eax, [esp + 4]
    lea edx, [esp + 8]
    push edx
    push eax
    call isr_common_c
    add esp, 8

    ret
