#include "../../baygui.h"

namespace baygui {
    namespace lang {
        /** 新しく生成された String オブジェクトを初期化して、空の文字シーケンスを表すようにします。*/
        String::String() {
            addClassName(baygui_lang_String);
            this->_buffer = NULL;
        }

        /** 新しい String を割り当てて、これが文字配列引数に現在含まれている文字シーケンスを表すようにします。*/
        String::String(const char* text) {
            addClassName(baygui_lang_String);
            this->_len = strlen(text);
            this->_buffer = new char[this->_len + 1];
            memcpy(this->_buffer, text, this->_len + 1);
        }

        /** 文字配列引数の部分配列からなる文字を含む新しい String を割り当てます。*/
        String::String(const char* text, int start, int length) {
            addClassName(baygui_lang_String);
            this->_len = length;
            this->_buffer = new char[length + 1];
            memcpy(this->_buffer, &text[start], length);
        }

        /** デストラクタです。*/
        String::~String() {
            delete this->_buffer;
        }

        /** この文字列が、指定された接尾辞で終るかどうかを判定します。*/
        bool String::endsWith(const char* text) {
            int len = strlen(text);
            int pos = this->_len - len;
            if (pos < 0) return false;
            for (int i = 0; i < len; i++) {
                if (this->_buffer[pos + i] != text[i]) return false;
            }
            return true;
        }

        /** この文字列の長さを返します。*/
        int String::length() {
            return this->_len;
        }

        /** この文字列を、指定された文字に一致する位置で分割します。*/
        ArrayList* String::split(char ch) {
            ArrayList* list = new ArrayList();
            int p = 0;
            for (int i = 0; i <= this->_len; i++) {
                if (i == this->_len || this->_buffer[i] == ch) {
                    if (i > p) {
                        list->add(new String(this->_buffer, p, i - p));
                    }
                    p = i + 1;
                }
            }
            return list;
        }

        /** この文字列が、指定された接頭辞で始まるかどうかを判定します。*/
        bool String::startsWith(const char* text) {
            int len = strlen(text);
            if (len > this->_len) return false;
            for (int i = 0; i < len; i++) {
                if (this->_buffer[i] != text[i]) return false;
            }
            return true;
        }

        /**
         * String をプラットフォームのデフォルトの文字エンコーディング（UTF-8）に従ってバイトに変換し、
         * 結果を新しいバイト配列に格納します。
        */
        char* String::toCharArray() {
            return this->_buffer;
        }
    }
}
