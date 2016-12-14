#include "../bayos.h"

Task** Scheduler::task_list  = NULL;
List<Task*>* Scheduler::runq = NULL;
Task* Scheduler::current     = NULL;
Task* Scheduler::fpu         = NULL;
bool Scheduler::ready        = false;

/* �X�P�W���[���̏����� */
void Scheduler::init() {
    /* �ϐ��̏����� */
    Scheduler::task_list = new Task*[MAX_TASKS];
    Scheduler::runq      = new List<Task*>();

    /* �^�X�N�ꗗ�̏����� */
    SegmentDescriptor* gdt = (SegmentDescriptor *) ADDRESS_GDT;
    for (int i = 0; i < MAX_TASKS; i++) {
        Scheduler::task_list[i] = new Task();
        Scheduler::task_list[i]->id       = i;
        Scheduler::task_list[i]->selector = (TASK_GDT_0 + i) * 8;
        Scheduler::task_list[i]->enable   = false;
        Scheduler::task_list[i]->fifo     = new List<Message*>();
        Scheduler::task_list[i]->tss.ldtr = (TASK_GDT_0 + MAX_TASKS + i) * 8;
        /* �J�[�l���^�X�N�p�L�q�q�̐ݒ� */
        Descriptor::setSegmentDescriptor
            (gdt + TASK_GDT_0 + i, 103, (int) &Scheduler::task_list[i]->tss, AR_TSS32);
        /* �A�v���P�[�V�����p�L�q�q�̐ݒ� */
        Descriptor::setSegmentDescriptor
            (gdt + TASK_GDT_0 + MAX_TASKS + i, 15, (int) Scheduler::task_list[i]->ldt, AR_LDT);
    }

    /* [0]�J�[�l���^�X�N�̐ݒ� */
    Scheduler::current = allocateTask(0, "KERNEL");

    /* [1]�A�C�h���^�X�N�̐ݒ� */
    Task* idle = allocateTask((int) &task_idle, "IDLE");

    /* [2]�L�[�{�[�h�^�X�N�̐ݒ� */
    Task* keyboard = allocateTask((int) &task_keyboard, "KEYBOARD");

    /* [3]�}�E�X�^�X�N�̐ݒ� */
    Task* mouse = allocateTask((int) &task_mouse, "MOUSE");

    /* [4]�R���\�[���^�X�N�̐ݒ� */
    Task* console = allocateTask((int) &task_console, "CONSOLE");

    /* ���s�L���[�Ƀ^�X�N���l�ߍ��� */
    Scheduler::runq->add(idle);
    Scheduler::runq->add(keyboard);
    Scheduler::runq->add(mouse);
    Scheduler::runq->add(console);
    Scheduler::runq->add(Scheduler::current);

    /* �X�P�W���[�����O�\ */
    Scheduler::ready = true;
}

/* �󂢂Ă���^�X�N�̎擾 */
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
                Scheduler::task_list[i]->tss.eax     = 0; /* �Ƃ肠����0�ɂ��Ă������Ƃɂ��� */
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

/* �^�X�N���E�� */
void Scheduler::killTask(int id) {
    /* �J�[�l���^�X�N����R���\�[���^�X�N�܂ł͎E���Ȃ� */
    if (TASK_CONSOLE < id && id < MAX_TASKS) {
        Task* task = Scheduler::task_list[id];
        task->enable = false;
        task->fifo->removeAll();
        Scheduler::runq->remove(task);
        switchTask();
    }
}

#if 0
/* �^�X�N���ꎞ�I�Ɏ~�߂� */
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

/* ����I�ȃ^�X�N�X�C�b�` */
void Scheduler::switchTask() {
    if (Scheduler::ready == false) return;
    Scheduler::current = Scheduler::runq->removeAt(0);
    Scheduler::runq->add(Scheduler::current);
    farjmp(0, Scheduler::current->selector);
}

/* �A�C�h���^�X�N */
void task_idle(void) {
    for (;;) {
        io_hlt();
    }
}

/* �A�v���P�[�V�������s�^�X�N */
void task_exec(void) {
    /* ���s���̃^�X�N */
    Task* current = Scheduler::current;

    if (current->fifo->isEmpty() == false) {
        /* �A�v���P�[�V�����t�@�C���̓ǂݍ��� */
        Message* message = current->fifo->removeAt(0);
        FileEntry* entry = File::load((char *) message->data);
        delete(message);
        dword app_size = entry->size;
        byte* app_code = entry->data;

        /* �A�v���P�[�V�������̎擾 */
        int seg_size     = *((int *) (app_code + 0x0000));
        int esp          = *((int *) (app_code + 0x000c));
        int data_size    = *((int *) (app_code + 0x0010));
        int data_hrb     = *((int *) (app_code + 0x0014));
        int malloc_start = *((int *) (app_code + 0x0020));

        /* �f�o�b�O�p */
        //Console::printf("%d,%x,%d,%x,%x\n", seg_size, esp, data_size, data_hrb, malloc_start);

        /* �f�[�^�Z�O�����g�̊m�ۂƃA�v���P�[�V�����p�������}�l�[�W���̏����� */
        byte* app_data   = new byte[seg_size];
        current->ds_base = (int) app_data;
        current->memory  = new Memory();
        current->memory->init((dword) &app_data[malloc_start], (dword) &app_data[seg_size - 1]);

        /* �f�[�^�Z�O�����g�ƃR�[�h�Z�O�����g�̐ݒ� */
        Descriptor::setSegmentDescriptor
            (&current->ldt[0], app_size - 1, (int) app_code, AR_CODE32_ER + 0x60);
        Descriptor::setSegmentDescriptor
            (&current->ldt[1], seg_size - 1, (int) app_data, AR_DATA32_RW + 0x60);
        memcpy(&app_data[esp], &app_code[data_hrb], data_size - 1);

        /* ���s�J�n */
        start_app(0x1b, 0 * 8 + 4, esp, 1 * 8 + 4, &(current->tss.esp0));

        /* ���s�I�� */
        delete(current->memory);
        delete(app_data);
    }

    Scheduler::killTask(current->id);
}


/* �L�[�{�[�h�^�X�N */
void task_keyboard(void) {
    for (;;) {
        List<Message*>* fifo = Scheduler::current->fifo;
        if (fifo->isEmpty() == false) {
            io_cli(); /* ���荞�݂��֎~���� */
            Message* message = fifo->removeAt(0);
            char c = Keyboard::decode(message->arg1);
            Sheet* sheet = SheetCtl::sheets[SheetCtl::top - 1];
            if (sheet->task != NULL) {
                /* �R���\�[���̃L�[���� */
                if (Keyboard::state == MSG_KEY_PRESSED && c != 0 && sheet->task->id == TASK_CONSOLE) {
                    //Console::putKey(c);
                    Message::send(TASK_CONSOLE, Message::create(MSG_CONSOLE_PUTKEY,  c));
                }

                /* �L�[�C�x���g */
                else {
                    Message::send(
                        sheet->task->id, 
                        Message::create(Keyboard::state, (int) sheet, Keyboard::state, message->arg1, c)
                    );
                }
            }
            delete message;
            io_sti(); /* ���荞�݂������� */
        } else {
            /* FIFO����ɂȂ�����ʂ̃^�X�N�ɐ؂�ւ� */
            Scheduler::switchTask();
        }
    }
}


/* �}�E�X�^�X�N */
void task_mouse(void) {
    bool drag_flag = false;
    int  mx = 0, my = 0;

    for (;;) {
        List<Message*>* fifo = Scheduler::current->fifo;
        if (fifo->isEmpty() == false) {
            io_cli(); /* ���荞�݂��֎~���� */
            Message* message = fifo->removeAt(0);
            if (Mouse::decode(message->arg1) != 0) {
                /* �}�E�X�̃{�^���������ꂽ */
                if (Mouse::state == MSG_MOUSE_PRESSED) {
                    for (int i = SheetCtl::top - 1; i > 0; i--) {
                        Sheet* sheet = SheetCtl::sheets[i];

                        /* ����{�^���������ꂽ */
                        if (sheet->vx0 + 4 < Mouse::x && Mouse::x < sheet->vx0 + 17 &&
                                sheet->vy0 + 4 < Mouse::y && Mouse::y < sheet->vy0 + 17 &&
                                    sheet->task != NULL)
                        {
                            /* �C�x���g���� */
                            Message::send(
                                sheet->task->id, 
                                Message::create(MSG_WINDOW_CLOSE, (int) sheet)
                            );
                            break;
                        }

                        /* �^�C�g���o�[�������ꂽ */
                        else if (sheet->vx0 < Mouse::x && Mouse::x < sheet->vx0 + sheet->width &&
                                   sheet->vy0 < Mouse::y && Mouse::y < sheet->vy0 + INSETS_TOP)
                        {
                            /* ��ԏ�Ȃ�h���b�O�Ώۂɂ��� */
                            if (i == SheetCtl::top - 1) {
                                drag_flag = true;
                                mx = Mouse::x - sheet->vx0;
                                my = Mouse::y - sheet->vy0;
                                break;
                            }
                            /* ���~������ԏォ��Q�ԖڂɈ����グ�� */
                            if (i < SheetCtl::top - 1) {
                                SheetCtl::updown(sheet, SheetCtl::top - 1);
                                break;
                            }
                        }

                        /* �C�x���g���� */
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

                /* �}�E�X���h���b�O���ꂽ */
                else if (Mouse::state == MSG_MOUSE_DRAGGED) {
                    /* ���~���𓮂��� */
                    if (drag_flag == true) {
                        Sheet* sheet = SheetCtl::sheets[SheetCtl::top - 1];
                        SheetCtl::slide(sheet, Mouse::x - mx, Mouse::y - my);
                    }

                    /* �C�x���g���� */
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

                /* �}�E�X�������� */
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

                /* �}�E�X�̃{�^���������ꂽ */
                else if (Mouse::state == MSG_MOUSE_RELEASED) {
                    /* ���~���̈ړ��I�� */
                    if (drag_flag == true) {
                        drag_flag = false;
                    }

                    /* �C�x���g���� */
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
            io_sti(); /* ���荞�݂������� */
        } else {
            /* FIFO����ɂȂ�����ʂ̃^�X�N�ɐ؂�ւ� */
            Scheduler::switchTask();
        }
    }
}

/* �R���\�[���^�X�N */
void task_console(void) {
    Console* console = new Console();
    console->init();
    Scheduler::current->console = console;

    for (;;) {
        List<Message*>* fifo = Scheduler::current->fifo;
        if (fifo->isEmpty() == false) {
            io_cli(); /* ���荞�݂��֎~���� */
            Message* message = fifo->removeAt(0);
            if (message->type == MSG_CONSOLE_PUTKEY) {
                console->put_key(message->arg1);
            }
            delete message;
            io_sti(); /* ���荞�݂������� */
        } else {
            /* FIFO����ɂȂ�����ʂ̃^�X�N�ɐ؂�ւ� */
            Scheduler::switchTask();
        }
    }
}
