#ifndef _DRIVER_FAT12_H_INCLUDED_
#define _DRIVER_FAT12_H_INCLUDED_

#define ADR_DISKIMG 0x00100000

namespace driver {
    /* ファイル情報 */
    class FileInfo {
    public:
        byte  name[8], ext[3], type;
        byte  reserve[10];
        word  time, date, clustno;
        dword size;
    };

    /* FAT12ファイルマネージャ */
    class FAT12 {
    private:
        static List<FileEntry*>* files;
        static int* fat;

    private:
        static void read(FileEntry* entry, byte* buf);

    public:
        static void init();
        static FileEntry* load(const char* name);
        static List<FileEntry*>* list();
    };
}

#endif
