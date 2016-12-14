#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** �f�t�H���g�R���X�g���N�^�ł��B*/
        AWTEvent::AWTEvent() {
            this->consumed = false;
            this->id = 0;
            this->source = NULL;
        }

        /** �C�x���g������܂��B*/
        void AWTEvent::consume() {
            this->consumed = true;
        }

        /* �C�x���g�̌^��Ԃ��܂��B*/
        int AWTEvent::getID() {
            return this->id;
        }

        /** Event ���ŏ��ɔ��������I�u�W�F�N�g�ł��B*/
        Object* AWTEvent::getSource() {
            return this->source;
        }

        /** �C�x���g������ꂽ���ǂ�����Ԃ��܂��B*/
        bool AWTEvent::isConsumed() {
            return this->consumed;
        }
    }
}
