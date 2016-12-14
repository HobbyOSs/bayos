#include "../apilib.h"

#if 0
void* memcpy(void* s1, const void* s2, size_t size)
{
    asm volatile("movl %0, %%edi \n"
                 "movl %1, %%esi \n"
                 "movl %2, %%ecx \n"
                 "cld            \n"
                 "rep            \n"
                 "movsb          \n"
                 : /* no output */
                 : "m"(s1), "m"(s2), "m"(size)
                 : "edi", "esi", "ecx");

    return s1;
}
#endif
// monapi2::MemoryFn::copy
void* memcpy(void* s1, const void* s2, size_t size) {
    int count4 = size / 4;
    int count1 = size - count4 * 4;

    /* 4バイト転送部分 */
    asm volatile("movl %0, %%edi \n"
                 "movl %1, %%esi \n"
                 "movl %2, %%ecx \n"
                 "cld            \n"
                 "rep movsd      \n"
                 :
                 : "m"(s1), "m"(s2), "m"(count4)
                 : "edi", "esi", "ecx");

    /* 1バイト転送部分 */
    asm volatile("movl %0, %%ecx \n"
                 "rep movsb      \n"
                 :
                 : "m"(count1)
                 : "ecx");

    return s1;
}
