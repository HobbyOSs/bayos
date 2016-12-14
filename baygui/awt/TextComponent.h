#if !defined(_BAYGUI_AWT_TEXTCOMPONENT_H_INCLUDED_)
#define _BAYGUI_AWT_TEXTCOMPONENT_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * TextComponent クラスは、テキストの編集を可能にするすべてのコンポーネントのスーパークラスです。
        */
        class TextComponent : public Component {
        protected:
            /** このテキストコンポーネントが編集可能かどうかをあらわします。*/
            bool editable;
            /** このテキストコンポーネントの現在のテキスト挿入キャレットの位置です。*/
            int position;
            /** このテキストコンポーネントのテキストです。*/
            char* text;
            
        public:
            /** デストラクタです。*/
            virtual ~TextComponent();

            /** このテキストコンポーネントのテキスト挿入キャレットの位置を返します。*/
            int getCaretPosition();

            /** このテキストコンポーネントのテキストを返します。*/
            char* getText();

            /** このテキストコンポーネントが編集可能であるかどうかを示します。*/
            bool isEditable();

            /** このテキストコンポーネントにテキスト挿入キャレットの位置を設定します。 */
            void setCaretPosition(int position);

            /** このテキストコンポーネントが編集可能であるかどうかを設定します。*/
            void setEditable(bool b);

            /** このテキストコンポーネントのテキストを、指定されたテキストに設定します。*/
            void setText(const char* text);
        };
    }
}

#endif
