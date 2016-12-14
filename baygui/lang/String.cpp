#include "../../baygui.h"

namespace baygui {
    namespace lang {
        /** �V�����������ꂽ String �I�u�W�F�N�g�����������āA��̕����V�[�P���X��\���悤�ɂ��܂��B*/
        String::String() {
            addClassName(baygui_lang_String);
            this->_buffer = NULL;
        }

        /** �V���� String �����蓖�ĂāA���ꂪ�����z������Ɍ��݊܂܂�Ă��镶���V�[�P���X��\���悤�ɂ��܂��B*/
        String::String(const char* text) {
            addClassName(baygui_lang_String);
            this->_len = strlen(text);
            this->_buffer = new char[this->_len + 1];
            memcpy(this->_buffer, text, this->_len + 1);
        }

        /** �����z������̕����z�񂩂�Ȃ镶�����܂ސV���� String �����蓖�Ă܂��B*/
        String::String(const char* text, int start, int length) {
            addClassName(baygui_lang_String);
            this->_len = length;
            this->_buffer = new char[length + 1];
            memcpy(this->_buffer, &text[start], length);
        }

        /** �f�X�g���N�^�ł��B*/
        String::~String() {
            delete this->_buffer;
        }

        /** ���̕����񂪁A�w�肳�ꂽ�ڔ����ŏI�邩�ǂ����𔻒肵�܂��B*/
        bool String::endsWith(const char* text) {
            int len = strlen(text);
            int pos = this->_len - len;
            if (pos < 0) return false;
            for (int i = 0; i < len; i++) {
                if (this->_buffer[pos + i] != text[i]) return false;
            }
            return true;
        }

        /** ���̕�����̒�����Ԃ��܂��B*/
        int String::length() {
            return this->_len;
        }

        /** ���̕�������A�w�肳�ꂽ�����Ɉ�v����ʒu�ŕ������܂��B*/
        ArrayList* String::split(char ch) {
            ArrayList* list = new ArrayList();
            int p = 0;
            for (int i = 0; i <= this->_len; i++) {
                if (i == this->_len || this->_buffer[i] == ch) {
                    if (i > p) {
                        list->add(new String(this->_buffer, p, i - p));
                    }
                    p = i + 1;
                }
            }
            return list;
        }

        /** ���̕����񂪁A�w�肳�ꂽ�ړ����Ŏn�܂邩�ǂ����𔻒肵�܂��B*/
        bool String::startsWith(const char* text) {
            int len = strlen(text);
            if (len > this->_len) return false;
            for (int i = 0; i < len; i++) {
                if (this->_buffer[i] != text[i]) return false;
            }
            return true;
        }

        /**
         * String ���v���b�g�t�H�[���̃f�t�H���g�̕����G���R�[�f�B���O�iUTF-8�j�ɏ]���ăo�C�g�ɕϊ����A
         * ���ʂ�V�����o�C�g�z��Ɋi�[���܂��B
        */
        char* String::toCharArray() {
            return this->_buffer;
        }
    }
}
