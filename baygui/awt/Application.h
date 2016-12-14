#if !defined(_BAYGUI_AWT_APPLICATION_H_INCLUDED_)
#define _BAYGUI_AWT_APPLICATION_H_INCLUDED_

namespace baygui {
    namespace awt {
        /** �A�v���P�[�V��������p�̃N���X�ł��B*/
        class Application {
        public:
            /** �A�v���P�[�V�����Ŏg���t���[���ꗗ�ł��B*/
            static ArrayList* frames;
            /** �A�v���P�[�V���������s�����ǂ�����\���܂��B*/
            static bool running;
            
        public:
            /** �w�肵���t���[����ǉ����܂��B*/
            static void add(Frame* frame);

            /** �v���b�g�t�H�[���l�C�e�B�u�ȃC�x���g���������܂��B*/
            static void doEvent(bool busy = true);

            /** �w�肵���n���h�������t���[����Ԃ��܂��B�Ȃ��ꍇ�� NULL �ɂȂ�܂��B*/
            static Frame* get(unsigned int handle);

            /** �w�肵���t���[�����폜���܂��B*/
            static void remove(Frame* frame);

            /** �A�v���P�[�V�����̎��s���J�n���܂��B*/
            static void run(Frame* main);
        };
    }
}

#endif
