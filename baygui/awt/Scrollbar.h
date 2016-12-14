#if !defined(_BAYGUI_AWT_SCROLLBAR_H_INCLUDED_)
#define _BAYGUI_AWT_SCROLLBAR_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         �����E�����X�N���[���o�[�N���X
        */
        class Scrollbar : public Component {
        public:
            /** �����X�N���[���o�[ */
            static const int HORIZONTAL = 0;
            /** �����X�N���[���o�[ */
            static const int VERTICAL   = 1;

        protected:
            /** �X�N���[���o�[�̎�ނł��B*/
            int orientation;
            /** �ŏ��l�ł��B*/
            int minimum;
            /** �ő�l�ł��B*/
            int maximum;
            /** �u�u���b�N�v�����l�ł��B*/
            int blocksize;
            /** ��O�̒l�ł��B*/
            int preValue;
            /** ���݂̒l�ł��B*/
            int value;

        public:
            /** �V���������X�N���[���o�[���\�z���܂��B*/
            Scrollbar();

            /** �w�肳�ꂽ�����̐V�����X�N���[���o�[���\�z���܂��B*/
            Scrollbar(int orientation);

            /** �f�X�g���N�^�ł��B*/
            virtual ~Scrollbar();

            /** ���̃X�N���[���o�[�́u�u���b�N�v�����l��Ԃ��܂��B*/
            int getBlocksize();

            /** ���̃X�N���[���o�[�̍ő�l��Ԃ��܂��B*/
            int getMaximum();

            /** ���̃X�N���[���o�[�̍ŏ��l��Ԃ��܂��B*/
            int getMinimum();

            /** ���̃X�N���[���o�[�̌��ݒl��Ԃ��܂��B*/
            int getValue();

            /** ���̃R���|�[�l���g���y�C���g���܂��B*/
            virtual void paint(Graphics* g);

            /** ���̃R���|�[�l���g�Ŕ�������}�E�X�C�x���g���������܂��B*/
            virtual void processMouseEvent(MouseEvent* e);

            /** ���̃R���|�[�l���g�Ŕ�������}�E�X���[�V�����C�x���g���������܂��B*/
            virtual void processMouseMotionEvent(MouseEvent* e);

            /** ���̃X�N���[���o�[�́u�u���b�N�v�����l��ݒ肵�܂��B*/
            void setBlocksize(int n);

            /** ���̃X�N���[���o�[�̍ő�l��ݒ肵�܂��B*/
            void setMaximum(int n);

            /** ���̃X�N���[���o�[�̍ŏ��l��ݒ肵�܂��B*/
            void setMinimum(int n);

            /**
             * ���̃R���|�[�l���g���ړ����A�T�C�Y�ύX���܂��B
             * �����X�N���[���o�[�̎��͕���16�A�����X�N���[���o�[�̂Ƃ��͍�����16�ɂȂ�܂��B
             * ����ȊO�̒l��ݒ肵�Ă�16�ɂȂ�܂��B
            */
            virtual void setBounds(int x, int y, int w, int h);

            /** ���̃X�N���[���o�[�̒l���A�w�肳�ꂽ�l�ɐݒ肵�܂��B*/
            void setValue(int value);
        };
    }
}

#endif
