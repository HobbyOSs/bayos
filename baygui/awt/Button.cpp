#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** ���x���Ȃ��̃{�^�����\�z���܂��B*/
        Button::Button() {
            addClassName(baygui_awt_Button);
            this->pushed = false;
            this->label  = NULL;
        }

        /** �w�肳�ꂽ���x�����t�����{�^�����\�z���܂��B*/
        Button::Button(const char* label) {
            addClassName(baygui_awt_Button);
            this->pushed = false;
            setLabel(label);
        }

        /** �f�X�g���N�^�ł��B*/
        Button::~Button() {
            delete this->label;
        }

        /** �{�^���̃��x����Ԃ��܂��B*/
        char* Button::getLabel() {
            return this->label;
        }

        /** ���̃R���|�[�l���g���y�C���g���܂��B*/
        void Button::paint(Graphics* g) {
            int w = getWidth();
            int h = getHeight();
            
            /* ��x�w�i�F�ŃN���A */
            g->setColor(getBackground());
            g->fillRect(0, 0, w, h);
            
            /* �g��`�� */
            g->setColor(Color::black);
            g->drawLine(2, 0, w - 3, 0);
            g->drawLine(2, h - 1, w - 3, h - 1);
            g->drawLine(0, 2, 0, h - 3);
            g->drawLine(w - 1, 2, w - 1, h - 3);
            g->drawLine(1, 1, 1, 1);
            g->drawLine(1, h - 2 , 1, h - 2);
            g->drawLine(w - 2 , 1, w - 2, 1);
            g->drawLine(w - 2 , h - 2, w - 2, h - 2);
            
            if (this->pushed) {
                g->setColor(Color::white);
                g->drawLine(2, h - 2, w - 3, h - 2);
                g->drawLine(w - 2, 2, w - 2, h - 3);
                g->drawLine(w - 3 , h - 3, w - 3, h - 3);
                g->setColor(Color::gray);
                g->drawLine(1, 2, 1, h - 3);
                g->drawLine(2, 1, w - 3, 1);
            } else {
                g->setColor(Color::gray);
                g->drawLine(2, h - 2, w - 3, h - 2);
                g->drawLine(w - 2, 2, w - 2, h - 3);
                g->drawLine(w - 3 , h - 3, w - 3, h - 3);
                g->setColor(Color::white);
                g->drawLine(1, 2, 1, h - 3);
                g->drawLine(2, 1, w - 3, 1);
            }
            
            /* �������`�� */
            int fw = FontMetrice::stringWidth(this->label);
            int fh = FontMetrice::getHeight();
            int x = (w - fw) / 2;
            int y = (h - fh) / 2;
            if (this->pushed) {
                x++;
                y++;
            }
            if (isEnabled() == true) {
                g->setColor(getForeground());
            } else {
                g->setColor(Color::gray);
            }
            g->drawString(this->label, x, y);
        }

        /** ���̃R���|�[�l���g�Ŕ�������}�E�X�C�x���g���������܂��B*/
        void Button::processMouseEvent(MouseEvent* e) {
            Component::processMouseEvent(e);

            if (e->getID() == MouseEvent::MOUSE_PRESSED) {
                this->pushed = true;
                repaint();
            } else if (e->getID() == MouseEvent::MOUSE_RELEASED || 
                        (e->getID() == MouseEvent::MOUSE_EXITED && 
                            this->pushed == true))
            {
                this->pushed = false;
                repaint();
            }
        }

        /** �{�^���̃��x�����A�w�肳�ꂽ������ɐݒ肵�܂��B*/
        void Button::setLabel(const char* label) {
            if (this->label != NULL) delete this->label;
            int I = strlen(label) + 1;
            this->label = new char[I];
            memcpy(this->label, label, I);
        }
    }
}
