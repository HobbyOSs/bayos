#ifndef _SYSTEM_CONSOLE_H_INCLUDED_
#define _SYSTEM_CONSOLE_H_INCLUDED_

/* ウィンドウのフチの大きさ */

#define INSETS_LEFT   6
#define INSETS_TOP    22
#define INSETS_BOTTOM 6
#define INSETS_RIGHT  6

namespace system {
    /* コンソール */
    class Console {
    public:
        int    cx;
        int    cy;
        int    cw;
        int    ch;
        word*  vram;
        char*  cmd_buf;
        Sheet* sheet;

    public:
        void init();
        void locate(int x, int y);
        void parseCommand();
        void restoreChar();
        void drawPrompt();
        void drawCarret();
        void put_char(byte c);
        void put_key(byte c);
        void put_string(const char* str);

    public:
        static void putChar(byte c);
        static void putString(const char* str);
        static void printf(const char* format, ...);
    };
}

#endif
