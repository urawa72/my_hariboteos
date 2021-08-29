# my_hariboteos

## 環境

以下の環境で作業する。

```
$ lsb_release -a
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 20.04.2 LTS
Release:        20.04
Codename:       focal

$ docker --version
Docker version 20.10.8, build 3967b7d
```

必要なツールをインストールする。

```
$ sudo apt install -y ghex build-essential qemu-kvm nasm mtools

$ gcc --version
gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

$ qemu-system-i386 --version
QEMU emulator version 4.2.1 (Debian 1:4.2-3ubuntu6.17)
Copyright (c) 2003-2019 Fabrice Bellard and the QEMU Project developers

$ nasm --version
NASM version 2.14.02

$ mtools --version
mtools (GNU mtools) 4.0.24
configured with the following options: enable-xdf disable-vold disable-new-vold disable-debug enable-raw-term
```

## 作業メモ

### 04_day

`gcc`のバージョンが 9 系だと以下のエラーが発生した。

```
make -r haribote.img
make[1]: Entering directory '/home/urawa72/repos/github.com/urawa72/my_hariboteos/04_day/harib01'
nasm ipl10.asm -o ipl10.bin -l ipl10.lst
nasm asmhead.asm -o asmhead.bin -l asmhead.lst
nasm -g -f elf nasmfunc.asm -o nasmfunc.o -l nasmfunc.lst
gcc -march=i486 -m32 -fno-pie -nostdlib -T os.lds -g bootpack.c nasmfunc.o -o bootpack.hrb
/usr/bin/ld: section .note.gnu.property LMA [00000000000001a0,00000000000001bb] overlaps section .data LMA [000000000000019f,00000000000001ce]
collect2: error: ld returned 1 exit status
make[1]: *** [Makefile:18: haribote.hrb] Error 1
make[1]: Leaving directory '/home/urawa72/repos/github.com/urawa72/my_hariboteos/04_day/harib01'
make: *** [Makefile:31: img] Error 2
```

解決策がわからないため、gcc のバージョンを 7 系まで下げた Docker コンテナでビルドすることにした。

```
make -r haribote.img
make[1]: Entering directory '/haribos'
nasm ipl10.asm -o ipl10.bin -l ipl10.lst
nasm asmhead.asm -o asmhead.bin -l asmhead.lst
nasm -g -f elf nasmfunc.asm -o nasmfunc.o -l nasmfunc.lst
gcc -march=i486 -m32 -fno-pie -nostdlib -T os.lds -g bootpack.c nasmfunc.o -o bootpack.hrb
cat asmhead.bin bootpack.hrb > haribote.sys
mformat -f 1440 -C -B ipl10.bin -i haribote.img ::
mcopy -i haribote.img haribote.sys ::
make[1]: Leaving directory '/haribos'
```

### 09_day

qemu に「memory 128MB」と表示される。これは qemu のデフォルトのメモリ量が 128MB のため。任意の値は`-m 32M`のように指定できる。

### 13_day

harib10c でベンチマークを取るためのコードに修正して qemu で動かしたところ、画面は表示されるがタイマーやマウスが動かなくなった。

`bootstap.c`の無限ループから文字列出力をなくすと上記の現象が発生するようになった。そのため、10 秒タイマーで出力していた count の値を for 文の先頭で出力するようにした。根本的な解決策は不明のまま。

```c
for(;;) {
  count++;
  // NOTE: The screen freeses without thw following code
  my_sprintf(s, "");
  putfonts8_asc_sht(sht_win, 40, 28, COL8_000000, COL8_C6C6C6, s, 1);

  io_cli();
  ...
}
```

### 18_day

`#include <string.h>`ができないため、自作の`strcmp`関数を用意する。[Apple のオープンソースサイト](https://opensource.apple.com/source/Libc/Libc-262/ppc/gen/strcmp.c.auto.html)のコードを流用する。
