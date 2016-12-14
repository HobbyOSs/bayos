#ifndef _DRIVER_KEYBOARD_H_INCLUDED_
#define _DRIVER_KEYBOARD_H_INCLUDED_

#define PORT_KEYDAT          0x0060
#define PORT_KEYCMD          0x0064
#define PORT_KEYSTA          0x0064
#define KEYSTA_SEND_NOTREADY 0x0002
#define KEYCMD_WRITE_MODE    0x0060
#define KBC_MODE             0x0047

namespace driver {
    /* PS/2キーボードドライバー */
    class Keyboard {
    private:
        static char ascii_table[];
        static char ascii_shift_table[];

    public:
        static int shift_ctrl_alt, state;

    public:
        static void init(void);
        static void wait(void);
        static char decode(int code);
    };
}

#endif
