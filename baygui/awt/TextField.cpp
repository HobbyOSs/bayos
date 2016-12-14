#include "../../baygui.h"

#define OFF_X 3
#define OFF_Y 3

namespace baygui {
    namespace awt {
        /** �V�����e�L�X�g�t�B�[���h���\�z���܂��B*/
        TextField::TextField() {
            addClassName(baygui_awt_TextField);
            this->background = Color::white;
            this->text = NULL;
        }

        /** �w�肳�ꂽ�e�L�X�g�ŏ��������ꂽ�V�����e�L�X�g�t�B�[���h���\�z���܂��B*/
        TextField::TextField(const char* text) {
            addClassName(baygui_awt_TextField);
            this->background = Color::white;
            setText(text);
        }

        /** ���̃R���|�[�l���g���y�C���g���܂��B*/
        void TextField::paint(Graphics* g) {
            int w = getWidth();
            int h = getHeight();

            /* �O�g��`�� */
            if (hasFocus() == true && isEnabled() == true) {
                g->setColor(0, 128, 255);
                g->drawRect(0, 0, w, h);
            } else {
                g->setColor(getParent()->getBackground());
                g->drawRect(0, 0, w, h);
            }

            /* ���g��`�� */
            g->setColor(getBackground());
            g->fillRect(1, 1, w - 2, h - 2);
            g->setColor(getForeground());
            g->drawRect(1, 1, w - 2, h - 2);

            /* �������`�� */
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
