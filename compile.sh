#!/usr/bin/env bash
nasm -felf32 boot/bootstrap.asm -o boot/bootstrap.o
i686-elf-gcc -std=gnu99 -ffreestanding -g -c kernel/oskrnl.c -o kernel/oskrnl.o
i686-elf-gcc -std=gnu99 -ffreestanding -g -c kernel/vga/write.c -o kernel/write.o
i686-elf-gcc -std=gnu99 -ffreestanding -g -c kernel/serialio/io.c -o kernel/io.o
i686-elf-gcc -std=gnu99 -ffreestanding -g -c external/printf/printf.c -o external/printf.o
i686-elf-gcc -ffreestanding -nostdlib -g -T linker.ld boot/bootstrap.o kernel/oskrnl.o kernel/write.o kernel/io.o external/printf.o -o oskrnl.elf -lgcc