#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** このフォントのテキスト 1 行の標準の高さを取得します。*/
        int FontMetrice::getHeight() {
            return 12;
        }

        /** 指定された文字列を、この Font で表示するための有効幅の合計を返します。*/
        int FontMetrice::stringWidth(const char* str) {
#ifdef BAYOS
            WSTR_INFO info;
            bayos_get_wstr_info((char *) str, &info);
            return info.width;
#else
            return strlen((char *) str) * 6;
#endif
        }
    }
}
