#if !defined(_BAYGUI_LANG_OBJECT_H_INCLUDED_)
#define _BAYGUI_LANG_OBJECT_H_INCLUDED_

namespace baygui {
    namespace lang {
        /**
         * Object クラスは、クラス階層のルートです。
         * すべてのクラスは、スーパークラスとして Object を持ちます。
        */
        class Object {
        private:
            /** クラス名リストのデフォルト容量です。*/
            static const int defaultCapacity = 5;
            /** クラス名リスト内の要素一覧です。*/
            int* _elements;
            /** クラス名リスト内の要素数です。*/
            int _size;
            /** クラス名リストの現在の容量です。*/
            int _capacity;

        public:
            /** デフォルトコンストラクタです。 */
            Object();

            /** デストラクタです。 */
            virtual ~Object();

        protected:
            /** C++ による擬似 instaceof のために使用します。*/
            void addClassName(int className);

        public:
            /** C++ による擬似 instanceof です。*/
            bool instanceof(int className);

        protected:
            /** C++ による擬似 instaceof のために使用します。*/
            void removeClassName(int className);
        };
    }
}

#endif
