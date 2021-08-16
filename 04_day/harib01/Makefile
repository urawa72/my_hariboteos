MAKE	= make -r
DEL		= rm -rf

default:
	$(MAKE) img

ipl10.bin: ipl10.asm Makefile
	nasm ipl10.asm -o ipl10.bin -l ipl10.lst

asmhead.bin: asmhead.asm Makefile
	nasm asmhead.asm -o asmhead.bin -l asmhead.lst

nasmfunc.o: nasmfunc.asm Makefile
	nasm -g -f elf nasmfunc.asm -o nasmfunc.o -l nasmfunc.lst

haribote.hrb: bootpack.c os.lds nasmfunc.o Makefile
	gcc -march=i486 -m32 -fno-pie -nostdlib -T os.lds -g bootpack.c nasmfunc.o -o bootpack.hrb

haribote.sys : asmhead.bin haribote.hrb Makefile
	cat asmhead.bin bootpack.hrb > haribote.sys

haribote.img: ipl10.bin haribote.sys Makefile
	mformat -f 1440 -C -B ipl10.bin -i haribote.img ::
	mcopy -i haribote.img haribote.sys ::

asm:
	$(MAKE) ipl10.bin

img:
	$(MAKE) haribote.img

build-with-docker:
	docker build -t haribos .
	docker run -v `pwd`:/haribos haribos make img

run:
	qemu-system-i386 -drive file=haribote.img,format=raw,if=floppy -boot a

clean:
	-$(DEL) *.bin
	-$(DEL) *.o
	-$(DEL) *.sys
	-$(DEL) *.lst
	-$(DEL) *.hrb

src_only:
	$(MAKE) clean
	-$(DEL) haribote.img
