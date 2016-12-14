#include "../bayos.h"

Task** Scheduler::task_list  = NULL;
List<Task*>* Scheduler::runq = NULL;
Task* Scheduler::current     = NULL;
Task* Scheduler::fpu         = NULL;
bool Scheduler::ready        = false;

/* スケジューラの初期化 */
void Scheduler::init() {
    /* 変数の初期化 */
    Scheduler::task_list = new Task*[MAX_TASKS];
    Scheduler::runq      = new List<Task*>();

    /* タスク一覧の初期化 */
    SegmentDescriptor* gdt = (SegmentDescriptor *) ADDRESS_GDT;
    for (int i = 0; i < MAX_TASKS; i++) {
        Scheduler::task_list[i] = new Task();
        Scheduler::task_list[i]->id       = i;
        Scheduler::task_list[i]->selector = (TASK_GDT_0 + i) * 8;
        Scheduler::task_list[i]->enable   = false;
        Scheduler::task_list[i]->fifo     = new List<Message*>();
        Scheduler::task_list[i]->tss.ldtr = (TASK_GDT_0 + MAX_TASKS + i) * 8;
        /* カーネルタスク用記述子の設定 */
        Descriptor::setSegmentDescriptor
            (gdt + TASK_GDT_0 + i, 103, (int) &Scheduler::task_list[i]->tss, AR_TSS32);
        /* アプリケーション用記述子の設定 */
        Descriptor::setSegmentDescriptor
            (gdt + TASK_GDT_0 + MAX_TASKS + i, 15, (int) Scheduler::task_list[i]->ldt, AR_LDT);
    }

    /* [0]カーネルタスクの設定 */
    Scheduler::current = allocateTask(0, "KERNEL");

    /* [1]アイドルタスクの設定 */
    Task* idle = allocateTask((int) &task_idle, "IDLE");

    /* [2]キーボードタスクの設定 */
    Task* keyboard = allocateTask((int) &task_keyboard, "KEYBOARD");

    /* [3]マウスタスクの設定 */
    Task* mouse = allocateTask((int) &task_mouse, "MOUSE");

    /* [4]コンソールタスクの設定 */
    Task* console = allocateTask((int) &task_console, "CONSOLE");

    /* 実行キューにタスクを詰め込む */
    Scheduler::runq->add(idle);
    Scheduler::runq->add(keyboard);
    Scheduler::runq->add(mouse);
    Scheduler::runq->add(console);
    Scheduler::runq->add(Scheduler::current);

    /* スケジューリング可能 */
    Scheduler::ready = true;
}

/* 空いているタスクの取得 */
Task* Scheduler::allocateTask(int eip, const char* name) {
    for (int i = 0; i < MAX_TASKS; i++) {
        if (Scheduler::task_list[i]->enable == false) {
            Scheduler::task_list[i]->enable = true;
            memcpy(task_list[i]->name, name, strlen(name) + 1);
            if (i == 0) {
                load_tr(Scheduler::task_list[i]->selector);
            } else {
                Scheduler::task_list[i]->tss.esp     = (int) (new byte[64 * 1024] + (64 * 1024));
                Scheduler::task_list[i]->tss.eip     = eip;
                Scheduler::task_list[i]->tss.eflags  = 0x00000202; /* IF = 1; */
                Scheduler::task_list[i]->tss.eax     = 0; /* とりあえず0にしておくことにする */
                Scheduler::task_list[i]->tss.ecx     = 0;
                Scheduler::task_list[i]->tss.edx     = 0;
                Scheduler::task_list[i]->tss.ebx     = 0;
                Scheduler::task_list[i]->tss.ebp     = 0;
                Scheduler::task_list[i]->tss.esi     = 0;
                Scheduler::task_list[i]->tss.edi     = 0;
                Scheduler::task_list[i]->tss.es      = 1 * 8;
                Scheduler::task_list[i]->tss.cs      = 2 * 8;
                Scheduler::task_list[i]->tss.ss      = 1 * 8;
                Scheduler::task_list[i]->tss.ds      = 1 * 8;
                Scheduler::task_list[i]->tss.fs      = 1 * 8;
                Scheduler::task_list[i]->tss.gs      = 1 * 8;
                Scheduler::task_list[i]->tss.iomap   = 0x40000000;
                Scheduler::task_list[i]->tss.ss0     = 0;
                Scheduler::task_list[i]->fpu[0]      = 0x037f; /* CW(control word) */
                Scheduler::task_list[i]->fpu[1]      = 0x0000; /* SW(status word)  */
                Scheduler::task_list[i]->fpu[2]      = 0xffff; /* TW(tag word)     */
            }
            return Scheduler::task_list[i];
        }
    }
    return NULL;
}

/* タスクを殺す */
void Scheduler::killTask(int id) {
    /* カーネルタスクからコンソールタスクまでは殺せない */
    if (TASK_CONSOLE < id && id < MAX_TASKS) {
        Task* task = Scheduler::task_list[id];
        task->enable = false;
        task->fifo->removeAll();
        Scheduler::runq->remove(task);
        switchTask();
    }
}

#if 0
/* タスクを一時的に止める */
void Scheduler::sleepTask(dword ms) {
    if (ms < 10) {
        while (0 < ms--) {
            __asm__ __volatile__ ("outb %%al, $0x80" ::: "%eax");
        }
    } else if (ms < Scheduler::runq->size() * 10) {
        Scheduler::runq->add(Scheduler::runq->remove(Scheduler::current));
        Scheduler::switchTask();
    } else {
        Scheduler::runq->remove(Scheduler::current);
        Scheduler::switchTask();
    }
}
#endif

/* 定期的なタスクスイッチ */
void Scheduler::switchTask() {
    if (Scheduler::ready == false) return;
    Scheduler::current = Scheduler::runq->removeAt(0);
    Scheduler::runq->add(Scheduler::current);
    farjmp(0, Scheduler::current->selector);
}

/* アイドルタスク */
void task_idle(void) {
    for (;;) {
        io_hlt();
    }
}

/* アプリケーション実行タスク */
void task_exec(void) {
    /* 実行中のタスク */
    Task* current = Scheduler::current;

    if (current->fifo->isEmpty() == false) {
        /* アプリケーションファイルの読み込み */
        Message* message = current->fifo->removeAt(0);
        FileEntry* entry = File::load((char *) message->data);
        delete(message);
        dword app_size = entry->size;
        byte* app_code = entry->data;

        /* アプリケーション情報の取得 */
        int seg_size     = *((int *) (app_code + 0x0000));
        int esp          = *((int *) (app_code + 0x000c));
        int data_size    = *((int *) (app_code + 0x0010));
        int data_hrb     = *((int *) (app_code + 0x0014));
        int malloc_start = *((int *) (app_code + 0x0020));

        /* デバッグ用 */
        //Console::printf("%d,%x,%d,%x,%x\n", seg_size, esp, data_size, data_hrb, malloc_start);

        /* データセグメントの確保とアプリケーション用メモリマネージャの初期化 */
        byte* app_data   = new byte[seg_size];
        current->ds_base = (int) app_data;
        current->memory  = new Memory();
        current->memory->init((dword) &app_data[malloc_start], (dword) &app_data[seg_size - 1]);

        /* データセグメントとコードセグメントの設定 */
        Descriptor::setSegmentDescriptor
            (&current->ldt[0], app_size - 1, (int) app_code, AR_CODE32_ER + 0x60);
        Descriptor::setSegmentDescriptor
            (&current->ldt[1], seg_size - 1, (int) app_data, AR_DATA32_RW + 0x60);
        memcpy(&app_data[esp], &app_code[data_hrb], data_size - 1);

        /* 実行開始 */
        start_app(0x1b, 0 * 8 + 4, esp, 1 * 8 + 4, &(current->tss.esp0));

        /* 実行終了 */
        delete(current->memory);
        delete(app_data);
    }

    Scheduler::killTask(current->id);
}


/* キーボードタスク */
void task_keyboard(void) {
    for (;;) {
        List<Message*>* fifo = Scheduler::current->fifo;
        if (fifo->isEmpty() == false) {
            io_cli(); /* 割り込みを禁止する */
            Message* message = fifo->removeAt(0);
            char c = Keyboard::decode(message->arg1);
            Sheet* sheet = SheetCtl::sheets[SheetCtl::top - 1];
            if (sheet->task != NULL) {
                /* コンソールのキー入力 */
                if (Keyboard::state == MSG_KEY_PRESSED && c != 0 && sheet->task->id == TASK_CONSOLE) {
                    //Console::putKey(c);
                    Message::send(TASK_CONSOLE, Message::create(MSG_CONSOLE_PUTKEY,  c));
                }

                /* キーイベント */
                else {
                    Message::send(
                        sheet->task->id, 
                        Message::create(Keyboard::state, (int) sheet, Keyboard::state, message->arg1, c)
                    );
                }
            }
            delete message;
            io_sti(); /* 割り込みを許可する */
        } else {
            /* FIFOが空になったら別のタスクに切り替え */
            Scheduler::switchTask();
        }
    }
}


/* マウスタスク */
void task_mouse(void) {
    bool drag_flag = false;
    int  mx = 0, my = 0;

    for (;;) {
        List<Message*>* fifo = Scheduler::current->fifo;
        if (fifo->isEmpty() == false) {
            io_cli(); /* 割り込みを禁止する */
            Message* message = fifo->removeAt(0);
            if (Mouse::decode(message->arg1) != 0) {
                /* マウスのボタンが押された */
                if (Mouse::state == MSG_MOUSE_PRESSED) {
                    for (int i = SheetCtl::top - 1; i > 0; i--) {
                        Sheet* sheet = SheetCtl::sheets[i];

                        /* 閉じるボタンが押された */
                        if (sheet->vx0 + 4 < Mouse::x && Mouse::x < sheet->vx0 + 17 &&
                                sheet->vy0 + 4 < Mouse::y && Mouse::y < sheet->vy0 + 17 &&
                                    sheet->task != NULL)
                        {
                            /* イベント発生 */
                            Message::send(
                                sheet->task->id, 
                                Message::create(MSG_WINDOW_CLOSE, (int) sheet)
                            );
                            break;
                        }

                        /* タイトルバーが押された */
                        else if (sheet->vx0 < Mouse::x && Mouse::x < sheet->vx0 + sheet->width &&
                                   sheet->vy0 < Mouse::y && Mouse::y < sheet->vy0 + INSETS_TOP)
                        {
                            /* 一番上ならドラッグ対象にする */
                            if (i == SheetCtl::top - 1) {
                                drag_flag = true;
                                mx = Mouse::x - sheet->vx0;
                                my = Mouse::y - sheet->vy0;
                                break;
                            }
                            /* 下敷きを一番上から２番目に引き上げる */
                            if (i < SheetCtl::top - 1) {
                                SheetCtl::updown(sheet, SheetCtl::top - 1);
                                break;
                            }
                        }

                        /* イベント発生 */
                        else if (sheet->vx0 < Mouse::x && Mouse::x < sheet->vx0 + sheet->width &&
                                    sheet->vy0 < Mouse::y && Mouse::y < sheet->vy0 + sheet->height &&
                                        i == SheetCtl::top - 1 && sheet->task != NULL)
                        {
                            mx = Mouse::x - sheet->vx0;
                            my = Mouse::y - sheet->vy0;
                            Message::send(
                                sheet->task->id, 
                                Message::create(MSG_MOUSE_PRESSED, (int) sheet, Mouse::button, mx, my)
                            );
                            break;
                        }
                    }
                }

                /* マウスがドラッグされた */
                else if (Mouse::state == MSG_MOUSE_DRAGGED) {
                    /* 下敷きを動かす */
                    if (drag_flag == true) {
                        Sheet* sheet = SheetCtl::sheets[SheetCtl::top - 1];
                        SheetCtl::slide(sheet, Mouse::x - mx, Mouse::y - my);
                    }

                    /* イベント発生 */
                    else {
                        Sheet* sheet = SheetCtl::sheets[SheetCtl::top - 1];
                        if (sheet->vx0 < Mouse::x && Mouse::x < sheet->vx0 + sheet->width &&
                                sheet->vy0 < Mouse::y && Mouse::y < sheet->vy0 + sheet->height &&
                                    sheet->task != NULL)
                        {
                            mx = Mouse::x - sheet->vx0;
                            my = Mouse::y - sheet->vy0;
                            Message::send(
                                sheet->task->id, 
                                Message::create(MSG_MOUSE_DRAGGED, (int) sheet, Mouse::button, mx, my)
                            );
                        }
                    }
                }

                /* マウスが動いた */
                else if (Mouse::state == MSG_MOUSE_MOVED) {
                    Sheet* sheet = SheetCtl::sheets[SheetCtl::top - 1];
                    if (sheet->vx0 < Mouse::x && Mouse::x < sheet->vx0 + sheet->width &&
                            sheet->vy0 < Mouse::y && Mouse::y < sheet->vy0 + sheet->height &&
                                sheet->task != NULL)
                    {
                        mx = Mouse::x - sheet->vx0;
                        my = Mouse::y - sheet->vy0;
                        Message::send(
                            sheet->task->id, 
                            Message::create(MSG_MOUSE_MOVED, (int) sheet, Mouse::button, mx, my)
                        );
                    }
                }

                /* マウスのボタンが離された */
                else if (Mouse::state == MSG_MOUSE_RELEASED) {
                    /* 下敷きの移動終了 */
                    if (drag_flag == true) {
                        drag_flag = false;
                    }

                    /* イベント発生 */
                    else {
                        Sheet* sheet = SheetCtl::sheets[SheetCtl::top - 1];
                        if (sheet->vx0 < Mouse::x && Mouse::x < sheet->vx0 + sheet->width &&
                                sheet->vy0 < Mouse::y && Mouse::y < sheet->vy0 + sheet->height &&
                                    sheet->task != NULL)
                        {
                            mx = Mouse::x - sheet->vx0;
                            my = Mouse::y - sheet->vy0;
                            Message::send(
                                sheet->task->id, 
                                Message::create(MSG_MOUSE_RELEASED, (int) sheet, Mouse::button, mx, my)
                            );
                        }
                    }
                }
                Mouse::draw();
            }
            delete message;
            io_sti(); /* 割り込みを許可する */
        } else {
            /* FIFOが空になったら別のタスクに切り替え */
            Scheduler::switchTask();
        }
    }
}

/* コンソールタスク */
void task_console(void) {
    Console* console = new Console();
    console->init();
    Scheduler::current->console = console;

    for (;;) {
        List<Message*>* fifo = Scheduler::current->fifo;
        if (fifo->isEmpty() == false) {
            io_cli(); /* 割り込みを禁止する */
            Message* message = fifo->removeAt(0);
            if (message->type == MSG_CONSOLE_PUTKEY) {
                console->put_key(message->arg1);
            }
            delete message;
            io_sti(); /* 割り込みを許可する */
        } else {
            /* FIFOが空になったら別のタスクに切り替え */
            Scheduler::switchTask();
        }
    }
}
