#if !defined(_BAYGUI_AWT_CONTAINER_H_INCLUDED_)
#define _BAYGUI_AWT_CONTAINER_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * ��ʓI�� �R���e�i�I�u�W�F�N�g�́A
         * �ق��̃R���|�[�l���g���܂ނ��Ƃ��ł���R���|�[�l���g�ł��B
        */
        class Container : public Component {
        protected:
            /** ���̃R���e�i�̎q�ꗗ�ł��B*/
            ArrayList* components;

        public:
            /** �V�����R���e�i���\�z���܂��B*/
            Container();

            /** �f�X�g���N�^�ł��B*/
            virtual ~Container();

            /** �w�肳�ꂽ�R���|�[�l���g�����̃R���e�i�̍Ō�ɒǉ����܂��B*/
            virtual Component* add(Component* c);

            /**
             * ���̃R���|�[�l���g�܂��͂��̃T�u�R���|�[�l���g�� 1 ��
             * �C�x���g���f�B�X�p�b�`���܂��B
            */
            virtual void dispatchEvent(AWTEvent* e);

            /**
             * ���̃R���|�[�l���g�܂��͂��̒��ڂ̃T�u�R���|�[�l���g��
             * �ʒu (x, y) ���܂�ł��邩�ǂ����𔻒肵�܂��B
            */
            virtual Component* getComponentAt(int x, int y);

            /** �R���e�i���̂��ׂẴR���|�[�l���g��Ԃ��܂��B*/
            ArrayList* getComponents();

            /** �R���e�i����A�w�肳�ꂽ�R���|�[�l���g���폜���܂��B*/
            virtual void remove(Component* c);

            /**
             * �R���e�i���ĕ`�悵�܂��B
             * ���̃��\�b�h�́A���̃R���e�i�̎q�ł���y�ʃR���|�[�l���g�ɍX�V�v����]�����܂��B
             * ���̃��\�b�h���Ď������ꂽ�ꍇ�AContainer::update(g) ���Ăяo���Čy�ʃR���|�[�l���g��
             * �K�؂ɕ`�悳���悤�ɂ���K�v������܂��B
            */
            virtual void update(Graphics* g, int x = 0, int y = 0, int w = 0, int h = 0);
        };
    }
}

#endif
