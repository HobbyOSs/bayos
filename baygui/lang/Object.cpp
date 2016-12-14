#include "../../baygui.h"

namespace baygui {
    namespace lang {
        /** �f�t�H���g�R���X�g���N�^�ł��B */
        Object::Object() {
            this->_elements = new int[defaultCapacity];
            this->_size = 0;
            this->_capacity = defaultCapacity;
            addClassName(baygui_lang_Object);
        }

        /** �f�X�g���N�^�ł��B */
        Object::~Object() {
            delete [] this->_elements;
        }

        /** C++ �ɂ��[�� instaceof �̂��߂Ɏg�p���܂��B*/
        void Object::addClassName(int className) {
            if (this->_size == this->_capacity) {
                /* ����Ȃ��Ȃ�����e�ʂ�{�ɑ��₷ */
                this->_capacity <<= 1;
                int* ptr = new int[this->_capacity];
                for (int i = 0; i < this->_size; i++) {
                    ptr[i] = this->_elements[i];
                }
                delete [] this->_elements;
                this->_elements = ptr;
            }
            this->_elements[this->_size] = className;
            this->_size++;
        }

        /** C++ �ɂ��[�� instanceof �ł��B*/
        bool Object::instanceof(int className) {
            for (int i = this->_size - 1; i >= 0; i--) {
                if (className == this->_elements[i]) return true;
            }
            return false;
        }

        /** C++ �ɂ��[�� instaceof �̂��߂Ɏg�p���܂��B*/
        void Object::removeClassName(int className) {
            int index;
            for (index = this->_size - 1; index >= 0; index--) {
                if (className == this->_elements[index]) break;
            }
            if (index < 0) return;
            this->_size--;
            for (int i = index; i < this->_size; i++) {
                this->_elements[i] = this->_elements[i + 1];
            }
        }
    }
}
