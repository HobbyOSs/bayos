#include "../apilib.h"

void* operator new(size_t size)
{
    void* p = (void *) api_malloc(size);
    if (p) {
        memset(p, 0, size);
    }
    return p;
}

void* operator new[](size_t size)
{
    void* p = (void *) api_malloc(size);
    if (p) {
        memset(p, 0, size);
    }
    return p;
}
