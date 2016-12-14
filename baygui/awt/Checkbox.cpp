#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** ���`�F�b�N�i�p���b�g�j */
        static unsigned int unchecked_palette[] = {
            0xff040204,
            0xff8c8e8c,
            0xffe4e2e4,
            0xff4c4e4c,
            0xffb4b2b4,
            0xfffcfefc,
            0xffc0c0c0, /* �w�i�F */
            0xffeceeec,
            0xff5c5e5c,
            0xffc4c2c4,
        };

        /** ���`�F�b�N�i�f�[�^�j*/
        static unsigned char unchecked_data[] = {
            0x6,0x6,0x6,0x6,0x3,0x0,0x0,0x3,0x6,0x6,0x6,0x6,
            0x6,0x6,0x0,0x8,0x2,0x2,0x2,0x9,0x3,0x0,0x6,0x6,
            0x6,0x0,0x9,0x2,0x7,0x5,0x5,0x5,0x2,0x1,0x0,0x6,
            0x6,0x8,0x2,0x7,0x5,0x5,0x7,0x7,0x2,0x9,0x3,0x6,
            0x3,0x2,0x7,0x5,0x5,0x7,0x7,0x7,0x2,0x9,0x1,0x3,
            0x0,0x2,0x5,0x5,0x7,0x7,0x2,0x2,0x9,0x9,0x1,0x0,
            0x0,0x2,0x5,0x7,0x7,0x7,0x2,0x9,0x9,0x4,0x1,0x0,
            0x3,0x9,0x5,0x7,0x2,0x2,0x9,0x9,0x4,0x4,0x1,0x3,
            0x6,0x8,0x2,0x2,0x2,0x9,0x9,0x4,0x4,0x1,0x3,0x6,
            0x6,0x0,0x1,0x9,0x9,0x9,0x4,0x4,0x1,0x1,0x0,0x6,
            0x6,0x6,0x0,0x8,0x1,0x1,0x1,0x1,0x3,0x0,0x6,0x6,
            0x6,0x6,0x6,0x6,0x3,0x0,0x0,0x3,0x6,0x6,0x6,0x6,
        };

        /** �`�F�b�N�i�p���b�g�j */
        static unsigned int checked_palette[] = {
            0xff040204,
            0xff8c8e8c,
            0xff4c4e4c,
            0xffe4e2e4,
            0xffc0c0c0, /* �w�i�F */
            0xffc4c2c4,
            0xff7c7e7c,
            0xff2c2a2c,
            0xff9c9e9c,
            0xfffcfefc,
            0xff5c5e5c,
        };

        /** �`�F�b�N�i�f�[�^�j*/
        static unsigned char checked_data[] = {
            0x4,0x4,0x4,0x4,0x7,0x0,0x0,0x7,0x4,0x4,0x4,0x4,
            0x4,0x4,0x7,0x0,0x2,0xa,0xa,0xa,0x2,0x0,0x4,0x4,
            0x4,0x7,0x2,0xa,0x6,0x6,0x6,0x1,0x1,0x8,0x0,0x4,
            0x4,0x0,0xa,0x6,0x0,0x0,0x0,0x0,0x8,0x8,0x2,0x4,
            0x7,0x2,0x6,0x0,0x0,0x0,0x0,0x0,0x0,0x8,0x5,0x2,
            0x0,0xa,0x6,0x0,0x0,0x0,0x0,0x0,0x0,0x5,0x5,0x0,
            0x0,0xa,0x6,0x0,0x0,0x0,0x0,0x0,0x0,0x5,0x3,0x0,
            0x7,0xa,0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0x9,0x2,
            0x4,0x7,0x1,0x8,0x0,0x0,0x0,0x0,0x3,0x9,0x2,0x4,
            0x4,0x7,0x8,0x8,0x8,0x5,0x5,0x3,0x9,0x9,0x0,0x4,
            0x4,0x4,0x7,0x2,0x5,0x5,0x3,0x9,0x2,0x0,0x4,0x4,
            0x4,0x4,0x4,0x4,0x2,0x0,0x0,0x2,0x4,0x4,0x4,0x4,
        };

        /** ���x���Ȃ��̃`�F�b�N�{�b�N�X���\�z���܂��B*/
        Checkbox::Checkbox() {
            addClassName(baygui_awt_Checkbox);
            this->state = false;
            this->group = NULL;
            this->label = NULL;
        }

        /** �w�肳�ꂽ���x�����t�����`�F�b�N�{�b�N�X���\�z���܂��B*/
        Checkbox::Checkbox(const char* label) {
            addClassName(baygui_awt_Checkbox);
            this->state = false;
            this->group = NULL;
            setLabel(label);
        }

        /** �f�X�g���N�^�ł��B*/
        Checkbox::~Checkbox() {
            delete this->label;
        }

        /** �`�F�b�N�{�b�N�X�̃��x����Ԃ��܂��B*/
        char* Checkbox::getLabel() {
            return this->label;
        }

        /** ���̃`�F�b�N�{�b�N�X���u�I���v�̏�Ԃł��邩�A�u�I�t�v�̏�Ԃł��邩�𔻒肵�܂��B*/
        bool Checkbox::getState() {
            return this->state;
        }

        /** ���̃R���|�[�l���g���y�C���g���܂��B*/
        void Checkbox::paint(Graphics* g) {
            int w = getWidth();
            int h = getHeight();

            /* ��x�w�i�F�ŃN���A */
            g->setColor(getBackground());
            g->fillRect(0, 0, w, h);

            /* �������`�� */
            int fh = 12;
            int y = (h - fh) / 2;
            if (isEnabled() == true) {
                g->setColor(getForeground());
            } else {
                g->setColor(Color::gray);
            }
            g->drawString(getLabel(), 14, y);

            /* �`�F�b�N��`�� */
            for (int i = 0; i < 12; i++) {
                for (int j = 0; j < 12; j++) {
                    /* �`�F�b�N�̎���͔w�i�F�œh�� */
                    unsigned int c = 0;
                    if (this->state == true) {
                        c = checked_palette[checked_data[i * 12 + j] & 0xFF];
                    } else {
                        c = unchecked_palette[unchecked_data[i * 12 + j] & 0xFF];
                    }
                    if (c == 0xffc0c0c0) {
                        g->setColor(getBackground());
                    } else {
                        g->setColor(c);
                    }
                    g->drawPixel(j + 0, i + y);
                }
            }
        }

        /** ���̃R���|�[�l���g�Ŕ�������}�E�X�C�x���g���������܂��B*/
        void Checkbox::processMouseEvent(MouseEvent* e) {
            Component::processMouseEvent(e);

            if (e->getID() == MouseEvent::MOUSE_PRESSED) {
                if (this->state == false) {
                    setState(true);
                }
            }
        }

        /** �`�F�b�N�{�b�N�X�̃��x�����A�w�肳�ꂽ������ɐݒ肵�܂��B*/
        void Checkbox::setLabel(const char* label) {
            if (this->label != NULL) delete this->label;
            int I = strlen(label) + 1;
            this->label = new char[I];
            memcpy(this->label, label, I);
        }

        /** ���̃`�F�b�N�{�b�N�X�̏�Ԃ��A�w�肳�ꂽ��Ԃɐݒ肵�܂��B*/
        void Checkbox::setState(bool state) {
            if (this->state == true && state == false) {
                this->state = false;
                repaint();
            } else if (this->state == false && state == true) {
                this->state = true;
                if (this->group != NULL) {
                    this->group->setSelectedCheckbox(this);
                }
                repaint();
            }
        }
    }
}