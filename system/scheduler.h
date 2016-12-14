#ifndef _SYSTEM_SCHEDULER_H_INCLUDED_
#define _SYSTEM_SCHEDULER_H_INCLUDED_

#define MAX_TASKS       256   /* 最大タスク数 */
#define TASK_GDT_0      3     /* TSSをGDTの何番から割り当てるのか */
#define TASK_KERNEL     0     /* カーネルタスクの番号 */
#define TASK_IDLE       1     /* アイドルタスクの番号 */
#define TASK_KEYBOARD   2     /* キーボードタスクの番号 */
#define TASK_MOUSE      3     /* マウスタスクの番号 */
#define TASK_CONSOLE    4     /* コンソールタスクの番号 */

/* C言語の関数宣言 */
extern "C" {
    /* アイドルタスク */
    void task_idle(void);

    /* アプリ実行タスク */
    void task_exec(void);

    /* キーボードタスク */
    void task_keyboard(void);

    /* マウスタスク */
    void task_mouse(void);

    /* コンソールタスク */
    void task_console(void);
}

namespace system {
    /* 32ビットTSS */
    class TSS32 {
    public:
        int backlink, esp0, ss0, esp1, ss1, esp2, ss2, cr3;
        int eip, eflags, eax, ecx, edx, ebx, esp, ebp, esi, edi;
        int es, cs, ss, ds, fs, gs;
        int ldtr, iomap;
    };

    class Console;

    /* タスク */
    class Task {
    public:
        int   id;             /* タスクID */
        int   selector;       /* GDTの番号 */
        bool  enable;         /* 動作フラグ */
        char  name[16];       /* タスク名 */
        TSS32 tss;            /* 32ビットTSS */
        int   ds_base;        /* データセグメント開始アドレス */
        int   fpu[108 / 4];   /* FPUレジスタ */
        List<Message*>* fifo; /* FIFOバッファ */
        Memory*  memory;      /* アプリ用メモリマネージャ */
        Console* console;     /* コンソール */
        SegmentDescriptor ldt[2]; /* ローカル記述子 */
    };

    /* タスクスケジューラ */
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
