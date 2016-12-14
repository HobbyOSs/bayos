#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** 空のラベルを構築します。*/
        Label::Label() {
            addClassName(baygui_awt_Label);
            this->alignment = Label::LEFT;
            this->text = NULL;
        }

        /** 新しいラベルを左揃えして、指定されたテキスト文字列で構築します。*/
        Label::Label(const char* text) {
            addClassName(baygui_awt_Label);
            this->alignment = Label::LEFT;
            setText(text);
        }

        /** 指定されたテキスト文字列を、指定された配置で表示する新しいラベルを構築します。*/
        Label::Label(const char* text, int alignment) {
            addClassName(baygui_awt_Label);
            this->alignment = alignment;
            setText(text);
        }

        /** デストラクタです。*/
        Label::~Label() {
            delete this->text;
        }

        /** このラベルの現在の配置を返します。*/
        int Label::getAlignment() {
            return this->alignment;
        }

        /** このラベルのテキストを返します。*/
        char* Label::getText() {
            return this->text;
        }

        /** このコンポーネントをペイントします。*/
        void Label::paint(Graphics* g) {
            int w = getWidth();
            int h = getHeight();

            /* 一度背景色でクリア */
            g->setColor(getBackground());
            g->fillRect(0, 0, w, h);

            /* 文字列を描画 */
            int fw = FontMetrice::stringWidth(this->text);
            int fh = FontMetrice::getHeight();
            if (isEnabled() == true) {
                g->setColor(getForeground());
            } else {
                g->setColor(Color::gray);
            }
            if (this->alignment == Label::RIGHT) {
                g->drawString(this->text, (w - fw), (h - fh) / 2);
            } else if (this->alignment == Label::CENTER) {
                g->drawString(this->text, (w - fw) / 2, (h - fh) / 2);
            } else {
                g->drawString(this->text, 0, (h - fh) / 2);
            }
        }

        /** このラベルの配置を、指定された配置に設定します。*/
        void Label::setAlignment(int alignment) {
            this->alignment = alignment;
        }

        /** このラベルのテキストを、指定されたテキストに設定します。*/
        void Label::setText(const char* text) {
            if (this->text != NULL) delete this->text;
            int I = strlen(text) + 1;
            this->text = new char[I];
            memcpy(this->text, text, I);
        }
    }
}
