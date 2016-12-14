#if !defined(_BAYGUI_AWT_AWTEVENT_H_INCLUDED_)
#define _BAYGUI_AWT_AWTEVENT_H_INCLUDED_

using namespace baygui::lang;

namespace baygui {
    namespace awt {
        /** ���ׂĂ� AWT �C�x���g�p�̃��[�g�C�x���g�N���X�ł��B*/
        class AWTEvent : public Object {
        protected:
            /** �C�x���g������ꂽ���ǂ����������t���O�ł��B*/
            bool consumed;
            /** �C�x���g�̌^�������l�ł��B*/
            int id;
            /** Event ���ŏ��ɔ��������I�u�W�F�N�g�ł��B*/
            Object* source;

        public:
            /** �f�t�H���g�R���X�g���N�^�ł��B*/
            AWTEvent();

            /** �C�x���g������܂��B*/
            void consume();

            /* �C�x���g�̌^��Ԃ��܂��B*/
            int getID();

            /** Event ���ŏ��ɔ��������I�u�W�F�N�g�ł��B*/
            Object* getSource();

            /** �C�x���g������ꂽ���ǂ�����Ԃ��܂��B*/
            bool isConsumed();
        };
    }
}

#endif
