#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** 新しいコンテナを構築します。*/
        Container::Container() {
            addClassName(baygui_awt_Container);
            this->components = new ArrayList();
        }

        /** デストラクタです。*/
        Container::~Container() {
            delete this->components;
        }

        /** 指定されたコンポーネントをこのコンテナの最後に追加します。*/
        Component* Container::add(Component* c) {
            c->setParent(this);
            this->components->add(c);
            return c;
        }

        /**
         * このコンポーネントまたはそのサブコンポーネントの 1 つに
         * イベントをディスパッチします。
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
         * このコンポーネントまたはその直接のサブコンポーネントが
         * 位置 (x, y) を含んでいるかどうかを判定します。
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

        /** コンテナ内のすべてのコンポーネントを返します。*/
        ArrayList* Container::getComponents() {
            return this->components;
        }

        /** コンテナから、指定されたコンポーネントを削除します。*/
        void Container::remove(Component* c) {
            this->components->remove(this->components->indexOf(c));
        }

        /**
         * コンテナを再描画します。
         * このメソッドは、このコンテナの子である軽量コンポーネントに更新要求を転送します。
         * このメソッドが再実装された場合、Container::update(g) を呼び出して軽量コンポーネントが
         * 適切に描画されるようにする必要があります。
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
