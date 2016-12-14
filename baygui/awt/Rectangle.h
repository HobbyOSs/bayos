#if !defined(_BAYGUI_AWT_RECTANGLE_H_INCLUDED_)
#define _BAYGUI_AWT_RECTANGLE_H_INCLUDED_

using namespace baygui::lang;

namespace baygui {
    namespace awt {
        /**
         * Rectangle �́ARectangle �I�u�W�F�N�g�̍��W��Ԃł̍���̓_ (x�A y)�A
         * ����т��̕��ƍ����ɂ���Ĉ͂܂����W��ԓ��̗̈���w�肵�܂��B
        */
        class Rectangle : public Object {
        public:
            /** Rectangle �̍����ł��B*/
            int height;
            /** Rectangle �̕��ł��B*/
            int width;
            /** Rectangle �� x ���W�ł��B*/
            int x;
            /** Rectangle �� y ���W�ł��B*/
            int y;

        public:
            /** ����������W��Ԃ� (0, 0) �ɂ���A���ƍ����������Ƃ� 0 �̐V���� Rectangle ���\�z���܂��B*/
            Rectangle();
        };
    }
}

#endif
