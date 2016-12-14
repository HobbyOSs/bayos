#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** �f�X�g���N�^�ł��B*/
        TextComponent::~TextComponent() {
            delete this->text;
        }

        /** ���̃e�L�X�g�R���|�[�l���g�̃e�L�X�g�}���L�����b�g�̈ʒu��Ԃ��܂��B*/
        int TextComponent::getCaretPosition() {
            return this->position;
        }

        /** ���̃e�L�X�g�R���|�[�l���g�̃e�L�X�g��Ԃ��܂��B*/
        char* TextComponent::getText() {
            return this->text;
        }

        /** ���̃e�L�X�g�R���|�[�l���g���ҏW�\�ł��邩�ǂ����������܂��B*/
        bool TextComponent::isEditable() {
            return this->editable;
        }

        /** ���̃e�L�X�g�R���|�[�l���g�Ƀe�L�X�g�}���L�����b�g�̈ʒu��ݒ肵�܂��B */
        void TextComponent::setCaretPosition(int position) {
            this->position = position;
        }

        /** ���̃e�L�X�g�R���|�[�l���g���ҏW�\�ł��邩�ǂ�����ݒ肵�܂��B*/
        void TextComponent::setEditable(bool b) {
            this->editable = b;
        }

        /** ���̃e�L�X�g�R���|�[�l���g�̃e�L�X�g���A�w�肳�ꂽ�e�L�X�g�ɐݒ肵�܂��B*/
        void TextComponent::setText(const char* text) {
            if (this->text != NULL) delete this->text;
            int I = strlen(text) + 1;
            this->text = new char[I];
            memcpy(this->text, text, I);
        }
    }
}
