/**
 * oskrnl.c
 */
#include <stdint.h>
#include <stddef.h>
#include "vga/write.h"
#include "../external/printf/printf.h"
#include "arch/i386/gdt.h"
#include "arch/i386/idt.h"

void _putchar(char character) {
    WritePut(character);
}

void SystemInitalize() {
    // initalize things
    InitGDT();
    printf("[status] GDT LOADED!\n");
    IdtInit();
    printf("[status] IDT LOADED!\n");
    
}

void kmain() {
    SystemInitalize();
    printf("Hello world!\n");
}
