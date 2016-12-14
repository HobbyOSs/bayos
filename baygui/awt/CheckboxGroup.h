#if !defined(_BAYGUI_AWT_CHECKBOXGROUP_H_INCLUDED_)
#define _BAYGUI_AWT_CHECKBOXGROUP_H_INCLUDED_

namespace baygui {
    namespace awt {
        /**
         * CheckboxGroup クラスは Checkbox ボタンをグループ化するのに使用します。
        */
        class CheckboxGroup : public Object {
        protected:
            /** チェックボックス一覧です。*/
            ArrayList* checkboxes;
            /** 選択されたチェックボックスです。*/
            Checkbox* selectedCheckbox;
            
        public:
            /** CheckboxGroup の新しいインスタンスを生成します。*/
            CheckboxGroup();

            /** デストラクタです。*/
            virtual ~CheckboxGroup();

            /** Checkboxを設定します。*/
            void add(Checkbox* box);

            /** このチェックボックスグループでの現在の選択を返します。*/
            Checkbox* getSelectedCheckbox();

            /** 現在このグループ内で選択されているチェックボックスを、指定されたチェックボックスに設定します。*/
            void setSelectedCheckbox(Checkbox* box);
        };
    }
}

#endif
