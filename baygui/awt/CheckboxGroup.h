#if !defined(_BAYGUI_AWT_CHECKBOXGROUP_H_INCLUDED_)
#define _BAYGUI_AWT_CHECKBOXGROUP_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * CheckboxGroup �N���X�� Checkbox �{�^�����O���[�v������̂Ɏg�p���܂��B
        */
        class CheckboxGroup : public Object {
        protected:
            /** �`�F�b�N�{�b�N�X�ꗗ�ł��B*/
            ArrayList* checkboxes;
            /** �I�����ꂽ�`�F�b�N�{�b�N�X�ł��B*/
            Checkbox* selectedCheckbox;
            
        public:
            /** CheckboxGroup �̐V�����C���X�^���X�𐶐����܂��B*/
            CheckboxGroup();

            /** �f�X�g���N�^�ł��B*/
            virtual ~CheckboxGroup();

            /** Checkbox��ݒ肵�܂��B*/
            void add(Checkbox* box);

            /** ���̃`�F�b�N�{�b�N�X�O���[�v�ł̌��݂̑I����Ԃ��܂��B*/
            Checkbox* getSelectedCheckbox();

            /** ���݂��̃O���[�v���őI������Ă���`�F�b�N�{�b�N�X���A�w�肳�ꂽ�`�F�b�N�{�b�N�X�ɐݒ肵�܂��B*/
            void setSelectedCheckbox(Checkbox* box);
        };
    }
}

#endif
