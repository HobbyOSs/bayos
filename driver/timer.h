#ifndef _DRIVER_TIMER_H_INCLUDED_
#define _DRIVER_TIMER_H_INCLUDED_

#define PIT_CTRL 0x0043
#define PIT_CNT0 0x0040

namespace driver {
    /* �^�C�}�[�h���C�o�[ */
    class Timer {
    public:
        static dword count;

    public:
        static void init(void);
        static void sleep(dword ms);
    };
}

#endif
