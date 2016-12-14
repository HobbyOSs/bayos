#ifndef __SYSCALL_H__
#define __SYSCALL_H__

/* 定数宣言 */

#ifndef NULL
#define NULL        0
#endif

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long
#endif
typedef __SIZE_TYPE__ size_t;

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned int   dword;

/* マウス情報 */
typedef struct MOUSE_INFO {
    int x, y, button, state;
};

/* システム情報 */
typedef struct SYS_INFO {
    byte cyls;     /* ブートセクタはどこまでディスクを読んだのか */
    byte leds;     /* ブート時のキーボードのLEDの状態 */
    byte bpps;     /* ビデオモード  何ビットカラーか */
    byte reserve;  /* 予約 */
    word screen_x; /* 画面解像度 */
    word screen_y; /* 画面解像度 */
    byte *vram;    /* VRAMのアドレス */
    word os_type;  /* OSの種別 */
};

/* 日付情報 */
typedef struct TIME_INFO {
    int year, month, day, hour, minutes, second;
};

/* メッセージ種別 */

#define MSG_MOUSE_PRESSED      1
#define MSG_MOUSE_RELEASED     2
#define MSG_MOUSE_DRAGGED      3
#define MSG_MOUSE_MOVED        4
#define MSG_KEY_PRESSED        5
#define MSG_KEY_RELEASED       6
#define MSG_KEYBOARD_RAW_DATA  7
#define MSG_MOUSE_RAW_DATA     8
#define MSG_CONSOLE_PUTKEY     9
#define MSG_WINDOW_CLOSE       10
#define MSG_WINDOW_OPEN        11

/* メッセージ情報 */
typedef struct MSG_INFO {
    int type, from, arg1, arg2, arg3, arg4, len;
    byte* data;
};

/* ワイド文字列情報 */
typedef struct WSTR_INFO {
    int width, height, length;
};

/* 特殊キーコード */

#define L_CTRL_PRESSED     29
#define L_SHIFT_PRESSED    42
#define R_SHIFT_PRESSED    54
#define L_ALT_PRESSED      56
#define HOME_PRESSED       71
#define UP_PRESSED         72
#define PAGE_UP_PRESSED    73
#define LEFT_PRESSED       75
#define RIGHT_PRESSED      77
#define END_PRESSED        79
#define DOWN_PRESSED       80
#define PAGE_DOWN_PRESSED  81

#define L_CTRL_RELEASED    157
#define L_SHIFT_RELEASED   170
#define R_SHIFT_RELEASED   182
#define L_ALT_RELEASED     184
#define HOME_RELEASED      199
#define UP_RELEASED        200
#define PAGE_UP_RELEASED   201
#define LEFT_RELEASED      203
#define RIGHT_RELEASED     205
#define END_RELEASED       207
#define DOWN_RELEASED      208
#define PAGE_DOWN_RELEASED 209

/* はりぼてOS互換システムコール */
extern "C" {
    void  api_putchar(char c);
    void  api_putstr0(char* s);
    void  api_putstr1(char* s, int len);
    void  api_end();
    int   api_openwin(byte* buf, int xsiz, int ysiz, int col_inv, char* title);
    void  api_putstrwin(int win, int x, int y, int col, int len, char* str);
    void  api_boxfilwin(int win, int x0, int y0, int x1, int y1, int col);
    void  api_initmalloc(void);
    dword api_malloc(int size);
    void  api_free(void* addr);
    void  api_point(int win, int x, int y, int col);
    void  api_refreshwin(int win, int x0, int y0, int x1, int y1);
    void  api_linewin(int win, int x0, int y0, int x1, int y1, int col);
    void  api_closewin(int win);
    int   api_getkey(int mode);
    int   api_alloctimer(void);
    void  api_inittimer(int timer, int data);
    void  api_settimer(int timer, int time);
    void  api_freetimer(int timer);
    void  api_beep(int tone);
    int   api_fopen(char* fname);
    void  api_fclose(int fhandle);
    void  api_fseek(int fhandle, int offset, int mode);
    int   api_fsize(int fhandle, int mode);
    int   api_fread(char* buf, int maxsize, int fhandle);
    int   api_cmdline(char *buf, int maxsize);
    int   api_getlang(void);
}

/* はりぼて友の会共通システムコール */
extern "C" {
    void tomo_getmouse(int win, MOUSE_INFO *info);
    int  tomo_gettick(void);
    void tomo_rdmsr(int id_ecx, int *eax, int *edx);
    void tomo_setlang(int lang);
    void tomo_sysinfo(SYS_INFO *info);
    void tomo_systime(TIME_INFO *info);
    void tomo_wrmsr(int id_ecx, int eax, int edx);
    void tomo_cpuid(int id_eax, int id_ecx, int *eax, int *ebx, int *ecx, int *edx);
    void tomo_rdtsc(int *high, int *low);
}

/* BayOSシステムコール */
extern "C" {
    int  bayos_thread_id();
    int  bayos_thread_join(dword function);
    void bayos_thread_kill(int id);
    void bayos_thread_yield();
    void bayos_msg_send(int to, MSG_INFO *info);
    int  bayos_msg_receive(MSG_INFO *info);
    int  bayos_get_wstr_info(char *str, WSTR_INFO *info);
}

/* C言語用関数 */
extern "C" {
    void  HariMain(void);
    void* memcpy(void* s1, const void* s2, size_t size);
    void* memset(void *d, int c, size_t sz);
    int   printf(const char* format, ...);
}

/* C++用演算子 */
void* operator new(size_t size);
void* operator new[](size_t size);
void  operator delete(void* address);
void  operator delete[](void* address);

#endif
