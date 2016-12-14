#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** デストラクタです。*/
        TextComponent::~TextComponent() {
            delete this->text;
        }

        /** このテキストコンポーネントのテキスト挿入キャレットの位置を返します。*/
        int TextComponent::getCaretPosition() {
            return this->position;
        }

        /** このテキストコンポーネントのテキストを返します。*/
        char* TextComponent::getText() {
            return this->text;
        }

        /** このテキストコンポーネントが編集可能であるかどうかを示します。*/
        bool TextComponent::isEditable() {
            return this->editable;
        }

        /** このテキストコンポーネントにテキスト挿入キャレットの位置を設定します。 */
        void TextComponent::setCaretPosition(int position) {
            this->position = position;
        }

        /** このテキストコンポーネントが編集可能であるかどうかを設定します。*/
        void TextComponent::setEditable(bool b) {
            this->editable = b;
        }

        /** このテキストコンポーネントのテキストを、指定されたテキストに設定します。*/
        void TextComponent::setText(const char* text) {
            if (this->text != NULL) delete this->text;
            int I = strlen(text) + 1;
            this->text = new char[I];
            memcpy(this->text, text, I);
        }
    }
}
