#include "../../../baygui.h"

namespace baygui {
    namespace awt {
        namespace event {
            /** �f�t�H���g�R���X�g���N�^�ł��B*/
            KeyEvent::KeyEvent() {
                addClassName(baygui_awt_event_KeyEvent);
                this->consumed = false;
                this->id = 0;
                this->source = NULL;
                this->keyChar = 0;
                this->keyCode = 0;
                this->modifiers = 0;
            }

            /** �w�肳�ꂽ�\�[�X�I�u�W�F�N�g�ƌ^���g�p���āAKeyEvent �I�u�W�F�N�g���\�z���܂��B*/
            KeyEvent::KeyEvent(Object* source, int id, int modifiers, int keyCode, char keyChar) {
                addClassName(baygui_awt_event_KeyEvent);
                this->consumed = false;
                this->id = id;
                this->source = source;
                this->keyChar = keyChar;
                this->keyCode = keyCode;
                this->modifiers = modifiers;
            }

            /** ���̃C�x���g�̃L�[�Ɋ֘A����������Ԃ��܂��B*/
            char KeyEvent::getKeyChar() {
                return this->keyChar;
            }

            /** ���̃C�x���g�̃L�[�Ɋ֘A���������^�̃L�[�R�[�h��Ԃ��܂��B*/
            int KeyEvent::getKeyCode() {
                return this->keyCode;
            }

            /** ���̃C�x���g�̃L�[�Ɋ֘A���������^�̏C���q��Ԃ��܂��B*/
            int KeyEvent::getModifiers() {
                return this->modifiers;
            }
        }
    }
}
