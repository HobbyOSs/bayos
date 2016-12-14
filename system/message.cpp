#include "../bayos.h"

/* �R���X�g���N�^ */
Message::Message() {
    type = from = arg1 = arg2 = arg3 = len = 0;
    data = NULL;
}

/* �f�X�g���N�^ */
Message::~Message() {
    delete [] data;
}

/* ���b�Z�[�W�̐��� */
Message* Message::create(int type, int arg1, int arg2, int arg3, int arg4, int len, byte* data) {
    Message* e = new Message();
    e->type = type;
    e->from = Scheduler::current->id;
    e->arg1 = arg1;
    e->arg2 = arg2;
    e->arg3 = arg3;
    e->arg4 = arg4;
    e->len  = len;
    if (len > 0) {
        e->data = new byte[len];
        memcpy(e->data, data, len);
    } else {
        e->data = NULL;
    }
    return e;
}

/* ���b�Z�[�W�̑��M */
void Message::send(int to, Message* msg) {
    Scheduler::task_list[to]->fifo->add(msg);
}
