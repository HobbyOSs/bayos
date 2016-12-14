#include "bayos.h"

/* C言語の関数宣言 */
extern "C" {
    /* C言語の入り口 */
    void HariMain(void);
};

/* メモリマネージャ */
Memory g_km;

/* C言語の入り口 */
void HariMain(void) {
    dword size = get_physical_size(0x00400000, 0xbfffffff); /* 物理メモリサイズ */
    g_km.init(0x00400000, size); /* メモリマネージャ初期化 */

    Descriptor::init();       /* GDT/IDTの初期化 */
    PIC::init();              /* PICの初期化 */
    Timer::init();            /* タイマーの初期化 */
    FAT12::init();            /* FAT12ファイルマネージャの初期化 */
    ISO9660::init();          /* ISO9660ファイルマネージャの初期化 */
    SheetCtl::init();         /* 下敷きの初期化 */
    Keyboard::init();         /* キーボードの初期化 */
    Mouse::init();            /* マウスの初期化 */
    Scheduler::init();        /* スケジューラの初期化 */
    io_out8(PIC0_IMR, 0xf8);  /* PITとPIC1とキーボードを許可(11111000) */
    io_out8(PIC1_IMR, 0xef);  /* マウスを許可(11101111) */
    io_sti();                 /* IDT/PICの初期化が終わったのでCPUの割り込み禁止を解除 */

    for (;;) {
        io_stihlt();          /* hlt しないと CPU 100% になる */
    }
}
