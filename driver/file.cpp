#include "../bayos.h"

int File::type = FS_TYPE_FAT12;

namespace driver {
    FileEntry* File::load(const char* name) {
        if (type == FS_TYPE_FAT12) {
            return FAT12::load(name);
        } else {
            return ISO9660::load(name);
        }
    }

    List<FileEntry*>* File::list() {
        if (type == FS_TYPE_FAT12) {
            return FAT12::list();
        } else {
            return ISO9660::list();
        }
    }
}
