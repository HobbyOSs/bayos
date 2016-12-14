#include "../../baygui.h"

namespace baygui {
    namespace lang {
        /** デフォルトコンストラクタです。 */
        Object::Object() {
            this->_elements = new int[defaultCapacity];
            this->_size = 0;
            this->_capacity = defaultCapacity;
            addClassName(baygui_lang_Object);
        }

        /** デストラクタです。 */
        Object::~Object() {
            delete [] this->_elements;
        }

        /** C++ による擬似 instaceof のために使用します。*/
        void Object::addClassName(int className) {
            if (this->_size == this->_capacity) {
                /* 足りなくなったら容量を倍に増やす */
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

        /** C++ による擬似 instanceof です。*/
        bool Object::instanceof(int className) {
            for (int i = this->_size - 1; i >= 0; i--) {
                if (className == this->_elements[i]) return true;
            }
            return false;
        }

        /** C++ による擬似 instaceof のために使用します。*/
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
