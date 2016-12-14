#ifndef _SYSTEM_IHANDLER_H_INCLUDED_
#define _SYSTEM_IHANDLER_H_INCLUDED_

#define ADR_BOOTINFO 0x00000ff0
#define ADR_DISKIMG  0x00100000

/* はりぼてOSシステムコール番号 */

#define API_PUTCHAR    0x01
#define API_PUTSTR0    0x02
#define API_PUTSTR1    0x03
#define API_END        0x04
#define API_OPENWIN    0x05
#define API_PUTSTRWIN  0x06
#define API_BOXFILWIN  0x07
#define API_INITMALLOC 0x08
#define API_MALLOC     0x09
#define API_FREE       0x0A
#define API_POINT      0x0B
#define API_REFRESHWIN 0x0C
#define API_LINEWIN    0x0D
#define API_CLOSEWIN   0x0E
#define API_GETKEY     0x0F
#define API_ALLOCTIMER 0x10
#define API_INITTIMER  0x11
#define API_SETTIMER   0x12
#define API_FREETIMER  0x13
#define API_BEEP       0x14
#define API_FOPEN      0x15
#define API_FCLOSE     0x16
#define API_FSEEK      0x17
#define API_FSIZE      0x18
#define API_FREAD      0x19
#define API_CMDLINE    0x1A
#define API_GETLANG    0x1B

/* はりぼて友の会共通システムコール番号 */

#define TOMO_GETMOUSE  0x1000
#define TOMO_GETTICK   0x1001
#define TOMO_RDMSR     0x1002
#define TOMO_SETLANG   0x1003
#define TOMO_SYSINFO   0x1004
#define TOMO_SYSTIME   0x1005
#define TOMO_WRMSR     0x1006

/* BayOSシステムコール番号 */

#define BAYOS_THREAD_ID     0x3000
#define BAYOS_THREAD_JOIN   0x3001
#define BAYOS_THREAD_KILL   0x3002
#define BAYOS_THREAD_YIELD  0x3003
#define BAYOS_MESG_SEND     0x3004
#define BAYOS_MESG_RECEIVE  0x3005
#define BAYOS_GET_WSTR_INFO 0x3006

/* C言語の関数宣言 */
extern "C" {
    /* ブート時のパラメータ (0x0ff0-0x0fff) */
    typedef struct BOOT_PARAM {
        byte cyls;     /* ブートセクタはどこまでディスクを読んだのか */
        byte leds;     /* ブート時のキーボードのLEDの状態 */
        byte bpps;     /* ビデオモード  何ビットカラーか */
        byte reserve;  /* 予約 */
        word screen_x; /* 画面解像度 */
        word screen_y; /* 画面解像度 */
        byte *vram;    /* VRAMのアドレス */
    };

    /* I/O系 */
    void io_hlt(void);
    void io_cli(void);
    void io_sti(void);
    void io_stihlt(void);
    int  io_in8(int port);
    int  io_in16(int port);
    int  io_in32(int port);
    void io_out8(int port, int data);
    void io_out16(int port, int data);
    void io_out32(int port, int data);
    int  io_load_eflags(void);
    void io_store_eflags(int eflags);
    void load_gdtr(int limit, int addr);
    void load_idtr(int limit, int addr);
    int  load_cr0(void);
    void store_cr0(int cr0);
    void load_tr(int tr);
    void clts(void);
    void fnsave(int *addr);
    void frstor(int *addr);

    /* ユーティリティ系 */
    unsigned int get_physical_size(unsigned int start, unsigned int end);
    void farjmp(int eip, int cs);
    void farcall(int eip, int cs);

    /* 割り込み系 */
    void asm_inthandler07(void);
    void asm_inthandler0c(void);
    void asm_inthandler0d(void);
    void asm_inthandler20(void);
    void asm_inthandler21(void);
    void asm_inthandler27(void);
    void asm_inthandler2c(void);

    /* システムコール系 */
    void asm_hrb_api(void);
    void asm_end_app(void);

    /* 割り込み系 */
    int* inthandler07(int *esp);
    int* inthandler0d(int *esp);
    int* inthandler0c(int *esp);
    void inthandler20(int *esp);
    void inthandler21(int *esp);
    void inthandler27(int *esp);
    void inthandler2c(int *esp);
    void start_app(int eip, int cs, int esp, int ds, int *tss_esp0);

    /* システムコール系 */
    int* hrb_api(int edi, int esi, int ebp, int esp, int ebx, int edx, int ecx, int eax);
}

#endif
