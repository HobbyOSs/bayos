#if !defined(_BAYGUI_AWT_APPLICATION_H_INCLUDED_)
#define _BAYGUI_AWT_APPLICATION_H_INCLUDED_

namespace baygui {
    namespace awt {
        /** アプリケーション動作用のクラスです。*/
        class Application {
        public:
            /** アプリケーションで使うフレーム一覧です。*/
            static ArrayList* frames;
            /** アプリケーションが実行中かどうかを表します。*/
            static bool running;
            
        public:
            /** 指定したフレームを追加します。*/
            static void add(Frame* frame);

            /** プラットフォームネイティブなイベントを処理します。*/
            static void doEvent(bool busy = true);

            /** 指定したハンドルを持つフレームを返します。ない場合は NULL になります。*/
            static Frame* get(unsigned int handle);

            /** 指定したフレームを削除します。*/
            static void remove(Frame* frame);

            /** アプリケーションの実行を開始します。*/
            static void run(Frame* main);
        };
    }
}

#endif
