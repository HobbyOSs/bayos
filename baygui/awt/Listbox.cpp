#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** �V�����X�N���[�����X�g���쐬���܂��B*/
        Listbox::Listbox() {
            addClassName(baygui_awt_Listbox);
            this->items = new ArrayList();
            this->selectedIndex = 0;
            this->background = Color::white;
        }

        /** �f�X�g���N�^�ł��B*/
        Listbox::~Listbox() {
            delete this->items;
        }

        /** �w�肳�ꂽ���ڂ��X�N���[�����X�g�̏I���ɒǉ����܂��B*/
        void Listbox::add(const char* item) {
            this->items->add(new String(item));
        }

        /** �w�肷��C���f�b�N�X�ɑΉ����鍀�ڂ�Ԃ��܂��B*/
        char* Listbox::getItem(int index) {
            String* str = (String *) this->items->get(index);
            if (str != NULL) {
                return str->toCharArray();
            } else {
                return NULL;
            }
        }

        /** ���X�g�őI������Ă��鍀�ڂ̃C���f�b�N�X��Ԃ��܂��B*/
        int Listbox::getSelectedIndex() {
            return selectedIndex;
        }

        /** ���X�g���̍��ڂ̐���Ԃ��܂��B*/
        int Listbox::getItemCount() {
            return this->items->size();
        }

        /** ���̃R���|�[�l���g���y�C���g���܂��B*/
        void Listbox::paint(Graphics* g)
        {
            int w = getWidth();
            int h = getHeight();
            int visibleRows = (h - 2) / 16;

            // �O�g
            if (hasFocus() == true && isEnabled() == true) {
                g->setColor(0,128,255);
                g->drawRect(0, 0, w, h);
            } else {
                g->setColor(getParent()->getBackground());
                g->drawRect(0, 0, w, h);
            }

            // ���g
            g->setColor(getBackground());
            g->fillRect(1, 1, w - 2, h - 2);
            g->setColor(getForeground());
            g->drawRect(1, 1, w - 2, h - 2);

            // ����
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

        /** ���̃R���|�[�l���g�Ŕ�������}�E�X�C�x���g���������܂��B*/
        void Listbox::processMouseEvent(MouseEvent* e) {
            Component::processMouseEvent(e);

            if (e->getID() == MouseEvent::MOUSE_PRESSED) {
                this->selectedIndex = (e->getY() - 3) / 16;
                repaint();
            }
        }
    }
}
