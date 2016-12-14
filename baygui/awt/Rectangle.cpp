#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** 左上隅が座標空間の (0, 0) にあり、幅と高さが両方とも 0 の新しい Rectangle を構築します。*/
        Rectangle::Rectangle() {
            addClassName(baygui_awt_Rectangle);
            x = y = width = height = 0;
        }
    }
}
