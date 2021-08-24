OBJS_BOOTPACK	= bootpack.o graphic.o dsctbl.o int.o fifo.o \
								keyboard.o mouse.o nasmfunc.o hankaku.o mysprintf.o

MAKE		= make -r
DEL			= rm -rf
DOCKER	= sudo docker
CFLAGS	= -m32 -fno-pic -nostdlib

# Default

default:
	$(MAKE) run

# File generation rule

ipl10.bin: ipl10.asm
	nasm ipl10.asm -o ipl10.bin -l ipl10.lst

asmhead.bin: asmhead.asm
	nasm $< -o $@ -l asmhead.lst

nasmfunc.o: nasmfunc.asm
	nasm -g -f elf $< -o $@ -l nasmfunc.lst

convHankakuTxt: convHankakuTxt.c
	gcc $< -o $@

hankaku.c: hankaku.txt convHankakuTxt
	./convHankakuTxt

bootpack.hrb: $(OBJS_BOOTPACK) os.lds
	gcc $(CFLAGS) -march=i486 -T os.lds -g $(OBJS_BOOTPACK) -o $@

haribote.sys : asmhead.bin bootpack.hrb
	cat asmhead.bin bootpack.hrb > haribote.sys

haribote.img: ipl10.bin haribote.sys
	mformat -f 1440 -C -B ipl10.bin -i haribote.img ::
	mcopy -i haribote.img haribote.sys ::

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

run:
	$(DOCKER) run --rm -v `pwd`:/haribos haribos:latest make img
	qemu-system-i386 -m 32M -drive file=haribote.img,format=raw,if=floppy -boot a

clean:
	-$(DEL) *.bin
	-$(DEL) *.o
	-$(DEL) *.sys
	-$(DEL) *.lst
	-$(DEL) *.hrb
	-$(DEL) *.img
