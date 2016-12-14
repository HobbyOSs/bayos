#if !defined(_BAYGUI_AWT_EVENT_KEYLISTENER_H_INCLUDED_)
#define _BAYGUI_AWT_EVENT_KEYLISTENER_H_INCLUDED_

namespace baygui {
    namespace awt {
        namespace event {
            /** このリスナーは、キーボードイベント (キーストローク) を受け取るためのインタフェースです。*/
            class KeyListener {
            public:
                /** キーを押しているときに呼び出されます。*/
                virtual void keyPressed(KeyEvent* e) {};
                /** キーを離したときに呼び出されます。*/
                virtual void keyReleased(KeyEvent* e) {};
            };
        }
    }
}

#endif
