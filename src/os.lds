/* https://vanya.jp.net/os/haribote.html#hrb */
OUTPUT_FORMAT("binary");

SECTIONS
{
    .head 0x0 : {
        LONG(64 * 1024)  /*  0 : stack+.data+heap $B$NBg$-$5!J(B4KB$B$NG\?t!K(B */
        LONG(0x69726148)      /*  4 : $B%7%0%M%A%c(B "Hari" */
        LONG(0)               /*  8 : mmarea $B$NBg$-$5!J(B4KB$B$NG\?t!K(B */
        LONG(0x310000)        /* 12 : $B%9%?%C%/=i4|CM!u(B.data$BE>Aw@h(B */
        LONG(SIZEOF(.data))   /* 16 : .data$B%5%$%:(B */
        LONG(LOADADDR(.data)) /* 20 : .data$B$N=i4|CMNs$N%U%!%$%k0LCV(B */
        LONG(0xE9000000)      /* 24 : 0xE9000000 */
        LONG(HariMain - 0x20) /* 28 : $B%(%s%H%j%"%I%l%9(B - 0x20 */
        LONG(0)               /* 32 : heap$BNN0h!J(Bmalloc$BNN0h!K3+;O%"%I%l%9(B */
    }

    .text : { *(.text) }

    .data 0x310000 : AT ( ADDR(.text) + SIZEOF(.text) ) {
        *(.data)
        *(.rodata*)
        *(.bss)
    }

    /DISCARD/ : { *(.eh_frame) }

}
