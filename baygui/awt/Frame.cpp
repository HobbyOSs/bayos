#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** 初期状態で可視ではない Frame の新しいインスタンスを生成します。Frame のタイトルは空です。*/
        Frame::Frame() {
            addClassName(baygui_awt_Frame);
            this->handle = 0;
            this->buffer = NULL;
            this->active = NULL;
            this->title  = NULL;
            Application::add(this);
        }

        /** デストラクタです。*/
        Frame::~Frame() {
            delete this->title;
        }

        /** フレームのタイトルを返します。*/
        char* Frame::getTitle() {
            return this->title;
        }

        /** このコンポーネントが入力フォーカスを取得することを要求します。*/
        void Frame::requestFocus() {
            this->focused = true;
            if (this->active != NULL) {
                this->active->transferFocus();
            }
            this->active = this;
        }

        /** アプリケーションの実行を開始します。*/
        void Frame::run() {
            Application::run(this);
        }

        /** このフレームのサイズ変更します。*/
        void Frame::setBounds(int x, int y, int width, int height) {
            this->rectangle->x = INSETS_LEFT;
            this->rectangle->y = INSETS_TOP;
            this->rectangle->width  = width;
            this->rectangle->height = height;

            if (this->buffer == NULL) {
                this->buffer = new unsigned char[width * height * sizeof(short)];
#ifdef HARIBOTE
                this->handle = api_openwin(
                    this->buffer, 
                    width, 
                    height, 
                    -1, 
                    (char *) this->title
                );
#endif
            }
        }

        /** このフレームのタイトルを、指定された文字列に設定します。*/
        void Frame::setTitle(const char* title) {
            if (this->title != NULL) delete this->title;
            int I = strlen(title) + 1;
            this->title = new char[I];
            memcpy(this->title, title, I);
        }

        /** 次のコンポーネントにフォーカスを移動します。*/
        void Frame::transferFocus() {
            this->focused = false;
        }
    }
}
