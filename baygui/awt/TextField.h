#if !defined(_BAYGUI_AWT_TEXTFIELD_H_INCLUDED_)
#define _BAYGUI_AWT_TEXTFIELD_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * TextField �I�u�W�F�N�g�́A1 �s�̃e�L�X�g�̕ҏW���s����悤�ɂ���e�L�X�g�R���|�[�l���g�ł��B
        */
        class TextField : public TextComponent {
        public:
            /** �V�����e�L�X�g�t�B�[���h���\�z���܂��B*/
            TextField();

            /** �w�肳�ꂽ�e�L�X�g�ŏ��������ꂽ�V�����e�L�X�g�t�B�[���h���\�z���܂��B*/
            TextField(const char* text);

            /** ���̃R���|�[�l���g���y�C���g���܂��B*/
            virtual void paint(Graphics* g);
        };
    }
}

#endif
