#if !defined(_BAYGUI_AWT_FONTMETRICS_H_INCLUDED_)
#define _BAYGUI_AWT_FONTMETRICS_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * FontMetrics �N���X�́A����̉�ʂł̓���̃t�H���g�Ɋւ���`������J�v�Z��������
         * �t�H���g���g���b�N�I�u�W�F�N�g���`���܂��B
        */
        class FontMetrice : public Object {
        public:
            /** ���̃t�H���g�̃e�L�X�g 1 �s�̕W���̍������擾���܂��B*/
            static int getHeight();

            /** �w�肳�ꂽ��������A���� Font �ŕ\�����邽�߂̗L�����̍��v��Ԃ��܂��B*/
            static int stringWidth(const char* str);
        };
    }
}

#endif
