#if !defined(_BAYGUI_AWT_LABEL_H_INCLUDED_)
#define _BAYGUI_AWT_LABEL_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * Label オブジェクトは、コンテナ内にテキストを配置するためのコンポーネントです。
         * ラベルは、単一行の読み取り専用テキストを表示します。
         * テキストを変更するにはアプリケーションを使い、ユーザが直接編集することはできません。
        */
        class Label : public Component {
        public:
            /** ラベルが中央揃えされることを示します。*/
            static const int CENTER = 1;
            /** ラベルが左揃えされることを示します。*/
            static const int LEFT   = 2;
            /** ラベルが右揃えされることを示します。*/
            static const int RIGHT  = 3;

        protected:
            /** このラベルの配置です。*/
            int alignment;
            /** このラベルのテキストです。*/
            char* text;
            
        public:
            /** 空のラベルを構築します。*/
            Label();

            /** 新しいラベルを左揃えして、指定されたテキスト文字列で構築します。*/
            Label(const char* text);

            /** 指定されたテキスト文字列を、指定された配置で表示する新しいラベルを構築します。*/
            Label(const char* text, int alignment);

            /** デストラクタです。*/
            virtual ~Label();

            /** このラベルの現在の配置を返します。*/
            int getAlignment();

            /** このラベルのテキストを返します。*/
            char* getText();

            /** このコンポーネントをペイントします。*/
            virtual void paint(Graphics* g);

            /** このラベルの配置を、指定された配置に設定します。*/
            void setAlignment(int alignment);

            /** このラベルのテキストを、指定されたテキストに設定します。*/
            void setText(const char* text);
        };
    }
}

#endif
