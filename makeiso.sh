#!/usr/bin/bash
mkdir isodir
cp oskrnl.elf isodir
mkdir -p isodir/boot/grub
cp config/grub.cfg isodir/boot/grub
grub-mkrescue -o os.iso isodir