#if !defined(_BAYGUI_AWT_TEXTCOMPONENT_H_INCLUDED_)
#define _BAYGUI_AWT_TEXTCOMPONENT_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * TextComponent �N���X�́A�e�L�X�g�̕ҏW���\�ɂ��邷�ׂẴR���|�[�l���g�̃X�[�p�[�N���X�ł��B
        */
        class TextComponent : public Component {
        protected:
            /** ���̃e�L�X�g�R���|�[�l���g���ҏW�\���ǂ���������킵�܂��B*/
            bool editable;
            /** ���̃e�L�X�g�R���|�[�l���g�̌��݂̃e�L�X�g�}���L�����b�g�̈ʒu�ł��B*/
            int position;
            /** ���̃e�L�X�g�R���|�[�l���g�̃e�L�X�g�ł��B*/
            char* text;
            
        public:
            /** �f�X�g���N�^�ł��B*/
            virtual ~TextComponent();

            /** ���̃e�L�X�g�R���|�[�l���g�̃e�L�X�g�}���L�����b�g�̈ʒu��Ԃ��܂��B*/
            int getCaretPosition();

            /** ���̃e�L�X�g�R���|�[�l���g�̃e�L�X�g��Ԃ��܂��B*/
            char* getText();

            /** ���̃e�L�X�g�R���|�[�l���g���ҏW�\�ł��邩�ǂ����������܂��B*/
            bool isEditable();

            /** ���̃e�L�X�g�R���|�[�l���g�Ƀe�L�X�g�}���L�����b�g�̈ʒu��ݒ肵�܂��B */
            void setCaretPosition(int position);

            /** ���̃e�L�X�g�R���|�[�l���g���ҏW�\�ł��邩�ǂ�����ݒ肵�܂��B*/
            void setEditable(bool b);

            /** ���̃e�L�X�g�R���|�[�l���g�̃e�L�X�g���A�w�肳�ꂽ�e�L�X�g�ɐݒ肵�܂��B*/
            void setText(const char* text);
        };
    }
}

#endif
