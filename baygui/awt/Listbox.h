#if !defined(_BAYGUI_AWT_LISTBOX_H_INCLUDED_)
#define _BAYGUI_AWT_LISTBOX_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * List コンポーネントは、テキスト項目のスクロールリストをユーザに対して表示します。
        */
        class Listbox : public Component {
        protected:
            /** スクロールリストです。*/
            ArrayList* items;
            /** 選択位置です。*/
            int selectedIndex;
            
        public:
            /** 新しいスクロールリストを作成します。*/
            Listbox();

            /** デストラクタです。*/
            virtual ~Listbox();

            /** 指定された項目をスクロールリストの終わりに追加します。*/
            void add(const char* item);

            /** 指定するインデックスに対応する項目を返します。*/
            char* getItem(int index);

            /** リストで選択されている項目のインデックスを返します。*/
            int getSelectedIndex();

            /** リスト内の項目の数を返します。*/
            int getItemCount();

            /** このコンポーネントをペイントします。*/
            virtual void paint(Graphics* g);

            /** このコンポーネントで発生するマウスイベントを処理します。*/
            virtual void processMouseEvent(MouseEvent* e);
        };
    }
}

#endif
