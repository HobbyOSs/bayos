#if !defined(_BAYGUI_AWT_EVENT_MOUSEEVENT_H_INCLUDED_)
#define _BAYGUI_AWT_EVENT_MOUSEEVENT_H_INCLUDED_

using namespace baygui::lang;
using namespace baygui::awt;

namespace baygui {
    namespace awt {
        namespace event {
            /** コンポーネント内でマウスアクションが発生したことを示すイベントです。*/
            class MouseEvent : public AWTEvent {
            public:
                enum {
                    /**「マウスエンター」イベントです。*/
                    MOUSE_ENTERED  = 200,
                    /**「マウスイグジット」イベントです。*/
                    MOUSE_EXITED   = 201,
                    /**「マウスプレス」イベントです。*/
                    MOUSE_PRESSED  = 202,
                    /**「マウスリリース」イベントです。*/
                    MOUSE_RELEASED = 203,
                    /**「マウスドラッグ」イベントです。*/
                    MOUSE_DRAGGED  = 204,
                    /**「マウスムーブ」イベントです。*/
                    MOUSE_MOVED    = 205
                };

            private:
                /** イベントが発生した位置の X 座標です。*/
                int x;
                /** イベントが発生した位置の Y 座標です。*/
                int y;
                /** このイベントに関連したボタンの種類です。*/
                int modifiers;

            public:
                /** デフォルトコンストラクタです。*/
                MouseEvent();

                /** 指定されたソースオブジェクトと型を使用して、MouseEvent オブジェクトを構築します。*/
                MouseEvent(Object* source, int id, int modifiers, int x, int y);

                /** このイベントに関連したボタンの種類を返します。*/
                int getModifiers();

                /** イベントが発生した位置の X 座標を発生元のコンポーネントに対する相対位置で返します。*/
                int getX();

                /** イベントが発生した位置の Y 座標を発生元のコンポーネントに対する相対位置で返します。*/
                int getY();
            };
        }
    }
}

#endif
