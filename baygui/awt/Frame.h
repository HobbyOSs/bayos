#if !defined(_BAYGUI_AWT_FRAME_H_INCLUDED_)
#define _BAYGUI_AWT_FRAME_H_INCLUDED_

#define INSETS_TOP    22
#define INSETS_BOTTOM 6
#define INSETS_LEFT   6
#define INSETS_RIGHT  6

namespace baygui {
    namespace awt {
        /** Frame は、タイトルとボーダ付きのトップレベルウィンドウです。*/
        class Frame : public Container {
        public:
            /** トップレベルウィンドウのハンドルです。*/
            unsigned int handle;
            /** 描画用のバッファーです。*/
            unsigned char* buffer;
            /** 現在フォーカスがあるコンポーネントをあらわします。*/
            Component* active;

        protected:
            /** このフレームのタイトルです。*/
            char* title;

        public:
            /** 初期状態で可視ではない Frame の新しいインスタンスを生成します。Frame のタイトルは空です。*/
            Frame();

            /** デストラクタです。*/
            virtual ~Frame();

            /** フレームのタイトルを返します。*/
            char* getTitle();

            /** このコンポーネントが入力フォーカスを取得することを要求します。*/
            virtual void requestFocus();

            /** アプリケーションの実行を開始します。*/
            void run();

            /** このフレームのサイズ変更します。*/
            virtual void setBounds(int x, int y, int width, int height);

            /** このフレームのタイトルを、指定された文字列に設定します。*/
            void setTitle(const char* title);

            /** 次のコンポーネントにフォーカスを移動します。*/
            virtual void transferFocus();
        };
    }
}

#endif
