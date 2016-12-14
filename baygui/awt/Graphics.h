#if !defined(_BAYGUI_AWT_GRAPHICS_H_INCLUDED_)
#define _BAYGUI_AWT_GRAPHICS_H_INCLUDED_

namespace baygui {
    namespace awt {
        class Frame;

        /** Graphics クラスは、すべてのグラフィックコンテキストの抽象基底クラスです。*/
        class Graphics : public Object {
        public:
            /** トップレベルウィンドウです。*/
            Frame* frame;
            /** 描画用のバッファーです。*/
            unsigned char* buffer;

        protected:
            /** トップレベルウィンドウの左端からの位置です。*/
            int tx;
            /** トップレベルウィンドウの左端からの位置です。*/
            int ty;
            /** 描画する色です。*/
            unsigned int color;

        public:
            /** 新しい Graphics オブジェクトを作成します。*/
            Graphics();

            /**
             * このグラフィックスコンテキストの座標体系の座標 (x1, y1) と
             * 座標 (x2, y2) との間に現在の色を使って線を描きます。
            */
            void drawLine(int x1, int y1, int x2, int y2);

            /** 指定された点を描きます。*/
            void drawPixel(int x, int y);

            /** 指定された矩形の輪郭を描きます。*/
            void drawRect(int x, int y, int width, int height);

            /**
             * このグラフィックスコンテキストの現在のフォントと色を使い、
             * 指定された文字列によって指定されたテキストを描きます。
            */
            void drawString(const char* str, int x, int y);

            /** 指定された矩形を塗りつぶします。*/
            void fillRect(int x, int y, int w, int h);

            /** このグラフィックスコンテキストの現在の色を、指定された色に設定します。*/
            void setColor(unsigned int color);

            /** このグラフィックスコンテキストの現在の色を、指定された色に設定します。*/
            void setColor(unsigned char r, unsigned char g, unsigned char b);

            /** グラフィックスコンテキストの原点を現在の座標系の (x, y) に変換します。*/
            void translate(int x, int y);
        };
    }
}

#endif
