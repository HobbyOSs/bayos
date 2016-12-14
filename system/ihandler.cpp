#include "../bayos.h"

/* �^�C�}�[�n���h�� */
void inthandler20(int *esp) {
    io_out8(PIC0_OCW2, 0x60); /* IRQ-00��t������PIC�ɒʒm */
    Timer::count++;           /* �J�E���g�A�b�v */
    Scheduler::switchTask();  /* 10ms���ƂɃ^�X�N�X�C�b�`���s�� */
    return;
}

/* �L�[�{�[�h�n���h�� */
void inthandler21(int *esp) {
    io_out8(PIC0_OCW2, 0x61);   /* IRQ-01��t������PIC�ɒʒm */
    int data = io_in8(PORT_KEYDAT);
    Message::send(TASK_KEYBOARD, Message::create(MSG_KEYBOARD_RAW_DATA, data));
    return;
}

/* PIC0����̕s���S���荞�ݑ΍� */
void inthandler27(int *esp) {
    io_out8(PIC0_OCW2, 0x67);   /* IRQ-07��t������PIC�ɒʒm */
    return;
}

/* �}�E�X�n���h�� */
void inthandler2c(int *esp) {
    io_out8(PIC1_OCW2, 0x64);   /* IRQ-12��t������PIC1�ɒʒm */
    io_out8(PIC0_OCW2, 0x62);   /* IRQ-02��t������PIC0�ɒʒm */
    int data = io_in8(PORT_KEYDAT);
    Message::send(TASK_MOUSE, Message::create(MSG_MOUSE_RAW_DATA, data));
    return;
}

/* FPU���荞�� */
int *inthandler07(int *esp) {
    Task* current = Scheduler::current;
    io_cli();
    clts();
    if (Scheduler::fpu != current) {
        if (Scheduler::fpu != 0) {
            fnsave(Scheduler::fpu->fpu);
        }
        frstor(current->fpu);
        Scheduler::fpu = current;
    }
    io_sti();
    return 0;
}

/* �X�^�b�N��O */
int *inthandler0d(int *esp) {
    Console::putString("stack exception\n");
    return &(Scheduler::current->tss.esp0); /* �ُ�I�������� */
}

/* ��ʕی��O */
int *inthandler0c(int *esp) {
    Console::putString("general protection\n");
    return &(Scheduler::current->tss.esp0); /* �ُ�I�������� */
}

/* �V�X�e���R�[�� */
int *hrb_api(int edi, int esi, int ebp, int esp, int ebx, int func_num, int ecx, int eax) {
    Task* current = Scheduler::current;
    int ds_base   = current->ds_base;

    /*
      �ۑ��̂��߂�PUSHAD�������ɏ���������
      �V�X�e���R�[���̖߂�l�� reg[7] �ɐݒ肷�邱��
      reg[0] : EDI, reg[1] : ESI, reg[2] : EBP, reg[3] : ESP
      reg[4] : EBX, reg[5] : EDX, reg[6] : ECX, reg[7] : EAX
    */
    int* reg = &eax + 1;

    if (func_num == API_PUTCHAR) {
        Console::putChar(eax & 0xff);
    } else if (func_num == API_PUTSTR0) {
        char* s = (char *) ebx + ds_base;
        Console::putString(s);
    } else if (func_num == API_PUTSTR1) {
        char* s = (char *) ebx + ds_base;
        for (int i = 0; i <= ecx; i++) {
            Console::putChar(s[i] & 0xff);
        }
    } else if (func_num == API_END) {
        return &(current->tss.esp0);
    } else if (func_num == API_OPENWIN) {
        byte* buffer = (byte *) ebx + ds_base;
        int w = esi;
        int h = edi;
        int transparent = eax;
        char* title = (char *) ecx + ds_base;
        Sheet* sheet = SheetCtl::allocate();
        SheetCtl::setbuf(sheet, (word *) buffer, w, h, transparent);
        sheet->vx0 = (SheetCtl::xsize - w) / 2;
        sheet->vy0 = (SheetCtl::ysize - h) / 2;
        SheetCtl::drawFrame(sheet, title);
        SheetCtl::updown(sheet, SheetCtl::top);
        reg[7] = (int) sheet;
    } else if (func_num == API_PUTSTRWIN) {
        Sheet* sheet = (Sheet *) ebx;
        int x   = esi;
        int y   = edi;
        int col = eax & 0xffff;
        char* s = (char *) ebp + ds_base;
        SheetCtl::drawString(sheet, s, x, y, col);
    } else if (func_num == API_BOXFILWIN) {
        Sheet* sheet = (Sheet *) ebx;
        int x0  = eax;
        int y0  = ecx;
        int x1  = esi;
        int y1  = edi;
        int col = ebp;
        SheetCtl::fillRect(sheet, x0, y0, x1, y1, col);
    } else if (func_num == API_INITMALLOC) {
        // �������Ȃ�
    } else if (func_num == API_MALLOC) {
        void* addr = current->memory->allocate(ecx);
        reg[7] = ((int) addr) - ds_base;
    } else if (func_num == API_FREE) {
        dword* addr = (dword *) eax + ds_base;
        current->memory->free(addr);
    } else if (func_num == API_POINT) {
        Sheet* sheet = (Sheet *) ebx;
        int x0  = esi;
        int y0  = edi;
        int col = eax;
        SheetCtl::drawPixel(sheet, x0, y0, col);
    } else if (func_num == API_REFRESHWIN) {
        Sheet* sheet = (Sheet *) ebx;
        int x0 = eax;
        int y0 = ecx;
        int x1 = esi;
        int y1 = edi;
        SheetCtl::refresh(sheet, x0, y0, x1, y1);
    } else if (func_num == API_LINEWIN) {
        Sheet* sheet = (Sheet *) ebx;
        int x0  = eax;
        int y0  = ecx;
        int x1  = esi;
        int y1  = edi;
        int col = ebp;
        SheetCtl::drawLine(sheet, x0, y0, x1, y1, col);
    } else if (func_num == API_CLOSEWIN) {
        Sheet* sheet = (Sheet *) ebx;
        SheetCtl::dispose(sheet);
    } else if (func_num == API_GETKEY) {
        #if 0
        if (Scheduler::task_list[TASK_IDLE]->fifo->isEmpty() == false) {
            Message* message = Scheduler::task_list[TASK_IDLE]->fifo->removeAt(0);
            reg[7] = message->arg1;
            delete(message);
        } else {
            reg[7] = 0;
        }
        #endif
        reg[7] = 0;
    } else if (func_num == API_ALLOCTIMER) {
        // �������Ȃ�
    } else if (func_num == API_INITTIMER) {
        // �������Ȃ�
    } else if (func_num == API_SETTIMER) {
        // �������Ȃ�
    } else if (func_num == API_FREETIMER) {
        // �������Ȃ�
    } else if (func_num == API_BEEP) {
        Beep::tone(eax);
    } else if (func_num == API_FOPEN) {
        char* s = (char *) ebx + ds_base;
        FileEntry* entry = File::load(s);
        reg[7] = (int) entry;
    } else if (func_num == API_FCLOSE) {
        // �������Ȃ�
    } else if (func_num == API_FSIZE) {
        FileEntry* entry = (FileEntry *) eax;
        if (entry != NULL) {
            reg[7] = entry->size;
        } else {
            reg[7] = 0;
        }
    } else if (func_num == API_FSEEK) {
        // �������Ȃ�
    } else if (func_num == API_FREAD) {
        char* s = (char *) ebx + ds_base;
        int maxsize = ecx;
        FileEntry* entry = (FileEntry *) eax;
        if (entry != NULL) {
            memcpy(s, entry->data, maxsize);
            reg[7] = entry->size;
        } else {
            reg[7] = 0;
        }
    } else if (func_num == API_CMDLINE) {
        // �������Ȃ�
    } else if (func_num == API_GETLANG) {
        // �������Ȃ�
    } else if (func_num == TOMO_GETMOUSE) {
        int tx, ty;
        /* ��ʂ̍��ォ��̐�΍��W */
        if (ebx == 0) {
            tx = ty = 0;
        }
        /* ���~���̍��ォ��̑��΍��W */
        else {
            Sheet* sheet = (Sheet *) ebx;
            tx = sheet->vx0;
            ty = sheet->vy0;
        }
        /* �}�E�X���̐ݒ� */
        MOUSE_INFO* info = (MOUSE_INFO *) (ecx + ds_base);
        info->x = Mouse::x - tx;
        info->y = Mouse::y - ty;
        info->button = Mouse::button;
        info->state  = Mouse::state;
    } else if (func_num == TOMO_GETTICK) {
        reg[7] = Timer::count;
    } else if (func_num == TOMO_RDMSR) {
        // �������Ȃ�
    } else if (func_num == TOMO_SETLANG) {
        // �������Ȃ�
    } else if (func_num == TOMO_SYSINFO) {
        BOOT_PARAM *boot_param = (BOOT_PARAM *) ADR_BOOTINFO;
        SYS_INFO* info = (SYS_INFO *) (eax + ds_base);
        info->cyls = boot_param->cyls;
        info->leds = boot_param->leds;
        info->bpps = boot_param->bpps;
        info->reserve  = boot_param->reserve;
        info->screen_x = boot_param->screen_x;
        info->screen_y = boot_param->screen_y;
        info->vram = boot_param->vram;
        info->os_type = 3; /* BayOS */
    } else if (func_num == TOMO_SYSTIME) {
        RTC::init();
        TIME_INFO* info = (TIME_INFO *) (eax + ds_base);
        info->year    = RTC::year;
        info->month   = RTC::month;
        info->day     = RTC::day;
        info->hour    = RTC::hour;
        info->minutes = RTC::minutes;
        info->second  = RTC::second;
    } else if (func_num == TOMO_WRMSR) {
        // �������Ȃ�
    } else if (func_num == BAYOS_THREAD_ID) {
        reg[7] = Scheduler::current->id;
    } else if (func_num == BAYOS_THREAD_JOIN) {
        // �������Ȃ�
    } else if (func_num == BAYOS_THREAD_KILL) {
        Scheduler::killTask(eax);
    } else if (func_num == BAYOS_THREAD_YIELD) {
        Scheduler::switchTask();
    } else if (func_num == BAYOS_MESG_SEND) {
        MSG_INFO* info = (MSG_INFO *) (ecx + ds_base);
        Message* message = Message::create(
            info->type, 
            info->arg1, 
            info->arg2, 
            info->arg3, 
            info->arg4, 
            info->len, 
            info->data
        );
        Message::send(ebx, message);
    } else if (func_num == BAYOS_MESG_RECEIVE) {
        MSG_INFO* info = (MSG_INFO *) (eax + ds_base);
        List<Message*>* fifo = current->fifo;
        if (fifo->isEmpty() == false) {
            Message* message = fifo->removeAt(0);
            info->type = message->type;
            info->from = message->from;
            info->arg1 = message->arg1;
            info->arg2 = message->arg2;
            info->arg3 = message->arg3;
            info->arg4 = message->arg4;
            info->len  = message->len;
            /* �A�v���P�[�V������Ԃւ̃f�[�^�R�s�[ */
            if (info->len > 0 && info->data != NULL) {
                current->memory->free((byte *) info->data + ds_base);
            }
            info->data = (byte *) current->memory->allocate(message->len) + ds_base;
            memcpy((byte *) info->data + ds_base, message->data, message->len);
            delete message;
            reg[7] = 1;
        } else {
            reg[7] = 0;
        }
    } else if (func_num == BAYOS_GET_WSTR_INFO) {
        char* str = (char *) (ebx + ds_base);
        WSTR_INFO* info = (WSTR_INFO *) (ecx + ds_base);
        SheetCtl::drawString(NULL, str, 0, 0, 0);
        info->width  = SheetCtl::wstrinfo->width;
        info->height = SheetCtl::wstrinfo->height;
        info->length = SheetCtl::wstrinfo->length;
    }

    return 0; /* 0�ȊO���Ԃ�ƃA�v���������I������� */
}
