#if !defined(_BAYGUI_LANG_STRING_H_INCLUDED_)
#define _BAYGUI_LANG_STRING_H_INCLUDED_

using namespace baygui::lang;
using namespace baygui::util;

namespace baygui {
    namespace lang {
        class String : public Object {
        private:
            /** �����Ŏg��������ł��B*/
            char* _buffer;
            /** �����Ŏg��������̃o�C�g���ł��B*/
            int _len;

        public:
            /** �V�����������ꂽ String �I�u�W�F�N�g�����������āA��̕����V�[�P���X��\���悤�ɂ��܂��B*/
            String();

            /** �V���� String �����蓖�ĂāA���ꂪ�����z������Ɍ��݊܂܂�Ă��镶���V�[�P���X��\���悤�ɂ��܂��B*/
            String(const char* text);

            /** �����z������̕����z�񂩂�Ȃ镶�����܂ސV���� String �����蓖�Ă܂��B*/
            String(const char* text, int start, int length);

            /** �f�X�g���N�^�ł��B*/
            ~String();

            /** ���̕����񂪁A�w�肳�ꂽ�ڔ����ŏI�邩�ǂ����𔻒肵�܂��B*/
            bool endsWith(const char* text);

            /** ���̕�����̒�����Ԃ��܂��B*/
            int length();

            /** ���̕�������A�w�肳�ꂽ�����Ɉ�v����ʒu�ŕ������܂��B*/
            ArrayList* split(char ch);

            /** ���̕����񂪁A�w�肳�ꂽ�ړ����Ŏn�܂邩�ǂ����𔻒肵�܂��B*/
            bool startsWith(const char* text);

            /**
             * String ���v���b�g�t�H�[���̃f�t�H���g�̕����G���R�[�f�B���O�iUTF-8�j�ɏ]���ăo�C�g�ɕϊ����A
             * ���ʂ�V�����o�C�g�z��Ɋi�[���܂��B
            */
            char* toCharArray();
        };
    }
}

#endif
