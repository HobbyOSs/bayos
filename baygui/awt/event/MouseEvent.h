#if !defined(_BAYGUI_AWT_EVENT_MOUSEEVENT_H_INCLUDED_)
#define _BAYGUI_AWT_EVENT_MOUSEEVENT_H_INCLUDED_

using namespace baygui::lang;
using namespace baygui::awt;

namespace baygui {
    namespace awt {
        namespace event {
            /** �R���|�[�l���g���Ń}�E�X�A�N�V�����������������Ƃ������C�x���g�ł��B*/
            class MouseEvent : public AWTEvent {
            public:
                enum {
                    /**�u�}�E�X�G���^�[�v�C�x���g�ł��B*/
                    MOUSE_ENTERED  = 200,
                    /**�u�}�E�X�C�O�W�b�g�v�C�x���g�ł��B*/
                    MOUSE_EXITED   = 201,
                    /**�u�}�E�X�v���X�v�C�x���g�ł��B*/
                    MOUSE_PRESSED  = 202,
                    /**�u�}�E�X�����[�X�v�C�x���g�ł��B*/
                    MOUSE_RELEASED = 203,
                    /**�u�}�E�X�h���b�O�v�C�x���g�ł��B*/
                    MOUSE_DRAGGED  = 204,
                    /**�u�}�E�X���[�u�v�C�x���g�ł��B*/
                    MOUSE_MOVED    = 205
                };

            private:
                /** �C�x���g�����������ʒu�� X ���W�ł��B*/
                int x;
                /** �C�x���g�����������ʒu�� Y ���W�ł��B*/
                int y;
                /** ���̃C�x���g�Ɋ֘A�����{�^���̎�ނł��B*/
                int modifiers;

            public:
                /** �f�t�H���g�R���X�g���N�^�ł��B*/
                MouseEvent();

                /** �w�肳�ꂽ�\�[�X�I�u�W�F�N�g�ƌ^���g�p���āAMouseEvent �I�u�W�F�N�g���\�z���܂��B*/
                MouseEvent(Object* source, int id, int modifiers, int x, int y);

                /** ���̃C�x���g�Ɋ֘A�����{�^���̎�ނ�Ԃ��܂��B*/
                int getModifiers();

                /** �C�x���g�����������ʒu�� X ���W�𔭐����̃R���|�[�l���g�ɑ΂��鑊�Έʒu�ŕԂ��܂��B*/
                int getX();

                /** �C�x���g�����������ʒu�� Y ���W�𔭐����̃R���|�[�l���g�ɑ΂��鑊�Έʒu�ŕԂ��܂��B*/
                int getY();
            };
        }
    }
}

#endif
