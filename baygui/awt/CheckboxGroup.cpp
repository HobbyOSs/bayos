#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** CheckboxGroup �̐V�����C���X�^���X�𐶐����܂��B*/
        CheckboxGroup::CheckboxGroup() {
            addClassName(baygui_awt_CheckboxGroup);
            this->checkboxes = new ArrayList();
            this->selectedCheckbox = NULL;
        }

        /** �f�X�g���N�^�ł��B*/
        CheckboxGroup::~CheckboxGroup() {
            delete(this->checkboxes);
        }

        /** Checkbox��ݒ肵�܂��B*/
        void CheckboxGroup::add(Checkbox* box) {
            this->checkboxes->add(box);
            box->group = this;
        }

        /** ���̃`�F�b�N�{�b�N�X�O���[�v�ł̌��݂̑I����Ԃ��܂��B*/
        Checkbox* CheckboxGroup::getSelectedCheckbox() {
            return this->selectedCheckbox;
        }

        /** ���݂��̃O���[�v���őI������Ă���`�F�b�N�{�b�N�X���A�w�肳�ꂽ�`�F�b�N�{�b�N�X�ɐݒ肵�܂��B*/
        void CheckboxGroup::setSelectedCheckbox(Checkbox* box) {
            int I = this->checkboxes->size();
            for (int i = 0; i < I; i++) {
                Checkbox* temp = (Checkbox *) this->checkboxes->get(i);
                if (box != temp && temp->getState() == true) {
                    temp->setState(false);
                }
            }
            this->selectedCheckbox = box;
        }
    }
}
