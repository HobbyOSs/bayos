#include "../../../baygui.h"

namespace baygui {
    namespace awt {
        namespace event {
            /** デフォルトコンストラクタです。*/
            KeyEvent::KeyEvent() {
                addClassName(baygui_awt_event_KeyEvent);
                this->consumed = false;
                this->id = 0;
                this->source = NULL;
                this->keyChar = 0;
                this->keyCode = 0;
                this->modifiers = 0;
            }

            /** 指定されたソースオブジェクトと型を使用して、KeyEvent オブジェクトを構築します。*/
            KeyEvent::KeyEvent(Object* source, int id, int modifiers, int keyCode, char keyChar) {
                addClassName(baygui_awt_event_KeyEvent);
                this->consumed = false;
                this->id = id;
                this->source = source;
                this->keyChar = keyChar;
                this->keyCode = keyCode;
                this->modifiers = modifiers;
            }

            /** このイベントのキーに関連した文字を返します。*/
            char KeyEvent::getKeyChar() {
                return this->keyChar;
            }

            /** このイベントのキーに関連した整数型のキーコードを返します。*/
            int KeyEvent::getKeyCode() {
                return this->keyCode;
            }

            /** このイベントのキーに関連した整数型の修飾子を返します。*/
            int KeyEvent::getModifiers() {
                return this->modifiers;
            }
        }
    }
}
