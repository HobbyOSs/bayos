#include "../bayos.h"

int Keyboard::shift_ctrl_alt = 0;
int Keyboard::state = 0;

/* �ʏ�̃L�[ */
char Keyboard::ascii_table[] =
{ 
    // 58�s
    0,
    0 /* ESC (1) */,
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '^',
    '\b',
    '\t',
    'q',
    'w',
    'e',
    'r',
    't',
    'y',
    'u',
    'i',
    'o',
    'p',
    '@',
    '[',
    '\n',
    0 /* L-CTRL (29) */,
    'a',
    's',
    'd',
    'f',
    'g',
    'h',
    'j',
    'k',
    'l',
    ';',
    ':',
    0 /* ���p (41) */,
    0 /* L-SHIFT (42) */,
    ']',
    'z',
    'x',
    'c',
    'v',
    'b',
    'n',
    'm',
    ',',
    '.',
    '/',
    0 /* R-SHIFT (54) */,
    0 /* ?  (55) */,
    0 /* L-ALT (56) */,
    ' '
};

/* �V�t�g���������Ƃ��̃L�[ */
char Keyboard::ascii_shift_table[] =
{
    // 58�s
    0,
    0,
    '!',
    '"',
    '#',
    '$',
    '%',
    '&',
    '\'',
    '(',
    ')',
    0,
    '=',
    '~',
    0,
    0,
    'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    'O',
    'P',
    '`',
    '{',
    0,
    0,
    'A',
    'S',
    'D',
    'F',
    'G',
    'H',
    'J',
    'K',
    'L',
    '+',
    '*',
    0,
    0,
    '}',
    'Z',
    'X',
    'C',
    'V',
    'B',
    'N',
    'M',
    '<',
    '>',
    '?',
    0,
    0,
    0,
    0
};

/* �L�[�{�[�h�̏����� */
void Keyboard::init() {
    wait();
    io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);
    wait();
    io_out8(PORT_KEYDAT, KBC_MODE);
    return;
}

/* �L�[�{�[�h�R���g���[�����f�[�^���M�\�ɂȂ�̂�҂� */
void Keyboard::wait(void) {
    for (;;) {
        if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0) {
            break;
        }
    }
    return;
}

/* ���f�[�^���f�R�[�h���� */
char Keyboard::decode(int code) {
    /* �L�[�R�[�h�𕶎��ɕϊ����� */
    if (code == R_SHIFT_PRESSED || code == L_SHIFT_PRESSED) {
        Keyboard::shift_ctrl_alt |= (1 << 0);
    } else if (code == L_CTRL_PRESSED) {
        Keyboard::shift_ctrl_alt |= (1 << 1);
    } else if (code == L_ALT_PRESSED) {
        Keyboard::shift_ctrl_alt |= (1 << 2);
    } else if (code == R_SHIFT_RELEASED || code == L_SHIFT_RELEASED) {
        Keyboard::shift_ctrl_alt &= ~(1 << 0);
    } else if (code == L_CTRL_RELEASED) {
        Keyboard::shift_ctrl_alt &= ~(1 << 1);
    } else if (code == L_ALT_RELEASED) {
        Keyboard::shift_ctrl_alt &= ~(1 << 2);
    } else if (0 <= code && code < 58) {
        Keyboard::state = MSG_KEY_PRESSED;
        if ((Keyboard::shift_ctrl_alt & (1 << 0)) != 0) {
            return Keyboard::ascii_shift_table[code];
        } else {
            return Keyboard::ascii_table[code];
        }
    } else if (128 <= code && code < 128 + 58) {
        Keyboard::state = MSG_KEY_RELEASED;
        if ((Keyboard::shift_ctrl_alt & (1 << 0)) != 0) {
            return Keyboard::ascii_shift_table[code - 128];
        } else {
            return Keyboard::ascii_table[code - 128];
        }
    }
    return 0;
}
