#if !defined(_BAYGUI_AWT_CHECKBOX_H_INCLUDED_)
#define _BAYGUI_AWT_CHECKBOX_H_INCLUDED_

namespace baygui {
    namespace awt {
        class CheckboxGroup;

        /**
         * チェックボックスは、「オン」 (true) または「オフ」 (false) の
         * どちらかの状態にすることができるグラフィカルコンポーネントです。
        */
        class Checkbox : public Component {
        public:
            /** チェックボックスグループです。*/
            CheckboxGroup* group;

        protected:
            /** このチェックボックスがチェックされたかどうかを示します。*/
            bool state;
            /** このチェックボックスのラベルです。*/
            char* label;
            
        public:
            /** ラベルなしのチェックボックスを構築します。*/
            Checkbox();

            /** 指定されたラベルが付いたチェックボックスを構築します。*/
            Checkbox(const char* label);

            /** デストラクタです。*/
            virtual ~Checkbox();

            /** チェックボックスのラベルを返します。*/
            char* getLabel();

            /** このチェックボックスが「オン」の状態であるか、「オフ」の状態であるかを判定します。*/
            bool getState();

            /** このコンポーネントをペイントします。*/
            virtual void paint(Graphics* g);

            /** このコンポーネントで発生するマウスイベントを処理します。*/
            virtual void processMouseEvent(MouseEvent* e);

            /** チェックボックスのラベルを、指定された文字列に設定します。*/
            void setLabel(const char* label);

            /** このチェックボックスの状態を、指定された状態に設定します。*/
            void setState(bool state);
        };
    }
}

#endif
