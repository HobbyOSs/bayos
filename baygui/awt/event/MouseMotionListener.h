#if !defined(_BAYGUI_AWT_EVENT_MOUSEMOTIONLISTENER_H_INCLUDED_)
#define _BAYGUI_AWT_EVENT_MOUSEMOTIONLISTENER_H_INCLUDED_

namespace baygui {
    namespace awt {
        namespace event {
            /** �R���|�[�l���g��̃}�E�X���[�V�����C�x���g���󂯎�邽�߂̃��X�i�[�C���^�t�F�[�X�ł��B�N���b�N����т��̑��̃C�x���g�ɂ́AMouseListener ���g�p���܂��B*/
            class MouseMotionListener {
            public:
                /** �R���|�[�l���g��Ń}�E�X�̃{�^���������ꂽ���ƃh���b�O���ꂽ�Ƃ��ɌĂяo����܂��B*/
                virtual void mouseDragged(MouseEvent* e) {};
                /** �R���|�[�l���g��Ń}�E�X���ړ������ (�{�^���͉�����Ȃ�) �ƌĂяo����܂��B*/
                virtual void mouseMoved(MouseEvent* e) {};
            };
        }
    }
}

#endif
