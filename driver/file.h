#ifndef _DRIVER_FILE_H_INCLUDED_
#define _DRIVER_FILE_H_INCLUDED_

#define FS_TYPE_FAT12   1
#define FS_TYPE_ISO9660 2

namespace driver {
    /* �t�@�C���G���g�� */
    class FileEntry {
    public:
        int   size;
        int   addr;
        char  name[12];
        byte* data;
    };

    /* ���z�t�@�C���}�l�[�W�� */
    class File {
    public:
        static int type;

    public:
        static FileEntry* load(const char* name);
        static List<FileEntry*>* list();
    };
}

#endif
