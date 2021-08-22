#include "bootpack.h"

// IRQ: interrupt request
// IMR: interrupt mask register
// ICW: initial control word
void init_pic() {
  io_out8(PIC0_IMR, 0xff);  // reject all interrupt
  io_out8(PIC1_IMR, 0x44);  // reject all interrupt

  io_out8(PIC0_ICW1, 0x11);    // edge trigger mode
  io_out8(PIC0_ICW2, 0x20);    // IRQ0-7 receive INT20-27
  io_out8(PIC0_ICW3, 1 << 2);  // PIC1 connect with IRQ2
  io_out8(PIC0_ICW4, 0x01);    // none buffer mode

  io_out8(PIC1_ICW1, 0x11);  // edge trigger mode
  io_out8(PIC1_ICW2, 0x28);  // IRQ-8 receive INT28-2f
  io_out8(PIC1_ICW3, 2);     // PIC1 connect with IRQ2
  io_out8(PIC1_ICW4, 0x01);  // none buffer mode

  io_out8(PIC0_IMR, 0xfb);  // fobidden without PIC1
  io_out8(PIC1_IMR, 0xff);  // reject all interrupt

  return;
}

void inthandler21(int *esp) {
  struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
  boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32 * 8 - 1, 15);
  putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, "INT 21(IRQ-1): OS/2 keyboard");
  for (;;) {
    io_hlt();
  }
}

void inthandler2c(int *esp) {
  struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
  boxfill8(binfo->vram, binfo->scrnx, COL8_000000, 0, 0, 32 * 8 - 1, 15);
  putfonts8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, "INT 21(IRQ-1): OS/2 mouse");
  for (;;) {
    io_hlt();
  }
}

void inthandler27(int *esp) {
	io_out8(PIC0_OCW2, 0x67);
	return;
}
