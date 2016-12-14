#include "../bayos.h"

int    Mouse::x = 0;
int    Mouse::y = 0;
int    Mouse::button = 0;
byte   Mouse::state  = 0;
byte   Mouse::phase  = 0;
char   Mouse::buff[] = { 0, 0, 0 };
Sheet* Mouse::sheet  = NULL;
char*  Mouse::cursor[] =
{
    "1..........",
    "11.........",
    "121........",
    "1221.......",
    "12221......",
    "122221.....",
    "1222221....",
    "12222221...",
    "122222221..",
    "1222222221.",
    "12222211111",
    "1221221....",
    "121.1221...",
    "11..1221...",
    "1....1221..",
    ".....1221..",
    "......11..."
};

/* マウスの初期化 */
void Mouse::init() {
    Keyboard::wait();
    io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
    Keyboard::wait();
    io_out8(PORT_KEYDAT, MOUSECMD_ENABLE);

    /* 変数の初期化 */
    Mouse::x = SheetCtl::xsize / 2;
    Mouse::y = SheetCtl::ysize / 2;
    Mouse::button = 0;
    Mouse::phase  = 0;

    /* マウス用の下敷きの初期化 */
    Mouse::sheet = SheetCtl::allocate();
    SheetCtl::setbuf(Mouse::sheet, (word *) malloc (MOUSE_W * MOUSE_H * sizeof(short)), MOUSE_W, MOUSE_H, 1/* 透過 */);
    for (int i = 0; i < MOUSE_W; i++) {
        for (int j = 0; j < MOUSE_H; j++) {
            if (Mouse::cursor[j][i] == '1') {
                Mouse::sheet->buffer[j * MOUSE_W + i] = WHITE;
            } else if (Mouse::cursor[j][i] == '2') {
                Mouse::sheet->buffer[j * MOUSE_W + i] = BLACK;
            } else {
                Mouse::sheet->buffer[j * MOUSE_W + i] = 1;/* 透過 */
            }
        }
    }
    Mouse::sheet->vx0 = Mouse::x;
    Mouse::sheet->vy0 = Mouse::y;
    SheetCtl::updown(Mouse::sheet, 2);

    return;
}

/* 生データのデコード */
int Mouse::decode(byte data) {
    /* マウスの0xfaを待っている段階 */
    if (Mouse::phase == 0) {
        if (data == 0xfa) {
            Mouse::phase = 1;
        }
        return 0;
    }

    /* マウスの1バイト目を待っている段階 */
    if (Mouse::phase == 1) {
        if ((data & 0xc8) == 0x08) {
            /* 正しい1バイト目だった */
            Mouse::buff[0] = data;
            Mouse::phase   = 2;
        }
        return 0;
    }

    /* マウスの2バイト目を待っている段階 */
    if (Mouse::phase == 2) {
        Mouse::buff[1] = data;
        Mouse::phase   = 3;
        return 0;
    }

    /* マウスの3バイト目を待っている段階 */
    if (Mouse::phase == 3) {
        Mouse::buff[2] = data;
        Mouse::phase   = 1;
        Mouse::button  = Mouse::buff[0] & 0x07;
        int dx = Mouse::buff[1];
        int dy = Mouse::buff[2];

        if ((Mouse::buff[0] & 0x10) != 0) {
            dx |= 0xffffff00;
        }

        if ((Mouse::buff[0] & 0x20) != 0) {
            dy |= 0xffffff00;
        }

        dy = - dy; /* マウスではy方向の符号が画面と反対 */

        if (dx == 0 && dy == 0) {
            if (Mouse::button == 0) {
                Mouse::state = MSG_MOUSE_RELEASED;  /* マウスのボタンを離した */
            } else {
                Mouse::state = MSG_MOUSE_PRESSED;   /* マウスのボタンを押した */
            }
        } else {
            if (Mouse::button == 0) {
                Mouse::state = MSG_MOUSE_MOVED;     /* マウスの移動 */
            } else {
                Mouse::state = MSG_MOUSE_DRAGGED;   /* マウスのドラッグ */
            }
        }

        Mouse::x += dx;
        Mouse::y += dy;

        Mouse::x = x & ~1; /* 2ドットずつしか動かせない */
        Mouse::y = y & ~1; /* 2ドットずつしか動かせない */

        /* 画面の端に行ってしまった場合の処理 */
        if (Mouse::x < 0) Mouse::x = 0;
        if (Mouse::y < 0) Mouse::y = 0;
        if (Mouse::x >= SheetCtl::xsize) Mouse::x = SheetCtl::xsize;
        if (Mouse::y >= SheetCtl::ysize) Mouse::y = SheetCtl::ysize;

        return 1;
    }

    return -1; /* ここに来ることはないはず */
}

/* 描画 */
void Mouse::draw() {
    SheetCtl::slide(Mouse::sheet, Mouse::x, Mouse::y);
}
