#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** �R���|�[�l���g��V�����\�z���܂��B*/
        Component::Component() {
            addClassName(baygui_awt_Component);
            this->tx = 0;
            this->ty = 0;
            this->background = Color::lightGray;
            this->foreground = Color::black;
            this->rectangle = new Rectangle();
            this->graphics = new Graphics();
            this->focused = false;
            this->enabled = true;
            this->mouseEntered = false;
            this->parent = NULL;
            this->keyListeners = new ArrayList();
            this->mouseListeners = new ArrayList();
            this->mouseMotionListeners = new ArrayList();
        }

        /** �f�X�g���N�^�ł��B*/
        Component::~Component() {
            delete this->rectangle;
            delete this->graphics;
            delete this->keyListeners;
            delete this->mouseListeners;
            delete this->mouseMotionListeners;
        }

        /**
         * ���̃R���|�[�l���g����L�[�C�x���g���󂯎�邽�߂ɁA
         * �w�肳�ꂽ�L�[���X�i�[��ǉ����܂��B
        */
        void Component::addKeyListener(KeyListener* l) {
            this->keyListeners->add((Object*) l);
        }

        /**
         * ���̃R���|�[�l���g����}�E�X�C�x���g���󂯎�邽�߂ɁA
         * �w�肳�ꂽ�}�E�X���X�i�[��ǉ����܂��B
        */
        void Component::addMouseListener(MouseListener* l) {
            this->mouseListeners->add((Object*) l);
        }

        /**
         * ���̃R���|�[�l���g����}�E�X���[�V�����C�x���g���󂯎�邽�߂ɁA
         * �w�肳�ꂽ�}�E�X���[�V�������X�i�[��ǉ����܂��B
        */
        void Component::addMouseMotionListener(MouseMotionListener* l) {
            this->mouseMotionListeners->add((Object*) l);
        }

        /** ���̃R���|�[�l���g�܂��͂��̃T�u�R���|�[�l���g�� 1 �ɃC�x���g���f�B�X�p�b�`���܂��B*/
        void Component::dispatchEvent(AWTEvent* e) {
            processEvent(e);
        }

        /** ���̃R���|�[�l���g�̃o�b�N�O���E���h�J���[��Ԃ��܂��B*/
        unsigned int Component::getBackground() {
            return this->background;
        }

        /** ���̃R���|�[�l���g�̋��E�� Rectangle �I�u�W�F�N�g�Ƃ��ĕԂ��܂��B*/
        Rectangle* Component::getBounds() {
            return this->rectangle;
        }

        /**
         * ���̃R���|�[�l���g�܂��͂��̒��ڂ̃T�u�R���|�[�l���g���ʒu (x, y) 
         * ���܂�ł��邩�ǂ����𔻒肵�܂��B
        */
        Component* Component::getComponentAt(int x, int y) {
            return (getX() < x && x < getX() + getWidth() &&
                    getY() < y && y < getY() + getHeight())
                   ? this : NULL;
        }

        /** ���̃R���|�[�l���g�̃t�H�A�O���E���h�J���[��Ԃ��܂��B*/
        unsigned int Component::getForeground() {
            return this->foreground;
        }

        /** ���̃R���|�[�l���g�̃O���t�B�b�N�X�R���e�L�X�g���쐬���܂��B*/
        Graphics* Component::getGraphics() {
            if (this->graphics->frame == NULL) {
                /* ���̃R���|�[�l���g�̐�Έʒu���v�Z */
                this->tx = getX();
                this->ty = getY();
                Component* c = this;
                while (1) {
                    if (c->getParent() == NULL) {
                        /* �A�v���P�[�V�����t���[����ݒ肵�A��Έʒu��ݒ� */
                        this->graphics->frame  = (Frame *) c;
                        this->graphics->buffer = ((Frame *) c)->buffer;
                        this->graphics->translate(this->tx, this->ty);
                        break;
                    } else {
                        c = c->getParent();
                    }
                    this->tx += c->getX();
                    this->ty += c->getY();
                }
            }
            return this->graphics;
        }

        /** ���̃R���|�[�l���g�̃T�C�Y��Ԃ��܂��B*/
        int Component::getHeight() {
            return this->rectangle->height;
        }

        /** ���� Component ���L�[�{�[�h�t�H�[�J�X�����ꍇ�� true ��Ԃ��܂��B*/
        bool Component::hasFocus() {
            return this->focused;
        }

        /** ���̃R���|�[�l���g���g�p�\�ł��邩�ǂ����𔻒肵�܂��B*/
        bool Component::isEnabled() {
            return this->enabled;
        }

        /** ���̃R���|�[�l���g�̐e��Ԃ��܂��B*/
        Container* Component::getParent() {
            return this->parent;
        }

        /** ���̃R���|�[�l���g�̃T�C�Y��Ԃ��܂��B*/
        int Component::getWidth() {
            return this->rectangle->width;
        }

        /** ���̃R���|�[�l���g�̈ʒu���A�R���|�[�l���g�̍�������w�肷��_�Ƃ��ĕԂ��܂��B*/
        int Component::getX() {
            return this->rectangle->x;
        }

        /** ���̃R���|�[�l���g�̈ʒu���A�R���|�[�l���g�̍�������w�肷��_�Ƃ��ĕԂ��܂��B*/
        int Component::getY() {
            return this->rectangle->y;
        }

        /** ���̃R���|�[�l���g���y�C���g���܂��B*/
        void Component::paint(Graphics* g) {
            if (getWidth() == 0 || getHeight() == 0) return;
        }

        /** ���̃R���|�[�l���g�Ŕ�������R���|�[�l���g�C�x���g���������܂��B*/
        void Component::processEvent(AWTEvent* e) {
            /* �񊈐��̂Ƃ��̓C�x���g���󂯕t���Ȃ��B*/
            if (isEnabled() == false) return;

            switch (e->getID()) {
            case MouseEvent::MOUSE_DRAGGED:
            case MouseEvent::MOUSE_MOVED:
            {
                int mouse_x = ((MouseEvent*) e)->getX() - this->tx;
                int mouse_y = ((MouseEvent*) e)->getY() - this->ty;
                int mouse_m = ((MouseEvent*) e)->getModifiers();

                if (Component::getComponentAt(mouse_x + getX(), mouse_y + getY()) == this) {
                    /* �}�E�X�������� */
                    if (this->mouseEntered == false) {
                        this->mouseEntered = true;
                        MouseEvent* me = new MouseEvent(
                            e->getSource(),
                            MouseEvent::MOUSE_ENTERED,
                            mouse_m,
                            mouse_x,
                            mouse_y
                        );
                        processMouseEvent(me);
                        delete(me);
                    /* �}�E�X�������� */
                    } else {
                        MouseEvent* me = new MouseEvent(
                            e->getSource(),
                            e->getID(),
                            mouse_m,
                            mouse_x,
                            mouse_y
                        );
                        processMouseMotionEvent(me);
                        delete(me);
                    }
                } else {
                    /* �}�E�X���o�� */
                    if (this->mouseEntered == true) {
                        this->mouseEntered = false;
                        MouseEvent* me = new MouseEvent(
                            e->getSource(),
                            MouseEvent::MOUSE_EXITED,
                            mouse_m,
                            mouse_x,
                            mouse_y
                        );
                        processMouseEvent(me);
                        delete(me);
                    }
                }
                break;
            }
            case MouseEvent::MOUSE_PRESSED:
            case MouseEvent::MOUSE_RELEASED:
            {
                int mouse_x = ((MouseEvent*) e)->getX() - this->tx;
                int mouse_y = ((MouseEvent*) e)->getY() - this->ty;
                int mouse_m = ((MouseEvent*) e)->getModifiers();

                if (Component::getComponentAt(mouse_x + getX(), mouse_y + getY()) == this) {
                    MouseEvent* me = new MouseEvent(
                        e->getSource(),
                        e->getID(),
                        mouse_m,
                        mouse_x,
                        mouse_y
                    );
                    processMouseEvent(me);
                    delete(me);
                }
                break;
            }
            case KeyEvent::KEY_PRESSED:
            case KeyEvent::KEY_RELEASED:
                processKeyEvent((KeyEvent*) e);
                break;
            default:
                break;
            }
        }

        /**
         * ���̃R���|�[�l���g�Ŕ�������L�[�C�x���g���A
         * �o�^����Ă��邷�ׂĂ� KeyListener �I�u�W�F�N�g�ɑ��邱�Ƃɂ��A
         * �L�[�C�x���g���������܂��B
        */
        void Component::processKeyEvent(KeyEvent* e) {
            int I = this->keyListeners->size();
            for (int i = I - 1; i >= 0; i--) {
                KeyListener* l = (KeyListener*) this->keyListeners->get(i);
                switch (e->getID()) {
                case KeyEvent::KEY_PRESSED:
                    l->keyPressed(e);
                    break;
                case KeyEvent::KEY_RELEASED:
                    l->keyReleased(e);
                    break;
                }
            }
        }

        /**
         * ���̃R���|�[�l���g�Ŕ�������}�E�X�C�x���g���A
         * �o�^����Ă��邷�ׂĂ� MouseListener �I�u�W�F�N�g�ɑ��邱�Ƃɂ��A
         * �}�E�X�C�x���g���������܂��B
        */
        void Component::processMouseEvent(MouseEvent* e) {
            int I = this->mouseListeners->size();
            for (int i = I - 1; i >= 0; i--) {
                MouseListener* l = (MouseListener*) this->mouseListeners->get(i);
                switch (e->getID()) {
                case MouseEvent::MOUSE_ENTERED:
                    l->mouseEntered(e);
                    break;
                case MouseEvent::MOUSE_EXITED:
                    l->mouseExited(e);
                    break;
                case MouseEvent::MOUSE_PRESSED:
                    l->mousePressed(e);
                    break;
                case MouseEvent::MOUSE_RELEASED:
                    l->mouseReleased(e);
                    break;
                }
            }
            /* �t�H�[�J�X���������� */
            if (this->focused == false && e->getID() == MouseEvent::MOUSE_PRESSED) {
                requestFocus();
            }
        }

        /**
         * ���̃R���|�[�l���g�Ŕ�������}�E�X���[�V�����C�x���g���A
         * �o�^����Ă��邷�ׂĂ� MouseMotionListener �I�u�W�F�N�g�ɑ��邱�Ƃɂ��A
         * �}�E�X���[�V�����C�x���g���������܂��B
        */
        void Component::processMouseMotionEvent(MouseEvent* e) {
            int I = this->mouseMotionListeners->size();
            for (int i = I - 1; i >= 0; i--) {
                MouseMotionListener* l = (MouseMotionListener*) this->mouseMotionListeners->get(i);
                switch (e->getID()) {
                case MouseEvent::MOUSE_DRAGGED:
                    l->mouseDragged(e);
                    break;
                case MouseEvent::MOUSE_MOVED:
                    l->mouseMoved(e);
                    break;
                }
            }
        }

        /**
         * ���̃R���|�[�l���g����L�[�C�x���g���󂯎��Ȃ��悤�ɁA
         * �w�肳�ꂽ�L�[���X�i�[���폜���܂��B
        */
        void Component::removeKeyListener(KeyListener* l) {
            this->keyListeners->remove(this->keyListeners->indexOf((Object*) l));
        }

        /**
         * ���̃R���|�[�l���g����}�E�X�C�x���g���󂯎��Ȃ��悤�ɁA
         * �w�肳�ꂽ�}�E�X���X�i�[���폜���܂��B
        */
        void Component::removeMouseListener(MouseListener* l) {
            this->mouseListeners->remove(this->mouseListeners->indexOf((Object*) l));
        }

        /**
         * ���̃R���|�[�l���g����}�E�X���[�V�����C�x���g���󂯎��Ȃ��悤�ɁA
         * �w�肳�ꂽ�}�E�X���[�V�������X�i�[���폜���܂��B
        */
        void Component::removeMouseListener(MouseMotionListener* l) {
            this->mouseListeners->remove(this->mouseListeners->indexOf((Object*) l));
        }

        /** ���̃R���|�[�l���g���ĕ`�悵�܂��B*/
        void Component::repaint(int x, int y, int width, int height) {
            update(getGraphics(), x, y, width, height);
        }

        /** ���̃R���|�[�l���g�����̓t�H�[�J�X���擾���邱�Ƃ�v�����܂��B*/
        void Component::requestFocus() {
            this->focused = true;
            if (this->graphics->frame->active != NULL) {
                this->graphics->frame->active->transferFocus();
            }
            this->graphics->frame->active = this;
            repaint();
        }

        /** ���̃R���|�[�l���g���ړ����A�T�C�Y�ύX���܂��B*/
        void Component::setBounds(int x, int y, int width, int height) {
            this->rectangle->x = x;
            this->rectangle->y = y;
            this->rectangle->width  = width;
            this->rectangle->height = height;
        }

        /** ���̃R���|�[�l���g�̃o�b�N�O���E���h�J���[��ݒ肵�܂��B*/
        void Component::setBackground(unsigned int c) {
            this->background = c;
        }

        /** ���̃R���|�[�l���g�̐e�R���|�[�l���g���w�肵�܂��B*/
        void Component::setParent(Container* parent) {
            this->parent = parent;
        }

        /** ���̃R���|�[�l���g�̃t�H�A�O���E���h�J���[��ݒ肵�܂��B*/
        void Component::setForeground(unsigned int c) {
            this->foreground = c;
        }

        /** ���̃R���|�[�l���g�Ƀt�H�[�J�X���ړ����܂��B*/
        void Component::transferFocus() {
            this->focused = false;
            repaint();
        }

        /** ���̃R���|�[�l���g���X�V���܂��B*/
        void Component::update(Graphics* g, int x, int y, int w, int h) {
            paint(g);
#ifdef HARIBOTE
            if (w == 0 && h == 0) {
                api_refreshwin(
                    g->frame->handle,
                    this->tx,
                    this->ty,
                    this->tx + getWidth(),
                    this->ty + getHeight()
                );
            } else {
                api_refreshwin(
                    g->frame->handle,
                    this->tx + x,
                    this->ty + y,
                    this->tx + w,
                    this->ty + h
                );
            }
#endif
        }
    }
}
