#if !defined(_BAYGUI_UTIL_ARRAYLIST_H_INCLUDED_)
#define _BAYGUI_UTIL_ARRAYLIST_H_INCLUDED_

using namespace baygui::lang;

namespace baygui {
    namespace util {
        /** List インタフェースのサイズ変更可能な配列の実装です。*/
        class ArrayList : public Object {
        private:
            /** リストのデフォルト容量です。*/
            static const int defaultCapacity = 5;
            /** リスト内の要素一覧です。*/
            Object** _elements;
            /** リスト内の要素数です。*/
            int _size;
            /** リストの現在の容量です。*/
            int _capacity;

        private:
            /** プライベート変数の初期化を行います。*/
            void initialize();

        public:
            /** 空のリストを作成します。*/
            ArrayList();

            /** デストラクタです。*/
            virtual ~ArrayList();

            /** リストの指定された位置に、指定された要素を挿入します。*/
            bool add(Object* o);

            /** リストからすべての要素を削除します。*/
            void clear();

            /** リストに指定の要素がある場合に true を返します。*/
            bool contains(Object* elem);

            /** リスト内の指定された位置にある要素を返します。*/
            Object* get(int index);

            /** 指定された引数と同じ内容の要素を先頭から検索します。*/
            int indexOf(Object* elem);

            /** リストに要素がないかどうかを判定します。*/
            bool isEmpty();

            /** リスト内の指定された位置から要素を削除します。*/
            Object* remove(int index);

            /** リスト内にある要素の数を返します。*/
            int size();

            /** リスト内のすべての要素が正しい順序で格納されている配列を返します。*/
            Object** toArray();
        };
    }
}

#endif
