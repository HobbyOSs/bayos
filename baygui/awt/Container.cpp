#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** �V�����R���e�i���\�z���܂��B*/
        Container::Container() {
            addClassName(baygui_awt_Container);
            this->components = new ArrayList();
        }

        /** �f�X�g���N�^�ł��B*/
        Container::~Container() {
            delete this->components;
        }

        /** �w�肳�ꂽ�R���|�[�l���g�����̃R���e�i�̍Ō�ɒǉ����܂��B*/
        Component* Container::add(Component* c) {
            c->setParent(this);
            this->components->add(c);
            return c;
        }

        /**
         * ���̃R���|�[�l���g�܂��͂��̃T�u�R���|�[�l���g�� 1 ��
         * �C�x���g���f�B�X�p�b�`���܂��B
        */
        void Container::dispatchEvent(AWTEvent* e) {
            Component::dispatchEvent(e);
            int I = this->components->size();
            for (int i = I - 1; i >= 0; i--) {
                Component* c = (Component*) this->components->get(i);
                c->dispatchEvent(e);
            }
        }

        /**
         * ���̃R���|�[�l���g�܂��͂��̒��ڂ̃T�u�R���|�[�l���g��
         * �ʒu (x, y) ���܂�ł��邩�ǂ����𔻒肵�܂��B
        */
        Component* Container::getComponentAt(int x, int y) {
            int I = this->components->size();
            for (int i = I - 1; i >= 0; i--) {
                Component* p = (Component*) this->components->get(i);
                Component* c = p->getComponentAt(x - p->getX(), y - p->getY());
                if (c != NULL) {
                    return c;
                }
            }
            return Component::getComponentAt(x, y);
        }

        /** �R���e�i���̂��ׂẴR���|�[�l���g��Ԃ��܂��B*/
        ArrayList* Container::getComponents() {
            return this->components;
        }

        /** �R���e�i����A�w�肳�ꂽ�R���|�[�l���g���폜���܂��B*/
        void Container::remove(Component* c) {
            this->components->remove(this->components->indexOf(c));
        }

        /**
         * �R���e�i���ĕ`�悵�܂��B
         * ���̃��\�b�h�́A���̃R���e�i�̎q�ł���y�ʃR���|�[�l���g�ɍX�V�v����]�����܂��B
         * ���̃��\�b�h���Ď������ꂽ�ꍇ�AContainer::update(g) ���Ăяo���Čy�ʃR���|�[�l���g��
         * �K�؂ɕ`�悳���悤�ɂ���K�v������܂��B
        */
        void Container::update(Graphics* g, int x, int y, int w, int h) {
            paint(g);
            int I = this->components->size();
            for (int i = 0; i < I; i++) {
                Component* c = (Component*) this->components->get(i);
                c->paint(c->getGraphics());
            }
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
