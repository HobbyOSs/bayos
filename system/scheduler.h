#ifndef _SYSTEM_SCHEDULER_H_INCLUDED_
#define _SYSTEM_SCHEDULER_H_INCLUDED_

#define MAX_TASKS       256   /* �ő�^�X�N�� */
#define TASK_GDT_0      3     /* TSS��GDT�̉��Ԃ��犄�蓖�Ă�̂� */
#define TASK_KERNEL     0     /* �J�[�l���^�X�N�̔ԍ� */
#define TASK_IDLE       1     /* �A�C�h���^�X�N�̔ԍ� */
#define TASK_KEYBOARD   2     /* �L�[�{�[�h�^�X�N�̔ԍ� */
#define TASK_MOUSE      3     /* �}�E�X�^�X�N�̔ԍ� */
#define TASK_CONSOLE    4     /* �R���\�[���^�X�N�̔ԍ� */

/* C����̊֐��錾 */
extern "C" {
    /* �A�C�h���^�X�N */
    void task_idle(void);

    /* �A�v�����s�^�X�N */
    void task_exec(void);

    /* �L�[�{�[�h�^�X�N */
    void task_keyboard(void);

    /* �}�E�X�^�X�N */
    void task_mouse(void);

    /* �R���\�[���^�X�N */
    void task_console(void);
}

namespace system {
    /* 32�r�b�gTSS */
    class TSS32 {
    public:
        int backlink, esp0, ss0, esp1, ss1, esp2, ss2, cr3;
        int eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
        int es, cs, ss, ds, fs, gs;
        int ldtr, iomap;
    };

    class Console;

    /* �^�X�N */
    class Task {
    public:
        int   id;             /* �^�X�NID */
        int   selector;       /* GDT�̔ԍ� */
        bool  enable;         /* ����t���O */
        char  name[16];       /* �^�X�N�� */
        TSS32 tss;            /* 32�r�b�gTSS */
        int   ds_base;        /* �f�[�^�Z�O�����g�J�n�A�h���X */
        int   fpu[108 / 4];   /* FPU���W�X�^ */
        List<Message*>* fifo; /* FIFO�o�b�t�@ */
        Memory*  memory;      /* �A�v���p�������}�l�[�W�� */
        Console* console;     /* �R���\�[�� */
        SegmentDescriptor ldt[2]; /* ���[�J���L�q�q */
    };

    /* �^�X�N�X�P�W���[�� */
    class Scheduler {
    public:
        static Task** task_list;
        static List<Task*>* runq;
        static Task* current;
        static Task* fpu;
        static bool ready;

    public:
        static void  init(void);
        static Task* allocateTask(int eip, const char* name);
        static void  killTask(int id);
        static void  switchTask(void);
    };
}

#endif
