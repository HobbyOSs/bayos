#include "../bayos.h"

List<FileEntry*>* ISO9660::files = NULL;
IDEDriver* ISO9660::ide = NULL;

/* IDE�^�X�N */
void ISO9660::init() {
    ISO9660::files = new List<FileEntry*>();

    /* ������ */
    ISO9660::ide = new IDEDriver(IDE_IRQ_PRIMARY, IDE_IRQ_SECONDARY);

    /* ATAPI �f�o�C�X�̌��� */
    int controller, deviceNo;
    if ( !ISO9660::ide->findDevice(DEVICE_ATAPI, 0x05, &controller, &deviceNo) ) {
        return;
    }

    /* IRQ �̎擾 */
    //byte irq = (controller == PRIMARY) ? IDE_IRQ_PRIMARY : IDE_IRQ_SECONDARY;

    /* ATAPI �f�o�C�X�̎g�p�J�n */
    if ( !ISO9660::ide->selectDevice(controller, deviceNo) ) {
        return;
    }

    /* ��{�{�����[���L�q�q�̓ǂݍ��� */
    PrimaryVolumeDescriptor* pvd = new PrimaryVolumeDescriptor;
    ISO9660::ide->read(16, pvd, ATAPI_SECTOR_SIZE); /* 16�Z�N�^�[�܂ł̓u�[�g�̈�Ȃ̂� */
    if (pvd->type[0] != ISO_PRIMARY_VOLUME_DESCRIPTOR || strncmp("CD001", pvd->id, 5) != 0) {
        return;
    }

    /* ���[�g�f�B���N�g����ǂݍ��� */
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
            /* �t�@�C�����̌�ɂ�";1"�i�o�[�W�����ԍ��j���폜 */
            memcpy(entry->name, dir->name, dir->name_len - 2);
            ISO9660::files->add(entry);
        }
        position += dir->length;
    }
    delete [] buffer;
}

/* �t�@�C�����J�� */
FileEntry* ISO9660::load(const char* name)
{
    char s[13];
    memcpy(s, name, strlen(name) + 1);
    for (int i = 0; i < 12; i++) {
        if ('a' <= s[i] && s[i] <= 'z') {
            /* �������͑啶���ɒ��� */
            s[i] -= 0x20;
        }
    }

    /* �t�@�C�������� */
    int I = ISO9660::files->size();
    for (int i = 0; i < I; i++) {
        FileEntry* entry = ISO9660::files->get(i);
        if (strncmp(entry->name, s, 12) == 0) {
            /* ���łɓǂݍ��ݍς� */
            if (entry->data != NULL) {
                return entry;
            }

            /* �t�@�C���t�H�[�}�b�g�`�F�b�N */
            byte* data = new byte[entry->size];
            ISO9660::ide->read(entry->addr, data, entry->size);
            int tek5s_size = tek_checkformat(entry->size, data);

            if (tek5s_size <= 0) {
                /* �ʏ�̃t�@�C�� */
                entry->data = data;
                return entry;
            } else {
                /* tek5s�`�� */
                entry->data = new byte[tek5s_size];
                tek_decode(tek5s_size, data, entry->data);
                entry->size = tek5s_size; /* �� ���̃T�C�Y�ɂ���ƃo�O�� */
                delete [] data;
                return entry;
            }
        }
    }

    return NULL; /* ������Ȃ����� */
}

/* �t�@�C���̈ꗗ��Ԃ� */
List<FileEntry*>* ISO9660::list() {
    return ISO9660::files;
}
