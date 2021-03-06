OBJS_BOOTPACK	= bootpack.o graphic.o dsctbl.o int.o fifo.o \
								keyboard.o mouse.o memory.o sheet.o timer.o mtask.o \
								window.o console.o file.o \
								nasmfunc.o hankaku.o mysprintf.o mystrcmp.o mystrncmp.o

MAKE		= make -r
DEL			= rm -rf
DOCKER	= sudo docker
CFLAGS	= -m32 -fno-pic -nostdlib

# Default

default:
	$(MAKE) run

# File generation rule

ipl10.bin: ipl10.asm
	nasm $< -o $@ -l ipl10.lst

asmhead.bin: asmhead.asm
	nasm $< -o $@ -l asmhead.lst

nasmfunc.o: nasmfunc.asm
	nasm -g -f elf $< -o $@ -l nasmfunc.lst

hello.hrb: hello.asm
	nasm $< -o $@ -l hello.lst

hello2.hrb: hello2.asm
	nasm $< -o $@ -l hello.lst

convHankakuTxt: convHankakuTxt.c
	gcc $< -o $@

hankaku.c: hankaku.txt convHankakuTxt
	./convHankakuTxt

bootpack.hrb: $(OBJS_BOOTPACK) os.lds
	gcc $(CFLAGS) -march=i486 -T os.lds -Xlinker -Map=bootpack.map -g $(OBJS_BOOTPACK) -o $@

haribote.sys : asmhead.bin bootpack.hrb
	cat asmhead.bin bootpack.hrb > haribote.sys

haribote.img: ipl10.bin haribote.sys hello.hrb hello2.hrb
	mformat -f 1440 -C -B ipl10.bin -i haribote.img ::
	mcopy -i haribote.img haribote.sys ipl10.asm hello.hrb hello2.hrb ::

# General rule

%.o: %.c
	gcc $(CFLAGS) -c $*.c -o $*.o

# Commands

build_docker_image:
	$(DOCKER) build -t haribos .

asm:
	$(MAKE) ipl10.bin

img:
	$(MAKE) haribote.img
	@chmod 777 haribote.img
	$(MAKE) clean

build:
	$(DOCKER) run --rm -v `pwd`:/haribos haribos:latest make img

run: build
	qemu-system-i386 -m 32M -drive file=haribote.img,format=raw,if=floppy -boot a

clean:
	-$(DEL) *.bin
	-$(DEL) *.o
	-$(DEL) *.sys
	-$(DEL) *.lst
	-$(DEL) *.hrb
	-$(DEL) *.map
	-$(DEL) convHankakuTxt
	-$(DEL) hankaku.c
