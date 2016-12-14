#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** デフォルトコンストラクタです。*/
        AWTEvent::AWTEvent() {
            this->consumed = false;
            this->id = 0;
            this->source = NULL;
        }

        /** イベントを消費します。*/
        void AWTEvent::consume() {
            this->consumed = true;
        }

        /* イベントの型を返します。*/
        int AWTEvent::getID() {
            return this->id;
        }

        /** Event が最初に発生したオブジェクトです。*/
        Object* AWTEvent::getSource() {
            return this->source;
        }

        /** イベントが消費されたかどうかを返します。*/
        bool AWTEvent::isConsumed() {
            return this->consumed;
        }
    }
}
