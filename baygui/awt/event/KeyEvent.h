#if !defined(_BAYGUI_AWT_EVENT_KEYEVENT_H_INCLUDED_)
#define _BAYGUI_AWT_EVENT_KEYEVENT_H_INCLUDED_

using namespace baygui::lang;
using namespace baygui::awt;

namespace baygui {
    namespace awt {
        namespace event {
            /** このイベントは、コンポーネントにおいてキーストロークが発生したことを示します。*/
            class KeyEvent : public AWTEvent {
            public:
                enum {
                    /** 「キープレス」イベントです。*/
                    KEY_PRESSED  = 100,
                    /** 「キーリリース」イベントです。*/
                    KEY_RELEASED = 101
                };

            private:
                /** 文字です。*/
                int keyChar;
                /** キーコードです。*/
                int keyCode;
                /** 修飾子です。*/
                int modifiers;

            public:
                /** デフォルトコンストラクタです。*/
                KeyEvent();

                /** 指定されたソースオブジェクトと型を使用して、KeyEvent オブジェクトを構築します。*/
                KeyEvent(Object* source, int id, int modifiers, int keyCode, char keyChar);

                /** このイベントのキーに関連した文字を返します。*/
                char getKeyChar();

                /** このイベントのキーに関連した整数型のキーコードを返します。*/
                int getKeyCode();

                /** このイベントのキーに関連した整数型の修飾子を返します。*/
                int getModifiers();
            };
        }
    }
}

#endif
