#include "../../../baygui.h"

namespace baygui {
    namespace awt {
        namespace event {
            /** デフォルトコンストラクタです。*/
            MouseEvent::MouseEvent() {
                addClassName(baygui_awt_event_MouseEvent);
                this->consumed = false;
                this->id = 0;
                this->source = NULL;
                this->modifiers = 0;
                this->x = 0;
                this->y = 0;
            }

            /** 指定されたソースオブジェクトと型を使用して、MouseEvent オブジェクトを構築します。*/
            MouseEvent::MouseEvent(Object* source, int id, int modifiers, int x, int y) {
                addClassName(baygui_awt_event_MouseEvent);
                this->consumed = false;
                this->id = id;
                this->source = source;
                this->modifiers = modifiers;
                this->x = x;
                this->y = y;
            }

            /** このイベントに関連したボタンの種類を返します。*/
            int MouseEvent::getModifiers() {
                return this->modifiers;
            }

            /** イベントが発生した位置の X 座標を発生元のコンポーネントに対する相対位置で返します。*/
            int MouseEvent::getX() {
                return this->x;
            }

            /** イベントが発生した位置の Y 座標を発生元のコンポーネントに対する相対位置で返します。*/
            int MouseEvent::getY() {
                return this->y;
            }
        }
    }
}
