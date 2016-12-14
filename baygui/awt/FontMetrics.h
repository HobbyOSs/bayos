#if !defined(_BAYGUI_AWT_FONTMETRICS_H_INCLUDED_)
#define _BAYGUI_AWT_FONTMETRICS_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * FontMetrics クラスは、特定の画面での特定のフォントに関する描画情報をカプセル化する
         * フォントメトリックオブジェクトを定義します。
        */
        class FontMetrice : public Object {
        public:
            /** このフォントのテキスト 1 行の標準の高さを取得します。*/
            static int getHeight();

            /** 指定された文字列を、この Font で表示するための有効幅の合計を返します。*/
            static int stringWidth(const char* str);
        };
    }
}

#endif
