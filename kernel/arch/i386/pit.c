#include "pit.h"
#include "../../serialio/io.h"
#include "../../../external/printf/printf.h"

uint32_t tick = 0;

void timer_callback() {
    tick++;
    printf("Tick: 0x%d\n", tick);
}

void InitalizeTimer(uint32_t Frequency) {
    uint32_t divisor = 1193180 / Frequency;

    outb(0x43, 0x36);

    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor>>8) & 0xFF);

    outb(0x40, low);
    outb(0x40, high);
}