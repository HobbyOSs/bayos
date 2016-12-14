#include "../bayos.h"

List<FileEntry*>* ISO9660::files = NULL;
IDEDriver* ISO9660::ide = NULL;

/* IDEタスク */
void ISO9660::init() {
    ISO9660::files = new List<FileEntry*>();

    /* 初期化 */
    ISO9660::ide = new IDEDriver(IDE_IRQ_PRIMARY, IDE_IRQ_SECONDARY);

    /* ATAPI デバイスの検索 */
    int controller, deviceNo;
    if ( !ISO9660::ide->findDevice(DEVICE_ATAPI, 0x05, &controller, &deviceNo) ) {
        return;
    }

    /* IRQ の取得 */
    //byte irq = (controller == PRIMARY) ? IDE_IRQ_PRIMARY : IDE_IRQ_SECONDARY;

    /* ATAPI デバイスの使用開始 */
    if ( !ISO9660::ide->selectDevice(controller, deviceNo) ) {
        return;
    }

    /* 基本ボリューム記述子の読み込み */
    PrimaryVolumeDescriptor* pvd = new PrimaryVolumeDescriptor;
    ISO9660::ide->read(16, pvd, ATAPI_SECTOR_SIZE); /* 16セクターまではブート領域なので */
    if (pvd->type[0] != ISO_PRIMARY_VOLUME_DESCRIPTOR || strncmp("CD001", pvd->id, 5) != 0) {
        return;
    }

    /* ルートディレクトリを読み込む */
    DirectoryEntry* root = (DirectoryEntry *)( pvd->root_directory_record );
    dword size = ((dword)((root->size_l + ATAPI_SECTOR_SIZE - 1) / ATAPI_SECTOR_SIZE)) * ATAPI_SECTOR_SIZE;
    byte* buffer = new byte[size];
    ISO9660::ide->read(root->extent_l, buffer, size);
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
            ISO9660::files->add(entry);
        }
        position += dir->length;
    }
    delete [] buffer;
}

/* ファイルを開く */
FileEntry* ISO9660::load(const char* name)
{
    char s[13];
    memcpy(s, name, strlen(name) + 1);
    for (int i = 0; i < 12; i++) {
        if ('a' <= s[i] && s[i] <= 'z') {
            /* 小文字は大文字に直す */
            s[i] -= 0x20;
        }
    }

    /* ファイルを検索 */
    int I = ISO9660::files->size();
    for (int i = 0; i < I; i++) {
        FileEntry* entry = ISO9660::files->get(i);
        if (strncmp(entry->name, s, 12) == 0) {
            /* すでに読み込み済み */
            if (entry->data != NULL) {
                return entry;
            }

            /* ファイルフォーマットチェック */
            byte* data = new byte[entry->size];
            ISO9660::ide->read(entry->addr, data, entry->size);
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
List<FileEntry*>* ISO9660::list() {
    return ISO9660::files;
}
