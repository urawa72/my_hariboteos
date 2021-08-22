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

#define PORT_KEYDAT 0x0060

struct FIFO8 keyfifo;

void inthandler21(int *esp) {
  unsigned char data;
  io_out8(PIC0_OCW2, 0x61);  // notify PIC to IRQ-01 reception closed
  data = io_in8(PORT_KEYDAT);
  fifo8_put(&keyfifo, data);
  return;
}

struct FIFO8 mousefifo;

void inthandler2c(int *esp) {
  unsigned char data;
  io_out8(PIC1_OCW2, 0x64);  // notify PIC1 to IRQ-12 reception closed
  io_out8(PIC0_OCW2, 0x62);  // notify PIC0 to IRQ-02 reception closed
  data = io_in8(PORT_KEYDAT);
  fifo8_put(&mousefifo, data);
  return;
}

void inthandler27(int *esp) {
  io_out8(PIC0_OCW2, 0x67);
  return;
}
