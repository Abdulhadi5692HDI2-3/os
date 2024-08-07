#include "idt.h"
#include <stdbool.h>
#include "pic.h"

typedef struct {
    uint16_t IsrLow;
    uint16_t KernelCs;
    uint8_t Zero;
    uint8_t Attributes;
    uint16_t IsrHigh;
} __attribute__((packed)) IdtEntry;

typedef struct {
    uint16_t Limit;
    uint32_t Base;
} __attribute__((packed)) Idtr_t;

__attribute__((aligned(0x10)))
static IdtEntry IDT[256];

static Idtr_t Idtr;

__attribute__((noreturn))
void ExceptionHandle(void);
void ExceptionHandle(void) {
    __asm__ volatile ("cli");
    __asm__ volatile ("hlt");
}

void IdtSetDescriptor(uint8_t vector, void* isr, uint8_t attributes) {
    IdtEntry* descriptor = &IDT[vector];

    descriptor->IsrLow = (uint32_t)isr & 0xFFFF;
    descriptor->KernelCs = 0x08;
    descriptor->Attributes = attributes;
    descriptor->IsrHigh = (uint32_t)isr >> 16;
    descriptor->Zero = 0;
}

static bool vectors[256];

extern void* IsrStubTable[];

void IdtInit() {
    Idtr.Base = (uintptr_t)&IDT[0];
    Idtr.Limit = (uint16_t)sizeof(IdtEntry) * 256 - 1;

    PIC_Remap(0x20, 0xA0);

    for (uint8_t vector = 0; vector < 32; vector++) {
        IdtSetDescriptor(vector, IsrStubTable[vector], 0x8E);
        vectors[vector] = true;
    }
    
    __asm__ volatile ("lidt %0" : : "m"(Idtr));
    __asm__ volatile ("sti");
}