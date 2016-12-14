#if !defined(_BAYGUI_AWT_COLOR_H_INCLUDED_)
#define _BAYGUI_AWT_COLOR_H_INCLUDED_

#define BPP24to16(color) (unsigned short)(((color >> 8) & 0xf800) | ((color >> 5) & 0x07e0) | ((color >> 3) & 0x1f))
#define BPP24to8(color)  (unsigned char)((16 + ((color >> 24) / 43) + ((color >> 16) / 43) * 6 + ((color >> 8) / 43) * 36) & 0xff)

namespace baygui {
    namespace awt {
        /**
         * Color �N���X�́A�f�t�H���g�̃V�X�e���J���[���J�v�Z��������̂Ɏg�p����܂��B
        */
        class Color {
        public:
            /** ���F */
            static const unsigned int black     = 0xff000000;
            /** �Z�����F */
            static const unsigned int maroon    = 0xff800000;
            /** �Z���ΐF */
            static const unsigned int green     = 0xff008000;
            /** �Z�����F */
            static const unsigned int olive     = 0xff808000;
            /** �Z���F */
            static const unsigned int navy      = 0xff000080;
            /** ���F */
            static const unsigned int purple    = 0xff800080;
            /** �Â��F */
            static const unsigned int teal      = 0xff008080;
            /** ���邢�D�F */
            static const unsigned int lightGray = 0xffC0C0C0;
            /** �D�F */
            static const unsigned int gray      = 0xff808080;
            /** �ԐF */
            static const unsigned int red       = 0xffff0000;
            /** ���邢�ΐF */
            static const unsigned int lime      = 0xff00ff00;
            /** ���F */
            static const unsigned int yellow    = 0xffffff00;
            /** �F */
            static const unsigned int blue      = 0xff0000ff;
            /** ���邢�ԐF */
            static const unsigned int magenta   = 0xffff00ff;
            /** ���F */
            static const unsigned int cyan      = 0xff00ffff;
            /** ���F */
            static const unsigned int white     = 0xffffffff;
        };
    }
}

#endif
