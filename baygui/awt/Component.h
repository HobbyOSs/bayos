#if !defined(_BAYGUI_AWT_COMPONENT_H_INCLUDED_)
#define _BAYGUI_AWT_COMPONENT_H_INCLUDED_

using namespace baygui::lang;
using namespace baygui::util;
using namespace baygui::awt::event;

namespace baygui {
    namespace awt {
        class Container;

        /** 「コンポーネント」は、画面に表示でき、ユーザと対話できるグラフィカルな表現を持つオブジェクトです。*/
        class Component : public Object {
        protected:
            /** トップレベルウィンドウの左端からの位置です。*/
            int tx;
            /** トップレベルウィンドウの左端からの位置です。*/
            int ty;
            /** このコンポーネントの背景色です。*/
            unsigned int background;
            /** このコンポーネントの前景色です。*/
            unsigned int foreground;
            /** このコンポーネントにフォーカスかあるかどうかをあらわします。*/
            bool focused;
            /** このコンポーネントが使用可能かどうかをあらわします。*/
            bool enabled;
            /** このコンポーネントにマウスが入ったかどうかをあらわします。*/
            bool mouseEntered;
            /** このコンポーネントの Rectangle です。*/
            Rectangle* rectangle;
            /** このコンポーネントのグラフィックコンテキストです。*/
            Graphics* graphics;
            /** このコンポーネントの親コンポーネントです。*/
            Container* parent;
            /** キーイベント用リスナーリストです。*/
            ArrayList* keyListeners;
            /** マウスイベント用リスナーリストです。*/
            ArrayList* mouseListeners;
            /** マウスモーションイベント用リスナーリストです。*/
            ArrayList* mouseMotionListeners;

        public:
            /** コンポーネントを新しく構築します。*/
            Component();

            /** デストラクタです。*/
            virtual ~Component();

            /**
             * このコンポーネントからキーイベントを受け取るために、
             * 指定されたキーリスナーを追加します。
            */
            void addKeyListener(KeyListener* l);

            /**
             * このコンポーネントからマウスイベントを受け取るために、
             * 指定されたマウスリスナーを追加します。
            */
            void addMouseListener(MouseListener* l);

            /**
             * このコンポーネントからマウスモーションイベントを受け取るために、
             * 指定されたマウスモーションリスナーを追加します。
            */
            void addMouseMotionListener(MouseMotionListener* l);

            /** このコンポーネントまたはそのサブコンポーネントの 1 つにイベントをディスパッチします。*/
            virtual void dispatchEvent(AWTEvent* e);

            /** このコンポーネントのバックグラウンドカラーを返します。*/
            unsigned int getBackground();

            /** このコンポーネントの境界を Rectangle オブジェクトとして返します。*/
            Rectangle* getBounds();

            /**
             * このコンポーネントまたはその直接のサブコンポーネントが位置 (x, y) 
             * を含んでいるかどうかを判定します。
            */
            virtual Component* getComponentAt(int x, int y);

            /** このコンポーネントのフォアグラウンドカラーを返します。*/
            unsigned int getForeground();

            /** このコンポーネントのグラフィックスコンテキストを作成します。*/
            virtual Graphics* getGraphics();

            /** このコンポーネントのサイズを返します。*/
            int getHeight();

            /** この Component がキーボードフォーカスを持つ場合に true を返します。*/
            bool hasFocus();

            /** このコンポーネントが使用可能であるかどうかを判定します。*/
            bool isEnabled();

            /** このコンポーネントの親を返します。*/
            Container* getParent();

            /** このコンポーネントのサイズを返します。*/
            int getWidth();

            /** このコンポーネントの位置を、コンポーネントの左上隅を指定する点として返します。*/
            int getX();

            /** このコンポーネントの位置を、コンポーネントの左上隅を指定する点として返します。*/
            int getY();

            /** このコンポーネントをペイントします。*/
            virtual void paint(Graphics* g);

        protected:
            /** このコンポーネントで発生するコンポーネントイベントを処理します。*/
            virtual void processEvent(AWTEvent* e);

            /**
             * このコンポーネントで発生するキーイベントを、
             * 登録されているすべての KeyListener オブジェクトに送ることにより、
             * キーイベントを処理します。
            */
            virtual void processKeyEvent(KeyEvent* e);

            /**
             * このコンポーネントで発生するマウスイベントを、
             * 登録されているすべての MouseListener オブジェクトに送ることにより、
             * マウスイベントを処理します。
            */
            virtual void processMouseEvent(MouseEvent* e);

            /**
             * このコンポーネントで発生するマウスモーションイベントを、
             * 登録されているすべての MouseMotionListener オブジェクトに送ることにより、
             * マウスモーションイベントを処理します。
            */
            virtual void processMouseMotionEvent(MouseEvent* e);

        public:
            /**
             * このコンポーネントからキーイベントを受け取らないように、
             * 指定されたキーリスナーを削除します。
            */
            void removeKeyListener(KeyListener* l);

            /**
             * このコンポーネントからマウスイベントを受け取らないように、
             * 指定されたマウスリスナーを削除します。
            */
            void removeMouseListener(MouseListener* l);

            /**
             * このコンポーネントからマウスモーションイベントを受け取らないように、
             * 指定されたマウスモーションリスナーを削除します。
            */
            void removeMouseListener(MouseMotionListener* l);

            /** このコンポーネントを再描画します。*/
            virtual void repaint(int x = 0, int y = 0, int w = 0, int h = 0);

            /** このコンポーネントが入力フォーカスを取得することを要求します。*/
            virtual void requestFocus();

            /** このコンポーネントのバックグラウンドカラーを設定します。*/
            void setBackground(unsigned int c);

            /** このコンポーネントを移動し、サイズ変更します。*/
            virtual void setBounds(int x, int y, int width, int height);

            /** このコンポーネントのフォアグラウンドカラーを設定します。*/
            void setForeground(unsigned int c);

            /** このコンポーネントの親コンポーネントを指定します。*/
            virtual void setParent(Container* parent);

            /** 次のコンポーネントにフォーカスを移動します。*/
            virtual void transferFocus();

            /** このコンポーネントを更新します。*/
            virtual void update(Graphics* g, int x = 0, int y = 0, int w = 0, int h = 0);
        };
    }
}

#endif
