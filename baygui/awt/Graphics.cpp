#include "../../baygui.h"

namespace baygui {
    namespace awt {
        /** �V���� Graphics �I�u�W�F�N�g���쐬���܂��B*/
        Graphics::Graphics() {
            addClassName(baygui_awt_Graphics);
            this->frame  = NULL;
            this->buffer = NULL;
            this->tx     = 0;
            this->ty     = 0;
            this->color  = 0;
        }

        /**
         * ���̃O���t�B�b�N�X�R���e�L�X�g�̍��W�̌n�̍��W (x1, y1) ��
         * ���W (x2, y2) �Ƃ̊ԂɌ��݂̐F���g���Đ���`���܂��B
        */
        void Graphics::drawLine(int x1, int y1, int x2, int y2) {
#ifdef HARIBOTE
            api_linewin(
                this->frame->handle,
                this->tx + x1,
                this->ty + y1,
                this->tx + x2,
                this->ty + y2,
                BPP24to16(this->color)
            );
#else
#ifdef BPP8
            unsigned char* p  = this->buffer;
            unsigned char col = BPP24to8(this->color);
#endif
#ifdef BPP16
            unsigned short* p  = (unsigned short *) this->buffer;
            unsigned short col = BPP24to16(this->color);
#endif
#ifdef BPP32
            unsigned int* p  = (unsigned int *) this->buffer;
            unsigned int col = this->color;
#endif
            int cw = this->frame->getWidth();
            int dx = (x1 > x2) ? (x1 - x2) : (x2 - x1);
            int dy = (y1 > y2) ? (y1 - y2) : (y2 - y1);

            if (dx == 0 && dy == 0) {
                p[(this->tx + x1) + cw * (this->ty + y1)] = col;
            } else if (dx >= dy) {
                if (x1 > x2) {
                    swap(&x1, &x2);
                    swap(&y1, &y2);
                }
                for (int x = x1; x <= x2; x++) {
                    p[(this->tx + x) + cw * (this->ty + ((2 * y1 + 2 * (y2 - y1) * (x - x1) / (x2 - x1)) + 1) / 2)] = col;
                }
            } else {
                if (y1 > y2) {
                    swap(&x1, &x2);
                    swap(&y1, &y2);
                }
                for (int y = y1; y <= y2; y++) {
                    p[(this->tx + (2 * x1 + 2 * (x2 - x1) * (y - y1) / (y2 - y1) + 1) / 2) + cw * (this->ty + y)] = col;
                }
            }
#endif
        }

        /** �w�肳�ꂽ�_��`���܂��B*/
        void Graphics::drawPixel(int x, int y) {
#ifdef HARIBOTE
            api_point(
                this->frame->handle,
                this->tx + x,
                this->ty + y,
                BPP24to16(this->color)
            );
#else
#ifdef BPP8
            unsigned char* p  = this->buffer;
            unsigned char col = BPP24to8(this->color);
#endif
#ifdef BPP16
            unsigned short* p  = (unsigned short *) this->buffer;
            unsigned short col = BPP24to16(this->color);
#endif
#ifdef BPP32
            unsigned int* p  = (unsigned int *) this->buffer;
            unsigned int col = this->color;
#endif
            int cw = this->frame->getWidth();
            p[(this->tx + x) + cw * (this->ty + y)] = col;
#endif
        }

        /** �w�肳�ꂽ��`�̗֊s��`���܂��B*/
        void Graphics::drawRect(int x, int y, int width, int height) {
            drawLine(x, y, x + width - 1, y);
            drawLine(x, y, x, y + height - 1);
            drawLine(x + width - 1, y, x + width - 1, y + height - 1);
            drawLine(x, y + height - 1, x + width - 1, y + height - 1);
        }

        /**
         * ���̃O���t�B�b�N�X�R���e�L�X�g�̌��݂̃t�H���g�ƐF���g���A
         * �w�肳�ꂽ������ɂ���Ďw�肳�ꂽ�e�L�X�g��`���܂��B
        */
        void Graphics::drawString(const char* str, int x, int y) {
#ifdef HARIBOTE
            api_putstrwin(
                this->frame->handle,
                this->tx + x,
                this->ty + y,
                BPP24to16(this->color),
                strlen(str),
                (char *) str
            );
#endif
        }

        /** �w�肳�ꂽ��`��h��Ԃ��܂��B*/
        void Graphics::fillRect(int x, int y, int w, int h) {
#ifdef HARIBOTE
            api_boxfilwin(
                this->frame->handle,
                this->tx + x,
                this->ty + y,
                w,
                h,
                BPP24to16(this->color)
            );
#else
#ifdef BPP8
            unsigned char* p  = this->buffer;
            unsigned char col = BPP24to8(this->color);
#endif
#ifdef BPP16
            unsigned short* p  = (unsigned short *) this->buffer;
            unsigned short col = BPP24to16(this->color);
#endif
#ifdef BPP32
            unsigned int* p  = (unsigned int *) this->buffer;
            unsigned int col = this->color;
#endif
            int cw = this->frame->getWidth();
            for (int i = y; i < y + h; i++) {
                for (int j = x; j < x + w; j++) {
                    p[(this->tx + j) + cw * (this->ty + i)] = col;
                }
            }
#endif
        }

        /** ���̃O���t�B�b�N�X�R���e�L�X�g�̌��݂̐F���A�w�肳�ꂽ�F�ɐݒ肵�܂��B*/
        void Graphics::setColor(unsigned int color) {
            this->color = color;
        }

        /** ���̃O���t�B�b�N�X�R���e�L�X�g�̌��݂̐F���A�w�肳�ꂽ�F�ɐݒ肵�܂��B*/
        void Graphics::setColor(unsigned char r, unsigned char g, unsigned char b) {
            this->color = (r << 16 | g << 8 | b);
        }

        /** �O���t�B�b�N�X�R���e�L�X�g�̌��_�����݂̍��W�n�� (x, y) �ɕϊ����܂��B*/
        void Graphics::translate(int x, int y) {
            this->tx = x;
            this->ty = y;
        }
    }
}
