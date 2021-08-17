MAKE		= make -r
DEL			= rm -rf
DOCKER	= sudo docker

default:
	$(MAKE) run

ipl10.bin: ipl10.asm Makefile
	nasm ipl10.asm -o ipl10.bin -l ipl10.lst

asmhead.bin: asmhead.asm Makefile
	nasm asmhead.asm -o asmhead.bin -l asmhead.lst

nasmfunc.o: nasmfunc.asm Makefile
	nasm -g -f elf nasmfunc.asm -o nasmfunc.o -l nasmfunc.lst

convHankakuTxt: convHankakuTxt.c
	gcc convHankakuTxt.c -o convHankakuTxt

hankaku.c: hankaku.txt convHankakuTxt
	./convHankakuTxt

haribote.hrb: bootpack.c os.lds nasmfunc.o hankaku.c Makefile
	gcc -march=i486 -m32 -fno-pie -nostdlib -T os.lds -g bootpack.c hankaku.c nasmfunc.o -o bootpack.hrb

haribote.sys : asmhead.bin haribote.hrb Makefile
	cat asmhead.bin bootpack.hrb > haribote.sys

haribote.img: ipl10.bin haribote.sys Makefile
	mformat -f 1440 -C -B ipl10.bin -i haribote.img ::
	mcopy -i haribote.img haribote.sys ::

asm:
	$(MAKE) ipl10.bin

img:
	$(MAKE) haribote.img

run:
	$(DOCKER) run --rm -v `pwd`:/haribos haribos:latest make img
	qemu-system-i386 -drive file=haribote.img,format=raw,if=floppy -boot a

build_docker_image:
	$(DOCKER) build -t haribos .

clean:
	-$(DEL) *.bin
	-$(DEL) *.o
	-$(DEL) *.sys
	-$(DEL) *.lst
	-$(DEL) *.hrb
	-$(DEL) *.img
