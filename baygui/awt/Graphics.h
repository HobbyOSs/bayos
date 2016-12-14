#if !defined(_BAYGUI_AWT_GRAPHICS_H_INCLUDED_)
#define _BAYGUI_AWT_GRAPHICS_H_INCLUDED_

namespace baygui {
    namespace awt {
        class Frame;

        /** Graphics �N���X�́A���ׂẴO���t�B�b�N�R���e�L�X�g�̒��ۊ��N���X�ł��B*/
        class Graphics : public Object {
        public:
            /** �g�b�v���x���E�B���h�E�ł��B*/
            Frame* frame;
            /** �`��p�̃o�b�t�@�[�ł��B*/
            unsigned char* buffer;

        protected:
            /** �g�b�v���x���E�B���h�E�̍��[����̈ʒu�ł��B*/
            int tx;
            /** �g�b�v���x���E�B���h�E�̍��[����̈ʒu�ł��B*/
            int ty;
            /** �`�悷��F�ł��B*/
            unsigned int color;

        public:
            /** �V���� Graphics �I�u�W�F�N�g���쐬���܂��B*/
            Graphics();

            /**
             * ���̃O���t�B�b�N�X�R���e�L�X�g�̍��W�̌n�̍��W (x1, y1) ��
             * ���W (x2, y2) �Ƃ̊ԂɌ��݂̐F���g���Đ���`���܂��B
            */
            void drawLine(int x1, int y1, int x2, int y2);

            /** �w�肳�ꂽ�_��`���܂��B*/
            void drawPixel(int x, int y);

            /** �w�肳�ꂽ��`�̗֊s��`���܂��B*/
            void drawRect(int x, int y, int width, int height);

            /**
             * ���̃O���t�B�b�N�X�R���e�L�X�g�̌��݂̃t�H���g�ƐF���g���A
             * �w�肳�ꂽ������ɂ���Ďw�肳�ꂽ�e�L�X�g��`���܂��B
            */
            void drawString(const char* str, int x, int y);

            /** �w�肳�ꂽ��`��h��Ԃ��܂��B*/
            void fillRect(int x, int y, int w, int h);

            /** ���̃O���t�B�b�N�X�R���e�L�X�g�̌��݂̐F���A�w�肳�ꂽ�F�ɐݒ肵�܂��B*/
            void setColor(unsigned int color);

            /** ���̃O���t�B�b�N�X�R���e�L�X�g�̌��݂̐F���A�w�肳�ꂽ�F�ɐݒ肵�܂��B*/
            void setColor(unsigned char r, unsigned char g, unsigned char b);

            /** �O���t�B�b�N�X�R���e�L�X�g�̌��_�����݂̍��W�n�� (x, y) �ɕϊ����܂��B*/
            void translate(int x, int y);
        };
    }
}

#endif
