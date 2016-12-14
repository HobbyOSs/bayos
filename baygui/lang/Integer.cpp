#include "../../baygui.h"

namespace baygui {
    namespace lang {
        /** プリミティブな int の引数を表す、新しく割り当てられた Integer オブジェクトを構築します。*/
        Integer::Integer(int value) {
            addClassName(baygui_lang_Integer);
            this->value = value;
        }

        /** 文字列で表現される数値を表す、新しく割り当てられた Integer オブジェクトを生成します。*/
        Integer::Integer(const char* s) {
            addClassName(baygui_lang_Integer);
            this->value = atoi(s);
        }

        /** このオブジェクトを指定されたオブジェクトと比較します。*/
        bool Integer::equals(Object* obj) {
            return this->intValue() == ((Integer *) obj)->intValue();
        }

        /** この Integer の値を int 値として返します。*/
        int Integer::intValue() {
            return this->value;
        }

        /** 文字列の引数を符号付き 10 進数の整数型として解析します。*/
        int Integer::parseInt(const char* s) {
            return atoi(s);
        }
    }
}
