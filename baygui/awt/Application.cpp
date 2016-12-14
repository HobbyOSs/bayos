#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /* 静的変数の設定 */
        ArrayList* Application::frames = NULL;
        /** アプリケーションが実行中かどうかを表します。*/
        bool Application::running = true;

        /** 指定したフレームを追加します。*/
        void Application::add(Frame* frame) {
            if (frames == NULL) {
                frames = new ArrayList();
            }
            frames->add(frame);
        }

        /** プラットフォームネイティブなイベントを処理します。*/
        void Application::doEvent(bool busy) {
#ifdef BAYOS
            MSG_INFO info;
            if (bayos_msg_receive(&info)) {
                /* メッセージを受けるフレームを検索 */
                Frame* frame = get(info.arg1);

                /* メッセージの振り分け */
                switch(info.type) {
                case MSG_WINDOW_CLOSE:
                    /* TODO dispathEvent(WindowEvent) */
                    //printf("MSG_WINDOW_CLOSE %x\n", info.arg1);
                    /* ウィンドウを閉じる */
                    api_closewin(info.arg1);
                    remove(frame);
                    /* アプリケーション終了 */
                    if (frames->size() == 0) {
                        running = false;
                        api_end();
                    }
                    break;
                case MSG_MOUSE_PRESSED:
                case MSG_MOUSE_RELEASED:
                case MSG_MOUSE_DRAGGED:
                case MSG_MOUSE_MOVED:
                    {
                        //printf("MOUSE_EVENT %x, %d, %d, %d\n", info.arg1, info.arg2, info.arg3, info.arg4);
                        MouseEvent* me = new MouseEvent(
                            frame, /* source */
                            info.type + 201, /* type */
                            info.arg2, /* modifiers */
                            info.arg3, /* x */
                            info.arg4  /* y */
                        );
                        frame->dispatchEvent(me);
                        delete(me);
                        break;
                    }
                case MSG_KEY_PRESSED:
                case MSG_KEY_RELEASED:
                    {
                        //printf("KEY_EVENT   %x, %d, %d, %d\n", info.arg1, info.arg2, info.arg3, info.arg4);
                        KeyEvent* ke = new KeyEvent(
                            frame, /* source */
                            info.type + 95, /* type */
                            info.arg2, /* modifiers */
                            info.arg3, /* keyCode */
                            info.arg4  /* keyCjar */
                        );
                        frame->dispatchEvent(ke);
                        delete(ke);
                        break;
                    }
                default:
                    break;
                }
            } else {
                if (!busy) bayos_thread_yield();
            }
#endif
        }

        /** 指定したハンドルを持つフレームを返します。ない場合は NULL になります。*/
        Frame* Application::get(unsigned int handle) {
            for (int i = 0; i < frames->size(); i++) {
                Frame* frame = (Frame *) frames->get(i);
                if (frame->handle = handle) {
                    return frame;
                }
            }
            return NULL;
        }

        /** 指定したフレームを削除します。*/
        void Application::remove(Frame* frame) {
            frames->remove(frames->indexOf(frame));
        }

        /** アプリケーションの実行を開始します。*/
        void Application::run(Frame* main) {
            main->repaint();
            while (running) {
                doEvent(false);
            }
        }
    }
}
