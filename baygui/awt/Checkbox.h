#if !defined(_BAYGUI_AWT_CHECKBOX_H_INCLUDED_)
#define _BAYGUI_AWT_CHECKBOX_H_INCLUDED_

namespace baygui {
    namespace awt {
        class CheckboxGroup;

        /**
         * �`�F�b�N�{�b�N�X�́A�u�I���v (true) �܂��́u�I�t�v (false) ��
         * �ǂ��炩�̏�Ԃɂ��邱�Ƃ��ł���O���t�B�J���R���|�[�l���g�ł��B
        */
        class Checkbox : public Component {
        public:
            /** �`�F�b�N�{�b�N�X�O���[�v�ł��B*/
            CheckboxGroup* group;

        protected:
            /** ���̃`�F�b�N�{�b�N�X���`�F�b�N���ꂽ���ǂ����������܂��B*/
            bool state;
            /** ���̃`�F�b�N�{�b�N�X�̃��x���ł��B*/
            char* label;
            
        public:
            /** ���x���Ȃ��̃`�F�b�N�{�b�N�X���\�z���܂��B*/
            Checkbox();

            /** �w�肳�ꂽ���x�����t�����`�F�b�N�{�b�N�X���\�z���܂��B*/
            Checkbox(const char* label);

            /** �f�X�g���N�^�ł��B*/
            virtual ~Checkbox();

            /** �`�F�b�N�{�b�N�X�̃��x����Ԃ��܂��B*/
            char* getLabel();

            /** ���̃`�F�b�N�{�b�N�X���u�I���v�̏�Ԃł��邩�A�u�I�t�v�̏�Ԃł��邩�𔻒肵�܂��B*/
            bool getState();

            /** ���̃R���|�[�l���g���y�C���g���܂��B*/
            virtual void paint(Graphics* g);

            /** ���̃R���|�[�l���g�Ŕ�������}�E�X�C�x���g���������܂��B*/
            virtual void processMouseEvent(MouseEvent* e);

            /** �`�F�b�N�{�b�N�X�̃��x�����A�w�肳�ꂽ������ɐݒ肵�܂��B*/
            void setLabel(const char* label);

            /** ���̃`�F�b�N�{�b�N�X�̏�Ԃ��A�w�肳�ꂽ��Ԃɐݒ肵�܂��B*/
            void setState(bool state);
        };
    }
}

#endif
