#include "../../baygui.h"

#define OFF_X 3
#define OFF_Y 3

namespace baygui {
    namespace awt {
        /** 新しいテキストフィールドを構築します。*/
        TextField::TextField() {
            addClassName(baygui_awt_TextField);
            this->background = Color::white;
            this->text = NULL;
        }

        /** 指定されたテキストで初期化された新しいテキストフィールドを構築します。*/
        TextField::TextField(const char* text) {
            addClassName(baygui_awt_TextField);
            this->background = Color::white;
            setText(text);
        }

        /** このコンポーネントをペイントします。*/
        void TextField::paint(Graphics* g) {
            int w = getWidth();
            int h = getHeight();

            /* 外枠を描画 */
            if (hasFocus() == true && isEnabled() == true) {
                g->setColor(0, 128, 255);
                g->drawRect(0, 0, w, h);
            } else {
                g->setColor(getParent()->getBackground());
                g->drawRect(0, 0, w, h);
            }

            /* 内枠を描画 */
            g->setColor(getBackground());
            g->fillRect(1, 1, w - 2, h - 2);
            g->setColor(getForeground());
            g->drawRect(1, 1, w - 2, h - 2);

            /* 文字列を描画 */
            int fh = 12;
            if (isEnabled() == true) {
                g->setColor(getForeground());
            } else {
                g->setColor(Color::gray);
            }
            g->drawString(this->text, OFF_X, (h - fh) / 2);
        }
    }
}
