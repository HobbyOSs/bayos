#if !defined(_BAYGUI_AWT_SCROLLBAR_H_INCLUDED_)
#define _BAYGUI_AWT_SCROLLBAR_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         水平・垂直スクロールバークラス
        */
        class Scrollbar : public Component {
        public:
            /** 水平スクロールバー */
            static const int HORIZONTAL = 0;
            /** 垂直スクロールバー */
            static const int VERTICAL   = 1;

        protected:
            /** スクロールバーの種類です。*/
            int orientation;
            /** 最小値です。*/
            int minimum;
            /** 最大値です。*/
            int maximum;
            /** 「ブロック」増分値です。*/
            int blocksize;
            /** 一つ前の値です。*/
            int preValue;
            /** 現在の値です。*/
            int value;

        public:
            /** 新しい垂直スクロールバーを構築します。*/
            Scrollbar();

            /** 指定された方向の新しいスクロールバーを構築します。*/
            Scrollbar(int orientation);

            /** デストラクタです。*/
            virtual ~Scrollbar();

            /** このスクロールバーの「ブロック」増分値を返します。*/
            int getBlocksize();

            /** このスクロールバーの最大値を返します。*/
            int getMaximum();

            /** このスクロールバーの最小値を返します。*/
            int getMinimum();

            /** このスクロールバーの現在値を返します。*/
            int getValue();

            /** このコンポーネントをペイントします。*/
            virtual void paint(Graphics* g);

            /** このコンポーネントで発生するマウスイベントを処理します。*/
            virtual void processMouseEvent(MouseEvent* e);

            /** このコンポーネントで発生するマウスモーションイベントを処理します。*/
            virtual void processMouseMotionEvent(MouseEvent* e);

            /** このスクロールバーの「ブロック」増分値を設定します。*/
            void setBlocksize(int n);

            /** このスクロールバーの最大値を設定します。*/
            void setMaximum(int n);

            /** このスクロールバーの最小値を設定します。*/
            void setMinimum(int n);

            /**
             * このコンポーネントを移動し、サイズ変更します。
             * 垂直スクロールバーの時は幅が16、水平スクロールバーのときは高さが16になります。
             * それ以外の値を設定しても16になります。
            */
            virtual void setBounds(int x, int y, int w, int h);

            /** このスクロールバーの値を、指定された値に設定します。*/
            void setValue(int value);
        };
    }
}

#endif
