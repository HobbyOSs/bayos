#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** 新しいスクロールリストを作成します。*/
        Listbox::Listbox() {
            addClassName(baygui_awt_Listbox);
            this->items = new ArrayList();
            this->selectedIndex = 0;
            this->background = Color::white;
        }

        /** デストラクタです。*/
        Listbox::~Listbox() {
            delete this->items;
        }

        /** 指定された項目をスクロールリストの終わりに追加します。*/
        void Listbox::add(const char* item) {
            this->items->add(new String(item));
        }

        /** 指定するインデックスに対応する項目を返します。*/
        char* Listbox::getItem(int index) {
            String* str = (String *) this->items->get(index);
            if (str != NULL) {
                return str->toCharArray();
            } else {
                return NULL;
            }
        }

        /** リストで選択されている項目のインデックスを返します。*/
        int Listbox::getSelectedIndex() {
            return selectedIndex;
        }

        /** リスト内の項目の数を返します。*/
        int Listbox::getItemCount() {
            return this->items->size();
        }

        /** このコンポーネントをペイントします。*/
        void Listbox::paint(Graphics* g)
        {
            int w = getWidth();
            int h = getHeight();
            int visibleRows = (h - 2) / 16;

            // 外枠
            if (hasFocus() == true && isEnabled() == true) {
                g->setColor(0,128,255);
                g->drawRect(0, 0, w, h);
            } else {
                g->setColor(getParent()->getBackground());
                g->drawRect(0, 0, w, h);
            }

            // 内枠
            g->setColor(getBackground());
            g->fillRect(1, 1, w - 2, h - 2);
            g->setColor(getForeground());
            g->drawRect(1, 1, w - 2, h - 2);

            // 文字
            int I = this->items->size();
            for (int i = 0; i < visibleRows; i++) {
                if ((0 + i) < I) {
                    if (this->selectedIndex == i && isEnabled() == true) {
                        g->setColor(0, 128, 255);
                        g->fillRect(3, (16 * i) + 3, w - 6, 16);
                        g->setColor(getBackground());
                        g->drawString(getItem(0 + i), 4, (16 * i) + 6);
                    } else {
                        g->setColor(getForeground());
                        g->drawString(getItem(0 + i), 4, (16 * i) + 6);
                    }
                }
            } 
        }

        /** このコンポーネントで発生するマウスイベントを処理します。*/
        void Listbox::processMouseEvent(MouseEvent* e) {
            Component::processMouseEvent(e);

            if (e->getID() == MouseEvent::MOUSE_PRESSED) {
                this->selectedIndex = (e->getY() - 3) / 16;
                repaint();
            }
        }
    }
}
