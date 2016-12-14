#ifndef _SYSTEM_SHEET_H_INCLUDED_
#define _SYSTEM_SHEET_H_INCLUDED_

/* システムカラー16色（16bpp版）*/

#define BLACK        0x0000
#define LIGHT_RED    0xf800
#define LIGHT_GREEN  0x07e0
#define LIGHT_YELLOW 0xffe0
#define LIGHT_BLUE   0x001f
#define LIGHT_PURPLE 0xf81f
#define LIGHT_AQUA   0x07ff
#define WHITE        0xffff
#define LIGHT_GRAY   0xc618
#define DARK_RED     0x8000
#define DARK_GREEN   0x0420
#define DARK_YELLOW  0x8420
#define DARK_BLUE    0x0010
#define DARK_PURPLE  0x8010
#define DARK_AQUA    0x0410
#define DARK_GRAY    0x8410

/* 下敷きの定数 */

#define MAX_SHEETS       256
#define WALLPAPER_WIDTH  640
#define WALLPAPER_HEIGHT 127
#define WALLPAPER_SCALE  2

/* フォントの定数 */

#define FONT_W 6
#define FONT_H 12

namespace system {
    /* 下敷き */
    class Sheet {
    public:
        word* buffer;
        int width, height, vx0, vy0, transparent, depth, flags;
        Task* task;
    };

    /* 下敷きマネージャ */
    class SheetCtl {
    public:
        static int xsize;
        static int ysize;
        static int top;
        static byte*   map;
        static word*   vram;
        static Sheet** sheets;
        static Sheet*  sheets0;
        static Sheet*  back;
        static byte*   zenkaku;
        static int*    offsets;
        static WSTR_INFO* wstrinfo;

    private:
        static void refreshmap(int vx0, int vy0, int vx1, int vy1, int h0);
        static void refreshsub(int vx0, int vy0, int vx1, int vy1, int h0, int h1);

    public:
        static void init();
        static Sheet* allocate();
        static void setbuf(Sheet* sht, word* buf, int xsize, int ysize, int transparent);
        static void updown(Sheet* sht, int depth);
        static void refresh(Sheet* sht, int bx0, int by0, int bx1, int by1);
        static void slide(Sheet* sht, int vx0, int vy0);
        static void dispose(Sheet* sht);

    public:
        static void drawPixel(Sheet* sht, int x, int y, word col);
        static void drawLine(Sheet* sht, int x0, int y0, int x1, int y1, word col);
        static void drawRect(Sheet* sht, int x, int y, int width, int height, word col);
        static void fillRect(Sheet* sht, int x0, int y0, int x1, int y1, word col);
        static void drawString(Sheet* sht, char* title, int x0, int y0, word col);
        static void drawFrame(Sheet* sht, char* title);
    };
}

#endif
