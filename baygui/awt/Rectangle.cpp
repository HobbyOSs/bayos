#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** ����������W��Ԃ� (0, 0) �ɂ���A���ƍ����������Ƃ� 0 �̐V���� Rectangle ���\�z���܂��B*/
        Rectangle::Rectangle() {
            addClassName(baygui_awt_Rectangle);
            x = y = width = height = 0;
        }
    }
}
