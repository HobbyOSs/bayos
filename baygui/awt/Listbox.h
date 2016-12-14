#if !defined(_BAYGUI_AWT_LISTBOX_H_INCLUDED_)
#define _BAYGUI_AWT_LISTBOX_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * List �R���|�[�l���g�́A�e�L�X�g���ڂ̃X�N���[�����X�g�����[�U�ɑ΂��ĕ\�����܂��B
        */
        class Listbox : public Component {
        protected:
            /** �X�N���[�����X�g�ł��B*/
            ArrayList* items;
            /** �I���ʒu�ł��B*/
            int selectedIndex;
            
        public:
            /** �V�����X�N���[�����X�g���쐬���܂��B*/
            Listbox();

            /** �f�X�g���N�^�ł��B*/
            virtual ~Listbox();

            /** �w�肳�ꂽ���ڂ��X�N���[�����X�g�̏I���ɒǉ����܂��B*/
            void add(const char* item);

            /** �w�肷��C���f�b�N�X�ɑΉ����鍀�ڂ�Ԃ��܂��B*/
            char* getItem(int index);

            /** ���X�g�őI������Ă��鍀�ڂ̃C���f�b�N�X��Ԃ��܂��B*/
            int getSelectedIndex();

            /** ���X�g���̍��ڂ̐���Ԃ��܂��B*/
            int getItemCount();

            /** ���̃R���|�[�l���g���y�C���g���܂��B*/
            virtual void paint(Graphics* g);

            /** ���̃R���|�[�l���g�Ŕ�������}�E�X�C�x���g���������܂��B*/
            virtual void processMouseEvent(MouseEvent* e);
        };
    }
}

#endif
