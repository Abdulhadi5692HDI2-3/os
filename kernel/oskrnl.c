/**
 * oskrnl.c
 */
#include <stdint.h>
#include <stddef.h>
#include "vga/write.h"

void SystemInitalize() {
    // initalize things
    
}

void kmain() {
    SystemInitalize();
    WritePut('A');
}
