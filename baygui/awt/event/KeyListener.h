#if !defined(_BAYGUI_AWT_EVENT_KEYLISTENER_H_INCLUDED_)
#define _BAYGUI_AWT_EVENT_KEYLISTENER_H_INCLUDED_

namespace baygui {
    namespace awt {
        namespace event {
            /** ���̃��X�i�[�́A�L�[�{�[�h�C�x���g (�L�[�X�g���[�N) ���󂯎�邽�߂̃C���^�t�F�[�X�ł��B*/
            class KeyListener {
            public:
                /** �L�[�������Ă���Ƃ��ɌĂяo����܂��B*/
                virtual void keyPressed(KeyEvent* e) {};
                /** �L�[�𗣂����Ƃ��ɌĂяo����܂��B*/
                virtual void keyReleased(KeyEvent* e) {};
            };
        }
    }
}

#endif
