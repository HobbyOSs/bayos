#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /* �ÓI�ϐ��̐ݒ� */
        ArrayList* Application::frames = NULL;
        /** �A�v���P�[�V���������s�����ǂ�����\���܂��B*/
        bool Application::running = true;

        /** �w�肵���t���[����ǉ����܂��B*/
        void Application::add(Frame* frame) {
            if (frames == NULL) {
                frames = new ArrayList();
            }
            frames->add(frame);
        }

        /** �v���b�g�t�H�[���l�C�e�B�u�ȃC�x���g���������܂��B*/
        void Application::doEvent(bool busy) {
#ifdef BAYOS
            MSG_INFO info;
            if (bayos_msg_receive(&info)) {
                /* ���b�Z�[�W���󂯂�t���[�������� */
                Frame* frame = get(info.arg1);

                /* ���b�Z�[�W�̐U�蕪�� */
                switch(info.type) {
                case MSG_WINDOW_CLOSE:
                    /* TODO dispathEvent(WindowEvent) */
                    //printf("MSG_WINDOW_CLOSE %x\n", info.arg1);
                    /* �E�B���h�E����� */
                    api_closewin(info.arg1);
                    remove(frame);
                    /* �A�v���P�[�V�����I�� */
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

        /** �w�肵���n���h�������t���[����Ԃ��܂��B�Ȃ��ꍇ�� NULL �ɂȂ�܂��B*/
        Frame* Application::get(unsigned int handle) {
            for (int i = 0; i < frames->size(); i++) {
                Frame* frame = (Frame *) frames->get(i);
                if (frame->handle = handle) {
                    return frame;
                }
            }
            return NULL;
        }

        /** �w�肵���t���[�����폜���܂��B*/
        void Application::remove(Frame* frame) {
            frames->remove(frames->indexOf(frame));
        }

        /** �A�v���P�[�V�����̎��s���J�n���܂��B*/
        void Application::run(Frame* main) {
            main->repaint();
            while (running) {
                doEvent(false);
            }
        }
    }
}
