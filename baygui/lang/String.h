#if !defined(_BAYGUI_LANG_STRING_H_INCLUDED_)
#define _BAYGUI_LANG_STRING_H_INCLUDED_

using namespace baygui::lang;
using namespace baygui::util;

namespace baygui {
    namespace lang {
        class String : public Object {
        private:
            /** 内部で使う文字列です。*/
            char* _buffer;
            /** 内部で使う文字列のバイト長です。*/
            int _len;

        public:
            /** 新しく生成された String オブジェクトを初期化して、空の文字シーケンスを表すようにします。*/
            String();

            /** 新しい String を割り当てて、これが文字配列引数に現在含まれている文字シーケンスを表すようにします。*/
            String(const char* text);

            /** 文字配列引数の部分配列からなる文字を含む新しい String を割り当てます。*/
            String(const char* text, int start, int length);

            /** デストラクタです。*/
            ~String();

            /** この文字列が、指定された接尾辞で終るかどうかを判定します。*/
            bool endsWith(const char* text);

            /** この文字列の長さを返します。*/
            int length();

            /** この文字列を、指定された文字に一致する位置で分割します。*/
            ArrayList* split(char ch);

            /** この文字列が、指定された接頭辞で始まるかどうかを判定します。*/
            bool startsWith(const char* text);

            /**
             * String をプラットフォームのデフォルトの文字エンコーディング（UTF-8）に従ってバイトに変換し、
             * 結果を新しいバイト配列に格納します。
            */
            char* toCharArray();
        };
    }
}

#endif
