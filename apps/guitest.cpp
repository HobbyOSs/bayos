#include "../baygui.h"

/** クラス定義部 */
class GuiTest : public Frame {
private:
    Button *button1;
    Label *label1, *label2, *label3;
    TextField *text1, *text2, *text3;
    Checkbox *check1, *check2;
    CheckboxGroup *group1;
    Listbox *list1;
    Scrollbar *scroll1, *scroll2;
    #if 0
    Window *dialog;
    #endif

public:
    /** コンストラクタ */
    GuiTest() {
        setTitle("(oAo) ﾅｶﾏ");
        setBounds((800 - 300) / 2,(600 - 200) / 2,300,200);

        // 部品を初期化
        button1 = new Button("ｵﾏｴﾓﾅ orz");
        button1->setBounds(5,5,80,20);
        label1 = new Label("Label<-");
        //label1->setFontStyle(Font::BOLD);
        label1->setBounds(5,26,100,20);
        label2 = new Label("=Label=", Label::CENTER);
        //label2->setFontStyle(Font::ITALIC);
        label2->setBackground(Color::black);
        label2->setForeground(Color::white);
        label2->setBounds(5,46,100,20);
        label3 = new Label("Label->", Label::RIGHT);
        //label3->setFontStyle(Font::BOLD | Font::ITALIC);
        label3->setBounds(5,66,100,20);
        text1 = new TextField();
        text1->setBounds(5,86,100,20);
        text1->setText("Hello,World");
        text2 = new TextField();
        text2->setBounds(5,107,100,20);
        text3 = new TextField();
        text3->setBounds(5,128,100,20);
        check1 = new Checkbox("本気ですか？");
        check1->setBounds(110,5,100,20);
        check2 = new Checkbox("買っちゃう？");
        check2->setBounds(110,25,100,20);
        group1 = new CheckboxGroup();
        group1->add(check1);
        group1->add(check2);
        list1 = new Listbox();
        list1->setBounds(110,50,100,100);
        list1->add("ひげぽん");
        list1->add("ｷﾀｰｰ!!");
        list1->add("Mona is here");
        scroll1 = new Scrollbar();
        scroll1->setBounds(273,0,16,158);
        scroll2 = new Scrollbar(Scrollbar::HORIZONTAL);
        scroll2->setBounds(0,157,274,16);

        // 部品を追加
        add(button1);
        add(label1);
        add(label2);
        add(label3);
        add(text1);
        add(text2);
        add(text3);
        add(check1);
        add(check2);
        add(list1);
        add(scroll1);
        add(scroll2);
    }

    /** デストラクタ */
    virtual ~GuiTest() {
        delete(button1);
        delete(label1);
        delete(label2);
        delete(label3);
        delete(text1);
        delete(text2);
        delete(text3);
        delete(check1);
        delete(check2);
        delete(group1);
        delete(list1);
        delete(scroll1);
        delete(scroll2);
    }
};

void HariMain(void) {
    GuiTest* test = new GuiTest();
    test->run();
}
