#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** CheckboxGroup の新しいインスタンスを生成します。*/
        CheckboxGroup::CheckboxGroup() {
            addClassName(baygui_awt_CheckboxGroup);
            this->checkboxes = new ArrayList();
            this->selectedCheckbox = NULL;
        }

        /** デストラクタです。*/
        CheckboxGroup::~CheckboxGroup() {
            delete(this->checkboxes);
        }

        /** Checkboxを設定します。*/
        void CheckboxGroup::add(Checkbox* box) {
            this->checkboxes->add(box);
            box->group = this;
        }

        /** このチェックボックスグループでの現在の選択を返します。*/
        Checkbox* CheckboxGroup::getSelectedCheckbox() {
            return this->selectedCheckbox;
        }

        /** 現在このグループ内で選択されているチェックボックスを、指定されたチェックボックスに設定します。*/
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
