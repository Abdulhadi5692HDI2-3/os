/**
 * oskrnl.c
 */
#include <stdint.h>
#include <stddef.h>
#include "vga/write.h"
#include "../external/printf/printf.h"

void _putchar(char character) {
    WritePut(character);
}

void SystemInitalize() {
    // initalize things
    
}

void kmain() {
    SystemInitalize();
    printf("Hello world!\n");
}
