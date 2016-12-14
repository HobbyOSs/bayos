#if !defined(_BAYGUI_AWT_BUTTON_H_INCLUDED_)
#define _BAYGUI_AWT_BUTTON_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * ���̃N���X�̓��x���t���{�^�����쐬���܂��B
         * �A�v���P�[�V�����́A�{�^���������ꂽ�Ƃ��ɃA�N�V������
         * ���s�����悤�ɂ��邱�Ƃ��ł��܂��B
        */
        class Button : public Component {
        protected:
            /** ���̃{�^���������ꂽ���ǂ����������܂��B*/
            bool pushed;
            /** ���̃{�^���̃��x���ł��B*/
            char* label;
            
        public:
            /** ���x���Ȃ��̃{�^�����\�z���܂��B*/
            Button();

            /** �w�肳�ꂽ���x�����t�����{�^�����\�z���܂��B*/
            Button(const char* label);

            /** �f�X�g���N�^�ł��B*/
            virtual ~Button();

            /** �{�^���̃��x����Ԃ��܂��B*/
            char* getLabel();

            /** ���̃R���|�[�l���g���y�C���g���܂��B*/
            virtual void paint(Graphics* g);

            /** ���̃R���|�[�l���g�Ŕ�������}�E�X�C�x���g���������܂��B*/
            virtual void processMouseEvent(MouseEvent* e);

            /** �{�^���̃��x�����A�w�肳�ꂽ������ɐݒ肵�܂��B*/
            void setLabel(const char* label);
        };
    }
}

#endif
