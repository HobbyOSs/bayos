#include "../bayos.h"

List<FileEntry*>* FAT12::files = NULL;
int* FAT12::fat = NULL;

/* クラスターを指定してファイルの内容を読み込む */
void FAT12::read(FileEntry* entry, byte* buf) {
    byte* img = (byte *) (ADR_DISKIMG + 0x003e00 /* データ開始位置 */);

    int size    = entry->size;
    int clustno = entry->addr;

    for (;;) {
        if (size <= 512) {
            for (int i = 0; i < size; i++) {
                buf[i] = img[clustno * 512 + i];
            }
            break;
        } else {
            for (int i = 0; i < 512; i++) {
                buf[i] = img[clustno * 512 + i];
            }
            size -= 512;
            buf  += 512;
            clustno = FAT12::fat[clustno];
        }
    }
}

/* ファイルマネージャの初期化 */
void FAT12::init() {
    byte* img = (byte *) (ADR_DISKIMG + 0x000200 /* ブートセクタ */);
    FileInfo* finfo = (FileInfo *) (ADR_DISKIMG + 0x002600 /* FAT12情報開始位置 */);

    FAT12::files = new List<FileEntry*>();
    FAT12::fat   = new int[2880];

    /* FATの圧縮を展開 */
    int j = 0;
    for (int i = 0; i < 2880; i += 2) {
        FAT12::fat[i + 0] = (img[j + 0]      | img[j + 1] << 8) & 0xfff;
        FAT12::fat[i + 1] = (img[j + 1] >> 4 | img[j + 2] << 4) & 0xfff;
        j += 3;
    }

    /* 全ファイルの情報を一気に読み込んでおく */
    for (int i = 0; i < 224 /* 最大ファイル数 */; i++) {
        FileInfo info = finfo[i];
        if (info.name[0] == 0x00) {
            break;
        } else if ((info.type & 0x18 /* ファイル */) == 0) {
            FileEntry* entry = new FileEntry();
            entry->size = info.size;
            entry->addr = info.clustno;
            entry->data = NULL;
            memcpy(entry->name, info.name, 11);
            FAT12::files->add(entry);
        }
    }
}

/* ファイルを開く */
FileEntry* FAT12::load(const char* name)
{
    char s[12];
    memset(s, ' ',  11);

    /* HOGE____TXT のような形に変換する */
    int j = 0;
    for (int i = 0; j < 11 && name[i] != 0; i++) {
        if (name[i] == '.') {
            j = 8;
        } else {
            s[j] = name[i];
            if ('a' <= s[j] && s[j] <= 'z') {
                /* 小文字は大文字に直す */
                s[j] -= 0x20;
            }
            j++;
        }
    }

    /* ファイルを検索 */
    int I = FAT12::files->size();
    for (int i = 0; i < I; i++) {
        FileEntry* entry = FAT12::files->get(i);
        if (strncmp(entry->name, s, 11) == 0) {
            /* すでに読み込み済み */
            if (entry->data != NULL) {
                return entry;
            }

            /* ファイルフォーマットチェック */
            byte* data = new byte[entry->size];
            read(entry, data);
            int tek5s_size = tek_checkformat(entry->size, data);

            if (tek5s_size <= 0) {
                /* 通常のファイル */
                entry->data = data;
                return entry;
            } else {
                /* tek5s形式 */
                entry->data = new byte[tek5s_size];
                tek_decode(tek5s_size, data, entry->data);
                entry->size = tek5s_size; /* ※ 元のサイズにするとバグる */
                delete [] data;
                return entry;
            }
        }
    }

    return NULL; /* 見つからなかった */
}

/* ファイルの一覧を返す */
List<FileEntry*>* FAT12::list() {
    return FAT12::files;
}
