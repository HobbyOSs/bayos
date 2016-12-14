#include "../../baygui.h"

namespace baygui {
    namespace lang {
        /** �v���~�e�B�u�� int �̈�����\���A�V�������蓖�Ă�ꂽ Integer �I�u�W�F�N�g���\�z���܂��B*/
        Integer::Integer(int value) {
            addClassName(baygui_lang_Integer);
            this->value = value;
        }

        /** ������ŕ\������鐔�l��\���A�V�������蓖�Ă�ꂽ Integer �I�u�W�F�N�g�𐶐����܂��B*/
        Integer::Integer(const char* s) {
            addClassName(baygui_lang_Integer);
            this->value = atoi(s);
        }

        /** ���̃I�u�W�F�N�g���w�肳�ꂽ�I�u�W�F�N�g�Ɣ�r���܂��B*/
        bool Integer::equals(Object* obj) {
            return this->intValue() == ((Integer *) obj)->intValue();
        }

        /** ���� Integer �̒l�� int �l�Ƃ��ĕԂ��܂��B*/
        int Integer::intValue() {
            return this->value;
        }

        /** ������̈����𕄍��t�� 10 �i���̐����^�Ƃ��ĉ�͂��܂��B*/
        int Integer::parseInt(const char* s) {
            return atoi(s);
        }
    }
}
