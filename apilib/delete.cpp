#include "../apilib.h"

void operator delete(void* address)
{
    if (address) {
        api_free(address);
    }
    return;
}

void operator delete[](void* address)
{
    if (address) {
        api_free(address);
    }
    return;
}
