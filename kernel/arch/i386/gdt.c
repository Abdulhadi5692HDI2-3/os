#include "gdt.h"

typedef struct {
    uint16_t LimitLow;
    uint16_t BaseLow;
    uint8_t BaseMiddle;
    uint8_t Access;
    uint8_t Flags;
    uint8_t BaseHigh;
} __attribute__((packed)) GdtEntry;

typedef struct {
    uint16_t Limit;
    uint32_t Base;
} __attribute__((packed)) GdtPtr;

extern void GdtFlush(uint32_t gdt);
static void GdtSetGate(int, uint32_t, uint32_t, uint8_t, uint8_t);

GdtEntry GdtEntries[5];
GdtPtr GdtPtr_;

void InitGDT() {
    GdtPtr_.Limit = (sizeof(GdtEntry) * 5) - 1;
    GdtPtr_.Base = (uint32_t)&GdtEntries;

    // Our segments
    GdtSetGate(0, 0, 0, 0, 0); // The NULL descriptor
    GdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel Mode Code descriptor
    GdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Mode Data descriptor
    GdtSetGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Mode Code descriptor
    GdtSetGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User Mode Data descriptor

    GdtFlush((uint32_t)&GdtPtr_);
}

static void GdtSetGate(int gatenum, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
    GdtEntries[gatenum].BaseLow = (base & 0xFFFF);
    GdtEntries[gatenum].BaseMiddle = (base >> 16) & 0xFF;
    GdtEntries[gatenum].BaseHigh = (base >> 24) & 0xFF;

    GdtEntries[gatenum].LimitLow = (limit & 0xFFFF);
    GdtEntries[gatenum].Flags = (limit >> 16) & 0x0F;
    GdtEntries[gatenum].Flags |= flags & 0xF0;

    GdtEntries[gatenum].Access = access;
}
