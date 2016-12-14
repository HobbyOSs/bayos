#if !defined(_BAYGUI_AWT_EVENT_MOUSELISTENER_H_INCLUDED_)
#define _BAYGUI_AWT_EVENT_MOUSELISTENER_H_INCLUDED_

namespace baygui {
    namespace awt {
        namespace event {
            /**
             * �R���|�[�l���g��́u�֘A����v�}�E�X�C�x���g
             * (�v���X�A�����[�X�A�N���b�N�A�R���|�[�l���g�ւ̏o����) 
             * ���󂯎�邽�߂̃��X�i�[�C���^�t�F�[�X�ł��B
             * �}�E�X�̈ړ�����уh���b�O��ǐՂ���ɂ́AMouseMotionListener ���g�p���܂��B
            */
            class MouseListener {
            public:
                /** �R���|�[�l���g�Ƀ}�E�X������ƌĂяo����܂��B*/
                virtual void mouseEntered(MouseEvent* e) {};
                /** �R���|�[�l���g����}�E�X���o��ƌĂяo����܂��B*/
                virtual void mouseExited(MouseEvent* e) {};
                /** �R���|�[�l���g��Ń}�E�X�{�^�����������ƌĂяo����܂��B*/
                virtual void mousePressed(MouseEvent* e) {};
                /** �R���|�[�l���g��Ń}�E�X�{�^�����������ƌĂяo����܂��B*/
                virtual void mouseReleased(MouseEvent* e) {};
            };
        }
    }
}

#endif
