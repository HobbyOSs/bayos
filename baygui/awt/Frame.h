#if !defined(_BAYGUI_AWT_FRAME_H_INCLUDED_)
#define _BAYGUI_AWT_FRAME_H_INCLUDED_

#define INSETS_TOP    22
#define INSETS_BOTTOM 6
#define INSETS_LEFT   6
#define INSETS_RIGHT  6

namespace baygui {
    namespace awt {
        /** Frame �́A�^�C�g���ƃ{�[�_�t���̃g�b�v���x���E�B���h�E�ł��B*/
        class Frame : public Container {
        public:
            /** �g�b�v���x���E�B���h�E�̃n���h���ł��B*/
            unsigned int handle;
            /** �`��p�̃o�b�t�@�[�ł��B*/
            unsigned char* buffer;
            /** ���݃t�H�[�J�X������R���|�[�l���g������킵�܂��B*/
            Component* active;

        protected:
            /** ���̃t���[���̃^�C�g���ł��B*/
            char* title;

        public:
            /** ������Ԃŉ��ł͂Ȃ� Frame �̐V�����C���X�^���X�𐶐����܂��BFrame �̃^�C�g���͋�ł��B*/
            Frame();

            /** �f�X�g���N�^�ł��B*/
            virtual ~Frame();

            /** �t���[���̃^�C�g����Ԃ��܂��B*/
            char* getTitle();

            /** ���̃R���|�[�l���g�����̓t�H�[�J�X���擾���邱�Ƃ�v�����܂��B*/
            virtual void requestFocus();

            /** �A�v���P�[�V�����̎��s���J�n���܂��B*/
            void run();

            /** ���̃t���[���̃T�C�Y�ύX���܂��B*/
            virtual void setBounds(int x, int y, int width, int height);

            /** ���̃t���[���̃^�C�g�����A�w�肳�ꂽ������ɐݒ肵�܂��B*/
            void setTitle(const char* title);

            /** ���̃R���|�[�l���g�Ƀt�H�[�J�X���ړ����܂��B*/
            virtual void transferFocus();
        };
    }
}

#endif
