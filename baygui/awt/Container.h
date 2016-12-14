#if !defined(_BAYGUI_AWT_CONTAINER_H_INCLUDED_)
#define _BAYGUI_AWT_CONTAINER_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * 一般的な コンテナオブジェクトは、
         * ほかのコンポーネントを含むことができるコンポーネントです。
        */
        class Container : public Component {
        protected:
            /** このコンテナの子一覧です。*/
            ArrayList* components;

        public:
            /** 新しいコンテナを構築します。*/
            Container();

            /** デストラクタです。*/
            virtual ~Container();

            /** 指定されたコンポーネントをこのコンテナの最後に追加します。*/
            virtual Component* add(Component* c);

            /**
             * このコンポーネントまたはそのサブコンポーネントの 1 つに
             * イベントをディスパッチします。
            */
            virtual void dispatchEvent(AWTEvent* e);

            /**
             * このコンポーネントまたはその直接のサブコンポーネントが
             * 位置 (x, y) を含んでいるかどうかを判定します。
            */
            virtual Component* getComponentAt(int x, int y);

            /** コンテナ内のすべてのコンポーネントを返します。*/
            ArrayList* getComponents();

            /** コンテナから、指定されたコンポーネントを削除します。*/
            virtual void remove(Component* c);

            /**
             * コンテナを再描画します。
             * このメソッドは、このコンテナの子である軽量コンポーネントに更新要求を転送します。
             * このメソッドが再実装された場合、Container::update(g) を呼び出して軽量コンポーネントが
             * 適切に描画されるようにする必要があります。
            */
            virtual void update(Graphics* g, int x = 0, int y = 0, int w = 0, int h = 0);
        };
    }
}

#endif
