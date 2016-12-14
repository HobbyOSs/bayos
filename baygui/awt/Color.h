#if !defined(_BAYGUI_AWT_COLOR_H_INCLUDED_)
#define _BAYGUI_AWT_COLOR_H_INCLUDED_

#define BPP24to16(color) (unsigned short)(((color >> 8) & 0xf800) | ((color >> 5) & 0x07e0) | ((color >> 3) & 0x1f))
#define BPP24to8(color)  (unsigned char)((16 + ((color >> 24) / 43) + ((color >> 16) / 43) * 6 + ((color >> 8) / 43) * 36) & 0xff)

namespace baygui {
    namespace awt {
        /**
         * Color クラスは、デフォルトのシステムカラーをカプセル化するのに使用されます。
        */
        class Color {
        public:
            /** 黒色 */
            static const unsigned int black     = 0xff000000;
            /** 濃い茶色 */
            static const unsigned int maroon    = 0xff800000;
            /** 濃い緑色 */
            static const unsigned int green     = 0xff008000;
            /** 濃い黄色 */
            static const unsigned int olive     = 0xff808000;
            /** 濃い青色 */
            static const unsigned int navy      = 0xff000080;
            /** 紫色 */
            static const unsigned int purple    = 0xff800080;
            /** 暗い青色 */
            static const unsigned int teal      = 0xff008080;
            /** 明るい灰色 */
            static const unsigned int lightGray = 0xffC0C0C0;
            /** 灰色 */
            static const unsigned int gray      = 0xff808080;
            /** 赤色 */
            static const unsigned int red       = 0xffff0000;
            /** 明るい緑色 */
            static const unsigned int lime      = 0xff00ff00;
            /** 黄色 */
            static const unsigned int yellow    = 0xffffff00;
            /** 青色 */
            static const unsigned int blue      = 0xff0000ff;
            /** 明るい赤色 */
            static const unsigned int magenta   = 0xffff00ff;
            /** 水色 */
            static const unsigned int cyan      = 0xff00ffff;
            /** 白色 */
            static const unsigned int white     = 0xffffffff;
        };
    }
}

#endif
