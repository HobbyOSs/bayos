#if !defined(_BAYGUI_AWT_EVENT_MOUSEMOTIONLISTENER_H_INCLUDED_)
#define _BAYGUI_AWT_EVENT_MOUSEMOTIONLISTENER_H_INCLUDED_

namespace baygui {
    namespace awt {
        namespace event {
            /** コンポーネント上のマウスモーションイベントを受け取るためのリスナーインタフェースです。クリックおよびその他のイベントには、MouseListener を使用します。*/
            class MouseMotionListener {
            public:
                /** コンポーネント上でマウスのボタンが押されたあとドラッグされたときに呼び出されます。*/
                virtual void mouseDragged(MouseEvent* e) {};
                /** コンポーネント上でマウスが移動される (ボタンは押されない) と呼び出されます。*/
                virtual void mouseMoved(MouseEvent* e) {};
            };
        }
    }
}

#endif
