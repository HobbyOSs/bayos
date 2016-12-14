#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** ���̃t�H���g�̃e�L�X�g 1 �s�̕W���̍������擾���܂��B*/
        int FontMetrice::getHeight() {
            return 12;
        }

        /** �w�肳�ꂽ��������A���� Font �ŕ\�����邽�߂̗L�����̍��v��Ԃ��܂��B*/
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
