# MyOS
MyOS is an x86_64-from-scratch operating system prototype. It includes a minimal Multiboot-compatible boot, an IDT with NASM stubs, basic IRQ/PIC + PIT setup, and a small C++ kernel that prints to VGA. The project is built on Linux and runs in QEMU using a GRUB-generated ISO.

# Features
 - From-scratch kernel (written from the ground up)
 - Multiboot header (NASM)
 - IDT + interrupt stubs (NASM + C++)
 - VGA output
 - PIC (master/slave) and PIT initialization
 - Runs in QEMU (ISO via GRUB)

# Requirements
Install the following tools (exact package names can vary by distro):
 - build-essential
 - gcc-multilib
 - binutils
 - nasm
 - make
 - qemu-system-x86 (or equivalent: qemu-system-i386)
 - gdb-multiarch
 - grub-pc-bin
 - xorriso
You also need Linux userland 32-bit toolchain support because the build uses -m32.

# Build
chmod +x script_os
bash -x ./script_os

This produces:
 - build/kernel.elf
 - build/myos.iso

# Run (QEMU)
Normal run:
qemu-system-i386 -cdrom build/myos.iso -boot d

# DEBUG (GDB)
1. Start QEMU waiting for the debugger:
qemu-system-i386 -cdrom build/myos.iso -S -s

2. In another terminal, start GDB:
gdb-multiarch build/kernel.elf

3. In GDB:
target remote :1234

# Autor
MichaelDz2001

Some parts of the documentation were assisted by AI. Code was written by the author.
