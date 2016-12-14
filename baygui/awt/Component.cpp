#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** コンポーネントを新しく構築します。*/
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

        /** デストラクタです。*/
        Component::~Component() {
            delete this->rectangle;
            delete this->graphics;
            delete this->keyListeners;
            delete this->mouseListeners;
            delete this->mouseMotionListeners;
        }

        /**
         * このコンポーネントからキーイベントを受け取るために、
         * 指定されたキーリスナーを追加します。
        */
        void Component::addKeyListener(KeyListener* l) {
            this->keyListeners->add((Object*) l);
        }

        /**
         * このコンポーネントからマウスイベントを受け取るために、
         * 指定されたマウスリスナーを追加します。
        */
        void Component::addMouseListener(MouseListener* l) {
            this->mouseListeners->add((Object*) l);
        }

        /**
         * このコンポーネントからマウスモーションイベントを受け取るために、
         * 指定されたマウスモーションリスナーを追加します。
        */
        void Component::addMouseMotionListener(MouseMotionListener* l) {
            this->mouseMotionListeners->add((Object*) l);
        }

        /** このコンポーネントまたはそのサブコンポーネントの 1 つにイベントをディスパッチします。*/
        void Component::dispatchEvent(AWTEvent* e) {
            processEvent(e);
        }

        /** このコンポーネントのバックグラウンドカラーを返します。*/
        unsigned int Component::getBackground() {
            return this->background;
        }

        /** このコンポーネントの境界を Rectangle オブジェクトとして返します。*/
        Rectangle* Component::getBounds() {
            return this->rectangle;
        }

        /**
         * このコンポーネントまたはその直接のサブコンポーネントが位置 (x, y) 
         * を含んでいるかどうかを判定します。
        */
        Component* Component::getComponentAt(int x, int y) {
            return (getX() < x && x < getX() + getWidth() &&
                    getY() < y && y < getY() + getHeight())
                   ? this : NULL;
        }

        /** このコンポーネントのフォアグラウンドカラーを返します。*/
        unsigned int Component::getForeground() {
            return this->foreground;
        }

        /** このコンポーネントのグラフィックスコンテキストを作成します。*/
        Graphics* Component::getGraphics() {
            if (this->graphics->frame == NULL) {
                /* このコンポーネントの絶対位置を計算 */
                this->tx = getX();
                this->ty = getY();
                Component* c = this;
                while (1) {
                    if (c->getParent() == NULL) {
                        /* アプリケーションフレームを設定し、絶対位置を設定 */
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

        /** このコンポーネントのサイズを返します。*/
        int Component::getHeight() {
            return this->rectangle->height;
        }

        /** この Component がキーボードフォーカスを持つ場合に true を返します。*/
        bool Component::hasFocus() {
            return this->focused;
        }

        /** このコンポーネントが使用可能であるかどうかを判定します。*/
        bool Component::isEnabled() {
            return this->enabled;
        }

        /** このコンポーネントの親を返します。*/
        Container* Component::getParent() {
            return this->parent;
        }

        /** このコンポーネントのサイズを返します。*/
        int Component::getWidth() {
            return this->rectangle->width;
        }

        /** このコンポーネントの位置を、コンポーネントの左上隅を指定する点として返します。*/
        int Component::getX() {
            return this->rectangle->x;
        }

        /** このコンポーネントの位置を、コンポーネントの左上隅を指定する点として返します。*/
        int Component::getY() {
            return this->rectangle->y;
        }

        /** このコンポーネントをペイントします。*/
        void Component::paint(Graphics* g) {
            if (getWidth() == 0 || getHeight() == 0) return;
        }

        /** このコンポーネントで発生するコンポーネントイベントを処理します。*/
        void Component::processEvent(AWTEvent* e) {
            /* 非活性のときはイベントを受け付けない。*/
            if (isEnabled() == false) return;

            switch (e->getID()) {
            case MouseEvent::MOUSE_DRAGGED:
            case MouseEvent::MOUSE_MOVED:
            {
                int mouse_x = ((MouseEvent*) e)->getX() - this->tx;
                int mouse_y = ((MouseEvent*) e)->getY() - this->ty;
                int mouse_m = ((MouseEvent*) e)->getModifiers();

                if (Component::getComponentAt(mouse_x + getX(), mouse_y + getY()) == this) {
                    /* マウスが入った */
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
                    /* マウスが動いた */
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
                    /* マウスが出た */
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
         * このコンポーネントで発生するキーイベントを、
         * 登録されているすべての KeyListener オブジェクトに送ることにより、
         * キーイベントを処理します。
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
         * このコンポーネントで発生するマウスイベントを、
         * 登録されているすべての MouseListener オブジェクトに送ることにより、
         * マウスイベントを処理します。
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
            /* フォーカスが当たった */
            if (this->focused == false && e->getID() == MouseEvent::MOUSE_PRESSED) {
                requestFocus();
            }
        }

        /**
         * このコンポーネントで発生するマウスモーションイベントを、
         * 登録されているすべての MouseMotionListener オブジェクトに送ることにより、
         * マウスモーションイベントを処理します。
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
         * このコンポーネントからキーイベントを受け取らないように、
         * 指定されたキーリスナーを削除します。
        */
        void Component::removeKeyListener(KeyListener* l) {
            this->keyListeners->remove(this->keyListeners->indexOf((Object*) l));
        }

        /**
         * このコンポーネントからマウスイベントを受け取らないように、
         * 指定されたマウスリスナーを削除します。
        */
        void Component::removeMouseListener(MouseListener* l) {
            this->mouseListeners->remove(this->mouseListeners->indexOf((Object*) l));
        }

        /**
         * このコンポーネントからマウスモーションイベントを受け取らないように、
         * 指定されたマウスモーションリスナーを削除します。
        */
        void Component::removeMouseListener(MouseMotionListener* l) {
            this->mouseListeners->remove(this->mouseListeners->indexOf((Object*) l));
        }

        /** このコンポーネントを再描画します。*/
        void Component::repaint(int x, int y, int width, int height) {
            update(getGraphics(), x, y, width, height);
        }

        /** このコンポーネントが入力フォーカスを取得することを要求します。*/
        void Component::requestFocus() {
            this->focused = true;
            if (this->graphics->frame->active != NULL) {
                this->graphics->frame->active->transferFocus();
            }
            this->graphics->frame->active = this;
            repaint();
        }

        /** このコンポーネントを移動し、サイズ変更します。*/
        void Component::setBounds(int x, int y, int width, int height) {
            this->rectangle->x = x;
            this->rectangle->y = y;
            this->rectangle->width  = width;
            this->rectangle->height = height;
        }

        /** このコンポーネントのバックグラウンドカラーを設定します。*/
        void Component::setBackground(unsigned int c) {
            this->background = c;
        }

        /** このコンポーネントの親コンポーネントを指定します。*/
        void Component::setParent(Container* parent) {
            this->parent = parent;
        }

        /** このコンポーネントのフォアグラウンドカラーを設定します。*/
        void Component::setForeground(unsigned int c) {
            this->foreground = c;
        }

        /** 次のコンポーネントにフォーカスを移動します。*/
        void Component::transferFocus() {
            this->focused = false;
            repaint();
        }

        /** このコンポーネントを更新します。*/
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
