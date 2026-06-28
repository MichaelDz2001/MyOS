; multiboot-заголовки та підготовка до загрузки

BITS 32
global start
extern kmain

section .multiboot
align 4
_multiboot_header:
    dd 0x1badb002
    dd 0x00000003
    dd -(0x1badb002 + 0x3)

section .data
gdt_start:
    dq 0x0000000000000000
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

section .text
start:
    cli
    mov esp, 0x90000
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 0x08:protected_entry

protected_entry:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    mov esp, 0x90000
    call kmain

.halt:
    cli
    hlt
    jmp .halt
