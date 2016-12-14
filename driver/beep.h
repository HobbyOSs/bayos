#ifndef _DRIVER_BEEP_H_INCLUDED_
#define _DRIVER_BEEP_H_INCLUDED_

namespace driver {
    /* ビープドライバー */
    class Beep {
    public:
        static void tone(int freq);
    };
}

#endif
