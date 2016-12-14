#if !defined(_BAYGUI_AWT_BUTTON_H_INCLUDED_)
#define _BAYGUI_AWT_BUTTON_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * このクラスはラベル付きボタンを作成します。
         * アプリケーションは、ボタンが押されたときにアクションが
         * 実行されるようにすることができます。
        */
        class Button : public Component {
        protected:
            /** このボタンが押されたかどうかを示します。*/
            bool pushed;
            /** このボタンのラベルです。*/
            char* label;
            
        public:
            /** ラベルなしのボタンを構築します。*/
            Button();

            /** 指定されたラベルが付いたボタンを構築します。*/
            Button(const char* label);

            /** デストラクタです。*/
            virtual ~Button();

            /** ボタンのラベルを返します。*/
            char* getLabel();

            /** このコンポーネントをペイントします。*/
            virtual void paint(Graphics* g);

            /** このコンポーネントで発生するマウスイベントを処理します。*/
            virtual void processMouseEvent(MouseEvent* e);

            /** ボタンのラベルを、指定された文字列に設定します。*/
            void setLabel(const char* label);
        };
    }
}

#endif
