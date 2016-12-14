#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** ��̃��x�����\�z���܂��B*/
        Label::Label() {
            addClassName(baygui_awt_Label);
            this->alignment = Label::LEFT;
            this->text = NULL;
        }

        /** �V�������x�������������āA�w�肳�ꂽ�e�L�X�g������ō\�z���܂��B*/
        Label::Label(const char* text) {
            addClassName(baygui_awt_Label);
            this->alignment = Label::LEFT;
            setText(text);
        }

        /** �w�肳�ꂽ�e�L�X�g��������A�w�肳�ꂽ�z�u�ŕ\������V�������x�����\�z���܂��B*/
        Label::Label(const char* text, int alignment) {
            addClassName(baygui_awt_Label);
            this->alignment = alignment;
            setText(text);
        }

        /** �f�X�g���N�^�ł��B*/
        Label::~Label() {
            delete this->text;
        }

        /** ���̃��x���̌��݂̔z�u��Ԃ��܂��B*/
        int Label::getAlignment() {
            return this->alignment;
        }

        /** ���̃��x���̃e�L�X�g��Ԃ��܂��B*/
        char* Label::getText() {
            return this->text;
        }

        /** ���̃R���|�[�l���g���y�C���g���܂��B*/
        void Label::paint(Graphics* g) {
            int w = getWidth();
            int h = getHeight();

            /* ��x�w�i�F�ŃN���A */
            g->setColor(getBackground());
            g->fillRect(0, 0, w, h);

            /* �������`�� */
            int fw = FontMetrice::stringWidth(this->text);
            int fh = FontMetrice::getHeight();
            if (isEnabled() == true) {
                g->setColor(getForeground());
            } else {
                g->setColor(Color::gray);
            }
            if (this->alignment == Label::RIGHT) {
                g->drawString(this->text, (w - fw), (h - fh) / 2);
            } else if (this->alignment == Label::CENTER) {
                g->drawString(this->text, (w - fw) / 2, (h - fh) / 2);
            } else {
                g->drawString(this->text, 0, (h - fh) / 2);
            }
        }

        /** ���̃��x���̔z�u���A�w�肳�ꂽ�z�u�ɐݒ肵�܂��B*/
        void Label::setAlignment(int alignment) {
            this->alignment = alignment;
        }

        /** ���̃��x���̃e�L�X�g���A�w�肳�ꂽ�e�L�X�g�ɐݒ肵�܂��B*/
        void Label::setText(const char* text) {
            if (this->text != NULL) delete this->text;
            int I = strlen(text) + 1;
            this->text = new char[I];
            memcpy(this->text, text, I);
        }
    }
}
