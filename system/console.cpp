#include "../bayos.h"
#include <stdio.h>

/* 背景色（白）*/
#define cb 0xffff
/* 前景色（黒）*/
#define cc 0x0000

/* 初期化する */
void Console::init() {
    /* 描画開始位置を初期化 */
    cx = INSETS_LEFT;
    cy = INSETS_TOP;
    cw = FONT_W * 58 + INSETS_LEFT + INSETS_RIGHT;
    ch = FONT_H * 17 + INSETS_TOP  + INSETS_BOTTOM;

    /* コマンドバッファーを初期化 */
    cmd_buf = new char[128];

    /* printf用バッファーを初期化 */
    //prt_buf = new char[128];

    /* 下敷きを初期化 */
    sheet = SheetCtl::allocate();
    SheetCtl::setbuf(sheet, (word *) malloc (cw * ch * sizeof(short)), cw, ch, -1);
    sheet->vx0 = (SheetCtl::xsize - cw) / 2;
    sheet->vy0 = (SheetCtl::ysize - ch) / 2;
    vram       = sheet->buffer;

    /* 枠を描画する */
    SheetCtl::drawFrame(sheet, "console");

    /* コンソール領域を背景色で塗りつぶす */
    SheetCtl::fillRect(
        sheet,
        INSETS_LEFT,
        INSETS_TOP,
        cw - INSETS_LEFT - INSETS_RIGHT,
        ch - INSETS_TOP  - INSETS_BOTTOM,
        WHITE
    );

    /* 下敷きリストに追加 */
    SheetCtl::updown(sheet, 1);

    drawPrompt(); /* プロンプトを描画*/
    drawCarret(); /* キャレットを描画 */
}

/* 描画開始位置を変更する */
void Console::locate(int x, int y) {
    cx = x;
    cy = y;
    if (cx >= cw - INSETS_RIGHT) {
        cy += FONT_H;
        cx = INSETS_LEFT;
    }
    if (cy >= ch - INSETS_BOTTOM) {
        cy = ch - INSETS_BOTTOM - FONT_H;
        cx = INSETS_LEFT;

        /* 1行スクロール */
        memcpy(
            &vram[cw * INSETS_TOP],
            &vram[cw * (INSETS_TOP + FONT_H)],
            cw * (ch - 28 - FONT_H) * sizeof(short)
        );

        /* スクロール後の最終行を背景色で塗りつぶす */
        SheetCtl::fillRect(
            sheet,
            INSETS_LEFT,
            ch - INSETS_BOTTOM - FONT_H,
            cw - INSETS_LEFT - INSETS_RIGHT,
            FONT_H,
            WHITE
        );
        SheetCtl::refresh(sheet, 0, 0, cw, ch);
    }
}

/* コマンドを解析する */
void Console::parseCommand() {
    /* 入力を促す */
    if (strlen(cmd_buf) == 0) {
        drawPrompt(); /* プロンプトを描画*/
        return;
    }

    /* help, ? */
    else if (strncmp(cmd_buf, "help", 4) == 0 || strncmp(cmd_buf, "?", 1) == 0) {
        put_string("CUI cosole command list\n");
        put_string("  help/?    - this command\n");
        put_string("  a:        - switch to floppy\n");
        put_string("  d:        - switch to CD-ROM\n");
        put_string("  ls/dir    - print files\n");
        put_string("  cat/type  - print file\n");
        put_string("  date/time - print current time\n");
        put_string("  uname/ver - print current version\n");
        put_string("  clear/cls - clear screen\n");
        put_string("  ps        - print all processes\n");
        put_string("  mem       - print current memory\n");
    }

    /* a: */
    else if (strncmp(cmd_buf, "a:", 2) == 0) {
        File::type = FS_TYPE_FAT12;
    }

    /* d: */
    else if (strncmp(cmd_buf, "d:", 2) == 0) {
        File::type = FS_TYPE_ISO9660;

        /* test */
        #if 0
        int devices = reg_config();
        printf("devices = %d\n", devices);
        int dev = 0; /* Secondary Primary */
        printf("result = %d\n", reg_reset(dev));

        memset(buffer, 0, 4096);
        memset(cdb, 0, 12);
        printf("result2 = %d\n", reg_pio_data_in_lba28(dev, CMD_IDENTIFY_DEVICE_PACKET, 0, 0, 0L /* lba */, buffer, 1L, 0));
        printf( "   data read %02x%02x%02x%02x %02x%02x%02x%02x "
                             "%02x%02x%02x%02x %02x%02x%02x%02x\n",
                 buffer[ 0], buffer[ 1], buffer[ 2], buffer[ 3],
                 buffer[ 4], buffer[ 5], buffer[ 6], buffer[ 7],
                 buffer[ 8], buffer[ 9], buffer[10], buffer[11],
                 buffer[12], buffer[13], buffer[14], buffer[15] );

        byte cdb[12];

        /* 基本ボリューム記述子の読み込み */
        PrimaryVolumeDescriptor* pvd = new PrimaryVolumeDescriptor;
        memset(cdb, 0, 12);
        cdb[0] = 0x28;
        cdb[5] = 16; /* lba */
        cdb[8] = 1; /* sectors */
        printf("result = %d\n", reg_packet(dev, 12, &cdb[0], 0, sizeof(PrimaryVolumeDescriptor), (byte *) pvd));
        printf("type = %d, id = %s\n", pvd->type[0], pvd->id);
        if (pvd->type[0] != ISO_PRIMARY_VOLUME_DESCRIPTOR || strncmp("CD001", pvd->id, 5) != 0) {
            put_string("PrimaryVolumeDescriptor not found.\n");
            return;
        }

        /* ルートディレクトリを読み込む */
        DirectoryEntry* root = (DirectoryEntry *)( pvd->root_directory_record );

        dword size = ((dword)((root->size_l + ATAPI_SECTOR_SIZE - 1) / ATAPI_SECTOR_SIZE)) * ATAPI_SECTOR_SIZE;
        printf("size_l = %d, extent_l = %d, sectors = %d\n", root->size_l, root->extent_l, ((root->size_l + ATAPI_SECTOR_SIZE - 1) / ATAPI_SECTOR_SIZE));

        byte* buffer = new byte[size];
        memset(cdb, 0, 12);
        cdb[0] = 0x28;
        cdb[5] = root->extent_l; /* lba */
        cdb[8] = ((root->size_l + ATAPI_SECTOR_SIZE - 1) / ATAPI_SECTOR_SIZE); /* sectors */
        printf("result = %d\n", reg_packet(dev, 12, &cdb[0], 0, size, buffer));
        
        /* ディレクトリの内容を表示 */
        for (dword position = 0; position < size;) {
            DirectoryEntry* dir = (DirectoryEntry *) (buffer + position);
            if (dir->size_l == 0) {
                break;
            } else if (dir->directory == 0) {
                FileEntry* entry = new FileEntry();
                entry->size = dir->size_l;
                entry->addr = dir->extent_l;
                entry->data = NULL;
                /* ファイル名の後につく";1"（バージョン番号）を削除 */
                memcpy(entry->name, dir->name, dir->name_len - 2);
                printf("size = %d, addr = %d, name = %s\n", entry->size, entry->addr, entry->name);
            }
            position += dir->length;
        }
        #endif
    }

    /* ls, dir */
    else if (strncmp(cmd_buf, "ls", 2) == 0 || strncmp(cmd_buf, "dir", 3) == 0) {
        List<FileEntry*>* list = File::list();
        int I = list->size();
        int total_size = 0;
        for (int i = 0; i < I; i++) {
            FileEntry* info = list->get(i);
            printf("%8d %13s\n", info->size, info->name);
            total_size += info->size;
        }
        printf("    %3d files %8d byte\n", I, total_size);
    }

    /* cat, type */
    else if (strncmp(cmd_buf, "cat ", 4) == 0 || strncmp(cmd_buf, "type ", 5) == 0) {
        char* filename;
        if (strncmp(cmd_buf, "cat ", 4) == 0) {
            filename = &cmd_buf[4];
        } else {
            filename = &cmd_buf[5];
        }
        if (strlen(filename) > 0) {
            FileEntry* entry = File::load(filename);
            dword read_size  = entry->size;
            if (read_size > 0) {
                for (int i = 0; i < (int) read_size; i++) {
                    if (entry->data[i] != '\r') {
                        put_char(entry->data[i]);
                    }
                }
            }
            put_char('\n');
        }
    }

    /* date, time */
    else if (strncmp(cmd_buf, "date", 4) == 0 || strncmp(cmd_buf, "time", 4) == 0) {
        const char* day [] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
        const char* ampm[] = { "AM", "PM" };

        RTC::init(); /* リアルタイムクロックの初期化 */

        /* ツェラーの公式 */
        int day_of_week = (
                              RTC::year +
                              int(RTC::year/4) -
                              int(RTC::year/100) +
                              int(RTC::year/400) +
                              int((13 * RTC::month + 8)/5) +
                              RTC::day
                          ) % 7;

        printf("%04d/%02d/%02d (%s) %s %02d:%02d:%02d\n",
               RTC::year,
               RTC::month,
               RTC::day,
               day[day_of_week % 7],
               ampm[RTC::hour / 12],
               RTC::hour % 12,
               RTC::minutes, RTC::second
              );
    }

    /* uname, ver */
    else if (strncmp(cmd_buf, "uname", 5) == 0 || strncmp(cmd_buf, "ver", 3) == 0) {
        printf("%s\n", BAYOS_VERSION);
    }

    /* clear, cls */
    else if (strncmp(cmd_buf, "clear", 5) == 0 || strncmp(cmd_buf, "cls", 3) == 0) {
        locate(INSETS_LEFT, INSETS_TOP);
        SheetCtl::fillRect(
            sheet,
            INSETS_LEFT,
            INSETS_TOP,
            cw - INSETS_LEFT - INSETS_RIGHT,
            ch - INSETS_TOP  - INSETS_BOTTOM,
            WHITE
        );
        SheetCtl::refresh(sheet, 0, 0, cw, ch);
        drawPrompt(); /* プロンプトを描画*/
        return;
    }

    /* ps */
    else if (strncmp(cmd_buf, "ps", 2) == 0) {
        put_string("[tid]  [eip]    [esp]    [name]\n");
        for (int i = 0; i < Scheduler::runq->size(); i++) {
            Task* task = Scheduler::runq->get(i);
            printf("%05d %08x %08x %s\n",
                   task->selector,
                   task->tss.eip,
                   task->tss.esp,
                   task->name
                  );
        }
    }

    /* mem */
    else if (strncmp(cmd_buf, "mem", 3) == 0) {
        printf("physical : %8d byte\n", g_km.getTotalSize());
        printf("    free : %8d byte\n", g_km.getFreeSize());
        printf("    used : %8d byte\n", (g_km.getTotalSize() - g_km.getFreeSize()));
    }

    /* 外部アプリ実行 */
    else {
        /* アプリ実行フラグ */
        bool do_exec = false;

        FileEntry* entry = File::load(cmd_buf);
        if (entry != NULL &&
                entry->size >= 36 &&
                strncmp((char *) (entry->data + 4), "Hari", 4) == 0 &&
                *(entry->data) == 0x00) {
            do_exec = true;
        } else {
            strcat(cmd_buf, ".hrb");
            entry = File::load(cmd_buf);
            if (entry != NULL &&
                    entry->size >= 36 &&
                    strncmp((char *) (entry->data + 4), "Hari", 4) == 0 &&
                    *(entry->data) == 0x00) {
                do_exec = true;
            }
        }
        if (do_exec == true) {
            Task* exec = Scheduler::allocateTask((int) &task_exec, cmd_buf);
            exec->console = this;
            Message::send(exec->id, Message::create(0, 0, 0, 0, 0, strlen(cmd_buf) + 1, (byte *) cmd_buf));
            Scheduler::runq->add(exec);
        } else {
            put_string("command not found!\n");
        }
    }

    drawPrompt(); /* プロンプトを描画*/
}

/* 1文字分の背景を復元する */
void Console::restoreChar() {
    /* 塗りつぶし */
    SheetCtl::fillRect(
        sheet,
        cx,
        cy,
        FONT_W * 2,
        FONT_H,
        WHITE
    );

    /* 部分再描画 */
    SheetCtl::refresh(
        sheet,
        cx,
        cy,
        cx + (FONT_W * 2) + 1,
        cy + FONT_H + 1
    );
}

/* プロンプトを書く */
void Console::drawPrompt() {
    if (File::type == FS_TYPE_FAT12) {
        put_string("a:\\> ");
    } else {
        put_string("d:\\> ");
    }
}

/* 画面にキャレットを書く */
void Console::drawCarret() {
    /* 塗りつぶし */
    SheetCtl::fillRect(
        sheet,
        cx,
        cy + FONT_H - 2,
        FONT_W,
        2,
        BLACK
    );

    /* 部分再描画 */
    SheetCtl::refresh(
        sheet,
        cx,
        cy + FONT_H - 2,
        cx + FONT_W + 1,
        cy + FONT_H + 1
    );
}

/* 画面に文字を書く */
void Console::put_char(byte c) {
    /* 改行 */
    if (c == '\n') {
        locate(INSETS_LEFT, cy + FONT_H);
        return;
    }

    /* タブ */
    else if (c == '\t') {
        put_char(' ');
        put_char(' ');
        put_char(' ');
        put_char(' ');
        return;
    }

    /* 半角英数字 または 半角カタカナ */
    else if ((0x20 <= c && c < 0x7f) || (0xA1 <= c && c <= 0xdf)) {
        char title[2];
        title[0] = c;
        title[1] = '\0';
        /* 文字列描画 */
        SheetCtl::drawString(
            sheet, 
            title, 
            cx, 
            cy, 
            BLACK
        );
        /* 部分再描画 */
        SheetCtl::refresh(
            sheet,
            cx,
            cy,
            cx + FONT_W + 1,
            cy + FONT_H + 1
        );
        /* カーソル移動 */
        locate(cx + FONT_W, cy);
    }

    /* それ以外の文字 */
    else {
        return;
    }
}

/* コマンドバッファーに文字をためてから画面に文字を書く */
void Console::put_key(byte c) {
    /* タブはスペースに変換しよう */
    if (c == '\t') {
        c = ' ';
    }

    /* 改行 */
    if (c == '\n') {
        restoreChar();
        locate(INSETS_LEFT, cy + FONT_H);
        parseCommand();
        memset(cmd_buf, '\0', 128);
        drawCarret();
        return;
    }

    /* バックスペース*/
    if (c == '\b' && strlen(cmd_buf) > 0) {
        cmd_buf[strlen(cmd_buf) - 1] = '\0';
        cx -= FONT_W;
    }

    /* 半角英数字 */
    else if (0x20 <= c && c < 0x7f) {
        cmd_buf[strlen(cmd_buf)] = c;
    }

    restoreChar();
    put_char(c);
    drawCarret();
}

/* 画面に文字列を書く */
void Console::put_string(const char* str) {
    while (*str != '\0') {
        put_char(*str & 0xff);
        str++;
    }
}

/* 画面に文字を書く */
void Console::putChar(byte c) {
    if (Scheduler::current->console != NULL) {
        Scheduler::current->console->put_char(c);
    }
}

/* 画面に文字列を書く */
void Console::putString(const char* str) {
    if (Scheduler::current->console != NULL) {
        Scheduler::current->console->put_string(str);
    }
}

/* 画面に書式化された文字列を書く */
void Console::printf(const char* format, ...) {
    char prt_buf[128];
    int buf_size = sizeof(prt_buf);
    memset(prt_buf, 0, buf_size);
    va_list args;
    va_start(args, format);
    int result = vsprintf(prt_buf, format, args);
    va_end(args);
    if (result > buf_size) {
        prt_buf[buf_size - 1] = 0;
    }
    if (Scheduler::current->console != NULL) {
        Scheduler::current->console->put_string(prt_buf);
    }
}
