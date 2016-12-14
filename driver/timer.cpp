#include "../bayos.h"

dword Timer::count = 0;

/* �^�C�}�[�̏����� */
void Timer::init() {
    io_out8(PIT_CTRL, 0x34);
    io_out8(PIT_CNT0, 0x9c); /* 10ms */
    io_out8(PIT_CNT0, 0x2e);
}

/* �w�肵�����Ԃ����҂� */
void Timer::sleep(dword ms) {
    dword wakeup = Timer::count + (ms / 10);
    while (Timer::count < wakeup) {
        io_hlt();
    }
}
