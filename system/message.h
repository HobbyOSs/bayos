#if !defined(SYSTEM_MESSAGE_H_INCLUDED_)
#define SYSTEM_MESSAGE_H_INCLUDED_

namespace system {
    /* メッセージ */
    class Message {
    public:
        int type;   /* メッセージ種別 */
        int from;   /* 送信元 */
        int arg1;   /* 引数(1) */
        int arg2;   /* 引数(2) */
        int arg3;   /* 引数(3) */
        int arg4;   /* 引数(4) */
        int len;    /* データの長さ */
        byte* data; /* 可変長データ */

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
