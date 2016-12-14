#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** ������Ԃŉ��ł͂Ȃ� Frame �̐V�����C���X�^���X�𐶐����܂��BFrame �̃^�C�g���͋�ł��B*/
        Frame::Frame() {
            addClassName(baygui_awt_Frame);
            this->handle = 0;
            this->buffer = NULL;
            this->active = NULL;
            this->title  = NULL;
            Application::add(this);
        }

        /** �f�X�g���N�^�ł��B*/
        Frame::~Frame() {
            delete this->title;
        }

        /** �t���[���̃^�C�g����Ԃ��܂��B*/
        char* Frame::getTitle() {
            return this->title;
        }

        /** ���̃R���|�[�l���g�����̓t�H�[�J�X���擾���邱�Ƃ�v�����܂��B*/
        void Frame::requestFocus() {
            this->focused = true;
            if (this->active != NULL) {
                this->active->transferFocus();
            }
            this->active = this;
        }

        /** �A�v���P�[�V�����̎��s���J�n���܂��B*/
        void Frame::run() {
            Application::run(this);
        }

        /** ���̃t���[���̃T�C�Y�ύX���܂��B*/
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

        /** ���̃t���[���̃^�C�g�����A�w�肳�ꂽ������ɐݒ肵�܂��B*/
        void Frame::setTitle(const char* title) {
            if (this->title != NULL) delete this->title;
            int I = strlen(title) + 1;
            this->title = new char[I];
            memcpy(this->title, title, I);
        }

        /** ���̃R���|�[�l���g�Ƀt�H�[�J�X���ړ����܂��B*/
        void Frame::transferFocus() {
            this->focused = false;
        }
    }
}
