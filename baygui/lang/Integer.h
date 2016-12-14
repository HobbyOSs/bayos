#if !defined(_BAYGUI_LANG_INTEGER_H_INCLUDED_)
#define _BAYGUI_LANG_INTEGER_H_INCLUDED_

namespace baygui {
    namespace lang {
        /** Integer �N���X�́A�v���~�e�B�u�^ int �̒l���I�u�W�F�N�g���Ƀ��b�v���܂��B*/
        class Integer : public Object {
        private:
            /** �v���~�e�B�u�^ */
            int value;

        public:
            /** �v���~�e�B�u�� int �̈�����\���A�V�������蓖�Ă�ꂽ Integer �I�u�W�F�N�g���\�z���܂��B*/
            Integer(int value);

            /** ������ŕ\������鐔�l��\���A�V�������蓖�Ă�ꂽ Integer �I�u�W�F�N�g�𐶐����܂��B*/
            Integer(const char* s);

            /** ���̃I�u�W�F�N�g���w�肳�ꂽ�I�u�W�F�N�g�Ɣ�r���܂��B*/
            bool equals(Object* obj);

            /** ���� Integer �̒l�� int �l�Ƃ��ĕԂ��܂��B*/
            int intValue();

            /** ������̈����𕄍��t�� 10 �i���̐����^�Ƃ��ĉ�͂��܂��B*/
            static int parseInt(const char* s);
        };
    }
}

#endif
