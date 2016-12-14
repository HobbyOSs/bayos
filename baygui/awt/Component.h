#if !defined(_BAYGUI_AWT_COMPONENT_H_INCLUDED_)
#define _BAYGUI_AWT_COMPONENT_H_INCLUDED_

using namespace baygui::lang;
using namespace baygui::util;
using namespace baygui::awt::event;

namespace baygui {
    namespace awt {
        class Container;

        /** �u�R���|�[�l���g�v�́A��ʂɕ\���ł��A���[�U�ƑΘb�ł���O���t�B�J���ȕ\�������I�u�W�F�N�g�ł��B*/
        class Component : public Object {
        protected:
            /** �g�b�v���x���E�B���h�E�̍��[����̈ʒu�ł��B*/
            int tx;
            /** �g�b�v���x���E�B���h�E�̍��[����̈ʒu�ł��B*/
            int ty;
            /** ���̃R���|�[�l���g�̔w�i�F�ł��B*/
            unsigned int background;
            /** ���̃R���|�[�l���g�̑O�i�F�ł��B*/
            unsigned int foreground;
            /** ���̃R���|�[�l���g�Ƀt�H�[�J�X�����邩�ǂ���������킵�܂��B*/
            bool focused;
            /** ���̃R���|�[�l���g���g�p�\���ǂ���������킵�܂��B*/
            bool enabled;
            /** ���̃R���|�[�l���g�Ƀ}�E�X�����������ǂ���������킵�܂��B*/
            bool mouseEntered;
            /** ���̃R���|�[�l���g�� Rectangle �ł��B*/
            Rectangle* rectangle;
            /** ���̃R���|�[�l���g�̃O���t�B�b�N�R���e�L�X�g�ł��B*/
            Graphics* graphics;
            /** ���̃R���|�[�l���g�̐e�R���|�[�l���g�ł��B*/
            Container* parent;
            /** �L�[�C�x���g�p���X�i�[���X�g�ł��B*/
            ArrayList* keyListeners;
            /** �}�E�X�C�x���g�p���X�i�[���X�g�ł��B*/
            ArrayList* mouseListeners;
            /** �}�E�X���[�V�����C�x���g�p���X�i�[���X�g�ł��B*/
            ArrayList* mouseMotionListeners;

        public:
            /** �R���|�[�l���g��V�����\�z���܂��B*/
            Component();

            /** �f�X�g���N�^�ł��B*/
            virtual ~Component();

            /**
             * ���̃R���|�[�l���g����L�[�C�x���g���󂯎�邽�߂ɁA
             * �w�肳�ꂽ�L�[���X�i�[��ǉ����܂��B
            */
            void addKeyListener(KeyListener* l);

            /**
             * ���̃R���|�[�l���g����}�E�X�C�x���g���󂯎�邽�߂ɁA
             * �w�肳�ꂽ�}�E�X���X�i�[��ǉ����܂��B
            */
            void addMouseListener(MouseListener* l);

            /**
             * ���̃R���|�[�l���g����}�E�X���[�V�����C�x���g���󂯎�邽�߂ɁA
             * �w�肳�ꂽ�}�E�X���[�V�������X�i�[��ǉ����܂��B
            */
            void addMouseMotionListener(MouseMotionListener* l);

            /** ���̃R���|�[�l���g�܂��͂��̃T�u�R���|�[�l���g�� 1 �ɃC�x���g���f�B�X�p�b�`���܂��B*/
            virtual void dispatchEvent(AWTEvent* e);

            /** ���̃R���|�[�l���g�̃o�b�N�O���E���h�J���[��Ԃ��܂��B*/
            unsigned int getBackground();

            /** ���̃R���|�[�l���g�̋��E�� Rectangle �I�u�W�F�N�g�Ƃ��ĕԂ��܂��B*/
            Rectangle* getBounds();

            /**
             * ���̃R���|�[�l���g�܂��͂��̒��ڂ̃T�u�R���|�[�l���g���ʒu (x, y) 
             * ���܂�ł��邩�ǂ����𔻒肵�܂��B
            */
            virtual Component* getComponentAt(int x, int y);

            /** ���̃R���|�[�l���g�̃t�H�A�O���E���h�J���[��Ԃ��܂��B*/
            unsigned int getForeground();

            /** ���̃R���|�[�l���g�̃O���t�B�b�N�X�R���e�L�X�g���쐬���܂��B*/
            virtual Graphics* getGraphics();

            /** ���̃R���|�[�l���g�̃T�C�Y��Ԃ��܂��B*/
            int getHeight();

            /** ���� Component ���L�[�{�[�h�t�H�[�J�X�����ꍇ�� true ��Ԃ��܂��B*/
            bool hasFocus();

            /** ���̃R���|�[�l���g���g�p�\�ł��邩�ǂ����𔻒肵�܂��B*/
            bool isEnabled();

            /** ���̃R���|�[�l���g�̐e��Ԃ��܂��B*/
            Container* getParent();

            /** ���̃R���|�[�l���g�̃T�C�Y��Ԃ��܂��B*/
            int getWidth();

            /** ���̃R���|�[�l���g�̈ʒu���A�R���|�[�l���g�̍�������w�肷��_�Ƃ��ĕԂ��܂��B*/
            int getX();

            /** ���̃R���|�[�l���g�̈ʒu���A�R���|�[�l���g�̍�������w�肷��_�Ƃ��ĕԂ��܂��B*/
            int getY();

            /** ���̃R���|�[�l���g���y�C���g���܂��B*/
            virtual void paint(Graphics* g);

        protected:
            /** ���̃R���|�[�l���g�Ŕ�������R���|�[�l���g�C�x���g���������܂��B*/
            virtual void processEvent(AWTEvent* e);

            /**
             * ���̃R���|�[�l���g�Ŕ�������L�[�C�x���g���A
             * �o�^����Ă��邷�ׂĂ� KeyListener �I�u�W�F�N�g�ɑ��邱�Ƃɂ��A
             * �L�[�C�x���g���������܂��B
            */
            virtual void processKeyEvent(KeyEvent* e);

            /**
             * ���̃R���|�[�l���g�Ŕ�������}�E�X�C�x���g���A
             * �o�^����Ă��邷�ׂĂ� MouseListener �I�u�W�F�N�g�ɑ��邱�Ƃɂ��A
             * �}�E�X�C�x���g���������܂��B
            */
            virtual void processMouseEvent(MouseEvent* e);

            /**
             * ���̃R���|�[�l���g�Ŕ�������}�E�X���[�V�����C�x���g���A
             * �o�^����Ă��邷�ׂĂ� MouseMotionListener �I�u�W�F�N�g�ɑ��邱�Ƃɂ��A
             * �}�E�X���[�V�����C�x���g���������܂��B
            */
            virtual void processMouseMotionEvent(MouseEvent* e);

        public:
            /**
             * ���̃R���|�[�l���g����L�[�C�x���g���󂯎��Ȃ��悤�ɁA
             * �w�肳�ꂽ�L�[���X�i�[���폜���܂��B
            */
            void removeKeyListener(KeyListener* l);

            /**
             * ���̃R���|�[�l���g����}�E�X�C�x���g���󂯎��Ȃ��悤�ɁA
             * �w�肳�ꂽ�}�E�X���X�i�[���폜���܂��B
            */
            void removeMouseListener(MouseListener* l);

            /**
             * ���̃R���|�[�l���g����}�E�X���[�V�����C�x���g���󂯎��Ȃ��悤�ɁA
             * �w�肳�ꂽ�}�E�X���[�V�������X�i�[���폜���܂��B
            */
            void removeMouseListener(MouseMotionListener* l);

            /** ���̃R���|�[�l���g���ĕ`�悵�܂��B*/
            virtual void repaint(int x = 0, int y = 0, int w = 0, int h = 0);

            /** ���̃R���|�[�l���g�����̓t�H�[�J�X���擾���邱�Ƃ�v�����܂��B*/
            virtual void requestFocus();

            /** ���̃R���|�[�l���g�̃o�b�N�O���E���h�J���[��ݒ肵�܂��B*/
            void setBackground(unsigned int c);

            /** ���̃R���|�[�l���g���ړ����A�T�C�Y�ύX���܂��B*/
            virtual void setBounds(int x, int y, int width, int height);

            /** ���̃R���|�[�l���g�̃t�H�A�O���E���h�J���[��ݒ肵�܂��B*/
            void setForeground(unsigned int c);

            /** ���̃R���|�[�l���g�̐e�R���|�[�l���g���w�肵�܂��B*/
            virtual void setParent(Container* parent);

            /** ���̃R���|�[�l���g�Ƀt�H�[�J�X���ړ����܂��B*/
            virtual void transferFocus();

            /** ���̃R���|�[�l���g���X�V���܂��B*/
            virtual void update(Graphics* g, int x = 0, int y = 0, int w = 0, int h = 0);
        };
    }
}

#endif
