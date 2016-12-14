#if !defined(_BAYGUI_AWT_LABEL_H_INCLUDED_)
#define _BAYGUI_AWT_LABEL_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * Label �I�u�W�F�N�g�́A�R���e�i���Ƀe�L�X�g��z�u���邽�߂̃R���|�[�l���g�ł��B
         * ���x���́A�P��s�̓ǂݎ���p�e�L�X�g��\�����܂��B
         * �e�L�X�g��ύX����ɂ̓A�v���P�[�V�������g���A���[�U�����ڕҏW���邱�Ƃ͂ł��܂���B
        */
        class Label : public Component {
        public:
            /** ���x����������������邱�Ƃ������܂��B*/
            static const int CENTER = 1;
            /** ���x��������������邱�Ƃ������܂��B*/
            static const int LEFT   = 2;
            /** ���x�����E��������邱�Ƃ������܂��B*/
            static const int RIGHT  = 3;

        protected:
            /** ���̃��x���̔z�u�ł��B*/
            int alignment;
            /** ���̃��x���̃e�L�X�g�ł��B*/
            char* text;
            
        public:
            /** ��̃��x�����\�z���܂��B*/
            Label();

            /** �V�������x�������������āA�w�肳�ꂽ�e�L�X�g������ō\�z���܂��B*/
            Label(const char* text);

            /** �w�肳�ꂽ�e�L�X�g��������A�w�肳�ꂽ�z�u�ŕ\������V�������x�����\�z���܂��B*/
            Label(const char* text, int alignment);

            /** �f�X�g���N�^�ł��B*/
            virtual ~Label();

            /** ���̃��x���̌��݂̔z�u��Ԃ��܂��B*/
            int getAlignment();

            /** ���̃��x���̃e�L�X�g��Ԃ��܂��B*/
            char* getText();

            /** ���̃R���|�[�l���g���y�C���g���܂��B*/
            virtual void paint(Graphics* g);

            /** ���̃��x���̔z�u���A�w�肳�ꂽ�z�u�ɐݒ肵�܂��B*/
            void setAlignment(int alignment);

            /** ���̃��x���̃e�L�X�g���A�w�肳�ꂽ�e�L�X�g�ɐݒ肵�܂��B*/
            void setText(const char* text);
        };
    }
}

#endif
