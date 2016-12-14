#if !defined(_BAYGUI_AWT_AWTEVENT_H_INCLUDED_)
#define _BAYGUI_AWT_AWTEVENT_H_INCLUDED_

using namespace baygui::lang;

namespace baygui {
    namespace awt {
        /** すべての AWT イベント用のルートイベントクラスです。*/
        class AWTEvent : public Object {
        protected:
            /** イベントが消費されたかどうかを示すフラグです。*/
            bool consumed;
            /** イベントの型を示す値です。*/
            int id;
            /** Event が最初に発生したオブジェクトです。*/
            Object* source;

        public:
            /** デフォルトコンストラクタです。*/
            AWTEvent();

            /** イベントを消費します。*/
            void consume();

            /* イベントの型を返します。*/
            int getID();

            /** Event が最初に発生したオブジェクトです。*/
            Object* getSource();

            /** イベントが消費されたかどうかを返します。*/
            bool isConsumed();
        };
    }
}

#endif
