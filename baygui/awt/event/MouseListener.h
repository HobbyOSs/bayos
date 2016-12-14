#if !defined(_BAYGUI_AWT_EVENT_MOUSELISTENER_H_INCLUDED_)
#define _BAYGUI_AWT_EVENT_MOUSELISTENER_H_INCLUDED_

namespace baygui {
    namespace awt {
        namespace event {
            /**
             * コンポーネント上の「関連する」マウスイベント
             * (プレス、リリース、クリック、コンポーネントへの出入り) 
             * を受け取るためのリスナーインタフェースです。
             * マウスの移動およびドラッグを追跡するには、MouseMotionListener を使用します。
            */
            class MouseListener {
            public:
                /** コンポーネントにマウスが入ると呼び出されます。*/
                virtual void mouseEntered(MouseEvent* e) {};
                /** コンポーネントからマウスが出ると呼び出されます。*/
                virtual void mouseExited(MouseEvent* e) {};
                /** コンポーネント上でマウスボタンが押されると呼び出されます。*/
                virtual void mousePressed(MouseEvent* e) {};
                /** コンポーネント上でマウスボタンが離されると呼び出されます。*/
                virtual void mouseReleased(MouseEvent* e) {};
            };
        }
    }
}

#endif
