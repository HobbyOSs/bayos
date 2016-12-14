#if !defined(_BAYGUI_AWT_EVENT_KEYEVENT_H_INCLUDED_)
#define _BAYGUI_AWT_EVENT_KEYEVENT_H_INCLUDED_

using namespace baygui::lang;
using namespace baygui::awt;

namespace baygui {
    namespace awt {
        namespace event {
            /** ���̃C�x���g�́A�R���|�[�l���g�ɂ����ăL�[�X�g���[�N�������������Ƃ������܂��B*/
            class KeyEvent : public AWTEvent {
            public:
                enum {
                    /** �u�L�[�v���X�v�C�x���g�ł��B*/
                    KEY_PRESSED  = 100,
                    /** �u�L�[�����[�X�v�C�x���g�ł��B*/
                    KEY_RELEASED = 101
                };

            private:
                /** �����ł��B*/
                int keyChar;
                /** �L�[�R�[�h�ł��B*/
                int keyCode;
                /** �C���q�ł��B*/
                int modifiers;

            public:
                /** �f�t�H���g�R���X�g���N�^�ł��B*/
                KeyEvent();

                /** �w�肳�ꂽ�\�[�X�I�u�W�F�N�g�ƌ^���g�p���āAKeyEvent �I�u�W�F�N�g���\�z���܂��B*/
                KeyEvent(Object* source, int id, int modifiers, int keyCode, char keyChar);

                /** ���̃C�x���g�̃L�[�Ɋ֘A����������Ԃ��܂��B*/
                char getKeyChar();

                /** ���̃C�x���g�̃L�[�Ɋ֘A���������^�̃L�[�R�[�h��Ԃ��܂��B*/
                int getKeyCode();

                /** ���̃C�x���g�̃L�[�Ɋ֘A���������^�̏C���q��Ԃ��܂��B*/
                int getModifiers();
            };
        }
    }
}

#endif
