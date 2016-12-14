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

/* �}�E�X�̏����� */
void Mouse::init() {
    Keyboard::wait();
    io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);
    Keyboard::wait();
    io_out8(PORT_KEYDAT, MOUSECMD_ENABLE);

    /* �ϐ��̏����� */
    Mouse::x = SheetCtl::xsize / 2;
    Mouse::y = SheetCtl::ysize / 2;
    Mouse::button = 0;
    Mouse::phase  = 0;

    /* �}�E�X�p�̉��~���̏����� */
    Mouse::sheet = SheetCtl::allocate();
    SheetCtl::setbuf(Mouse::sheet, (word *) malloc (MOUSE_W * MOUSE_H * sizeof(short)), MOUSE_W, MOUSE_H, 1/* ���� */);
    for (int i = 0; i < MOUSE_W; i++) {
        for (int j = 0; j < MOUSE_H; j++) {
            if (Mouse::cursor[j][i] == '1') {
                Mouse::sheet->buffer[j * MOUSE_W + i] = WHITE;
            } else if (Mouse::cursor[j][i] == '2') {
                Mouse::sheet->buffer[j * MOUSE_W + i] = BLACK;
            } else {
                Mouse::sheet->buffer[j * MOUSE_W + i] = 1;/* ���� */
            }
        }
    }
    Mouse::sheet->vx0 = Mouse::x;
    Mouse::sheet->vy0 = Mouse::y;
    SheetCtl::updown(Mouse::sheet, 2);

    return;
}

/* ���f�[�^�̃f�R�[�h */
int Mouse::decode(byte data) {
    /* �}�E�X��0xfa��҂��Ă���i�K */
    if (Mouse::phase == 0) {
        if (data == 0xfa) {
            Mouse::phase = 1;
        }
        return 0;
    }

    /* �}�E�X��1�o�C�g�ڂ�҂��Ă���i�K */
    if (Mouse::phase == 1) {
        if ((data & 0xc8) == 0x08) {
            /* ������1�o�C�g�ڂ����� */
            Mouse::buff[0] = data;
            Mouse::phase   = 2;
        }
        return 0;
    }

    /* �}�E�X��2�o�C�g�ڂ�҂��Ă���i�K */
    if (Mouse::phase == 2) {
        Mouse::buff[1] = data;
        Mouse::phase   = 3;
        return 0;
    }

    /* �}�E�X��3�o�C�g�ڂ�҂��Ă���i�K */
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

        dy = - dy; /* �}�E�X�ł�y�����̕�������ʂƔ��� */

        if (dx == 0 && dy == 0) {
            if (Mouse::button == 0) {
                Mouse::state = MSG_MOUSE_RELEASED;  /* �}�E�X�̃{�^���𗣂��� */
            } else {
                Mouse::state = MSG_MOUSE_PRESSED;   /* �}�E�X�̃{�^���������� */
            }
        } else {
            if (Mouse::button == 0) {
                Mouse::state = MSG_MOUSE_MOVED;     /* �}�E�X�̈ړ� */
            } else {
                Mouse::state = MSG_MOUSE_DRAGGED;   /* �}�E�X�̃h���b�O */
            }
        }

        Mouse::x += dx;
        Mouse::y += dy;

        Mouse::x = x & ~1; /* 2�h�b�g�������������Ȃ� */
        Mouse::y = y & ~1; /* 2�h�b�g�������������Ȃ� */

        /* ��ʂ̒[�ɍs���Ă��܂����ꍇ�̏��� */
        if (Mouse::x < 0) Mouse::x = 0;
        if (Mouse::y < 0) Mouse::y = 0;
        if (Mouse::x >= SheetCtl::xsize) Mouse::x = SheetCtl::xsize;
        if (Mouse::y >= SheetCtl::ysize) Mouse::y = SheetCtl::ysize;

        return 1;
    }

    return -1; /* �����ɗ��邱�Ƃ͂Ȃ��͂� */
}

/* �`�� */
void Mouse::draw() {
    SheetCtl::slide(Mouse::sheet, Mouse::x, Mouse::y);
}
