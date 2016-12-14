#if !defined(_BAYGUI_AWT_TEXTFIELD_H_INCLUDED_)
#define _BAYGUI_AWT_TEXTFIELD_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * TextField オブジェクトは、1 行のテキストの編集を行えるようにするテキストコンポーネントです。
        */
        class TextField : public TextComponent {
        public:
            /** 新しいテキストフィールドを構築します。*/
            TextField();

            /** 指定されたテキストで初期化された新しいテキストフィールドを構築します。*/
            TextField(const char* text);

            /** このコンポーネントをペイントします。*/
            virtual void paint(Graphics* g);
        };
    }
}

#endif
