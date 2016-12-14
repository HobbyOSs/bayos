#if !defined(SYSTEM_MESSAGE_H_INCLUDED_)
#define SYSTEM_MESSAGE_H_INCLUDED_

namespace system {
    /* ���b�Z�[�W */
    class Message {
    public:
        int type;   /* ���b�Z�[�W��� */
        int from;   /* ���M�� */
        int arg1;   /* ����(1) */
        int arg2;   /* ����(2) */
        int arg3;   /* ����(3) */
        int arg4;   /* ����(4) */
        int len;    /* �f�[�^�̒��� */
        byte* data; /* �ϒ��f�[�^ */

    public:
        Message();
        virtual ~Message();
        static Message* create(
            int type = 0, 
            int arg1 = 0, 
            int arg2 = 0, 
            int arg3 = 0, 
            int arg4 = 0, 
            int len  = 0, 
            byte* data = NULL
        );
        static void send(int to, Message* msg);
    };
}

#endif
