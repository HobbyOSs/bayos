#if !defined(_BAYGUI_AWT_RECTANGLE_H_INCLUDED_)
#define _BAYGUI_AWT_RECTANGLE_H_INCLUDED_

using namespace baygui::lang;

namespace baygui {
    namespace awt {
        /**
         * Rectangle は、Rectangle オブジェクトの座標空間での左上の点 (x、 y)、
         * およびその幅と高さによって囲まれる座標空間内の領域を指定します。
        */
        class Rectangle : public Object {
        public:
            /** Rectangle の高さです。*/
            int height;
            /** Rectangle の幅です。*/
            int width;
            /** Rectangle の x 座標です。*/
            int x;
            /** Rectangle の y 座標です。*/
            int y;

        public:
            /** 左上隅が座標空間の (0, 0) にあり、幅と高さが両方とも 0 の新しい Rectangle を構築します。*/
            Rectangle();
        };
    }
}

#endif
