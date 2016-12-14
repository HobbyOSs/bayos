#if !defined(_BAYGUI_LANG_OBJECT_H_INCLUDED_)
#define _BAYGUI_LANG_OBJECT_H_INCLUDED_

namespace baygui {
    namespace lang {
        /**
         * Object �N���X�́A�N���X�K�w�̃��[�g�ł��B
         * ���ׂẴN���X�́A�X�[�p�[�N���X�Ƃ��� Object �������܂��B
        */
        class Object {
        private:
            /** �N���X�����X�g�̃f�t�H���g�e�ʂł��B*/
            static const int defaultCapacity = 5;
            /** �N���X�����X�g���̗v�f�ꗗ�ł��B*/
            int* _elements;
            /** �N���X�����X�g���̗v�f���ł��B*/
            int _size;
            /** �N���X�����X�g�̌��݂̗e�ʂł��B*/
            int _capacity;

        public:
            /** �f�t�H���g�R���X�g���N�^�ł��B */
            Object();

            /** �f�X�g���N�^�ł��B */
            virtual ~Object();

        protected:
            /** C++ �ɂ��[�� instaceof �̂��߂Ɏg�p���܂��B*/
            void addClassName(int className);

        public:
            /** C++ �ɂ��[�� instanceof �ł��B*/
            bool instanceof(int className);

        protected:
            /** C++ �ɂ��[�� instaceof �̂��߂Ɏg�p���܂��B*/
            void removeClassName(int className);
        };
    }
}

#endif
