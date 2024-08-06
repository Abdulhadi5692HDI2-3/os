#include <stdint.h>
#include <stddef.h>
#include "../serialio/io.h"

size_t CursorY = 0;
size_t CursorX = 0;
uint16_t *VideoMemory = (uint16_t*) 0xB8000;
// we need to move the "hardware" cursor
static void MoveCursor() {
	uint16_t CursorLocation = CursorY * 80 + CursorX;
	outb(0x3D4, 14);
	outb(0x3D5, CursorLocation >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, CursorLocation);
}

// at some point the screen will be filled up with things and crap
// so we need a way to scroll
static void Scroll() {
	uint8_t AttributeByte = (0 << 4) | (7 & 0x0F);
	uint16_t Blank = 0x20 | (AttributeByte << 8);

	if (CursorY >= 25) {
		int i;
		for (i = 0*80; i < 24*80; i++) {
			VideoMemory[i] = VideoMemory[i+80];
		}

		for (i = 24*80; i < 25*80; i++) {
			VideoMemory[i] = Blank;
		}

		CursorY = 24;
	}
}

void WritePut(char character) {
	uint8_t bg = 0;
	uint8_t fg = 7;

	uint8_t AttributeByte = (bg << 4) | (fg& 0x0F);

	uint16_t Attribute = AttributeByte << 8;
	uint16_t *Location;

	if (character == 0x08 && CursorX) {
		CursorX--;
	}

	else if (character == 0x09) {
		CursorX = (CursorX+8) & ~(8-1);
	}

	else if (character == '\r') {
		CursorX = 0;
	}

	else if (character == '\n') {
		CursorX = 0;
		CursorY++;
	}

	else if (character >= ' ') {
		Location = VideoMemory + (CursorY*80 + CursorX);
		*Location = character | Attribute;
		CursorX++;
	}

	if (CursorX >= 80) {
		CursorX = 0;
		CursorY++;
	}

	Scroll();
	MoveCursor();
}

void WriteCls() {
	uint8_t AttributeByte = (0 << 4) | (7 & 0x0F);
	uint16_t Blank = 0x20 | (AttributeByte << 8);

	int i;
	for (i = 0; i < 80*25; i++) {
		VideoMemory[i] = Blank;
	}

	CursorX = 0;
	CursorY = 0;
	MoveCursor();
}