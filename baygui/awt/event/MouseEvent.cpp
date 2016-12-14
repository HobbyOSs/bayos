#include "../../../baygui.h"

namespace baygui {
    namespace awt {
        namespace event {
            /** �f�t�H���g�R���X�g���N�^�ł��B*/
            MouseEvent::MouseEvent() {
                addClassName(baygui_awt_event_MouseEvent);
                this->consumed = false;
                this->id = 0;
                this->source = NULL;
                this->modifiers = 0;
                this->x = 0;
                this->y = 0;
            }

            /** �w�肳�ꂽ�\�[�X�I�u�W�F�N�g�ƌ^���g�p���āAMouseEvent �I�u�W�F�N�g���\�z���܂��B*/
            MouseEvent::MouseEvent(Object* source, int id, int modifiers, int x, int y) {
                addClassName(baygui_awt_event_MouseEvent);
                this->consumed = false;
                this->id = id;
                this->source = source;
                this->modifiers = modifiers;
                this->x = x;
                this->y = y;
            }

            /** ���̃C�x���g�Ɋ֘A�����{�^���̎�ނ�Ԃ��܂��B*/
            int MouseEvent::getModifiers() {
                return this->modifiers;
            }

            /** �C�x���g�����������ʒu�� X ���W�𔭐����̃R���|�[�l���g�ɑ΂��鑊�Έʒu�ŕԂ��܂��B*/
            int MouseEvent::getX() {
                return this->x;
            }

            /** �C�x���g�����������ʒu�� Y ���W�𔭐����̃R���|�[�l���g�ɑ΂��鑊�Έʒu�ŕԂ��܂��B*/
            int MouseEvent::getY() {
                return this->y;
            }
        }
    }
}
