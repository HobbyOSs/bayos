#include "../apilib.h"

void HariMain(void)
{
#if 1
    api_putchar('H');
    api_putchar('i');
    api_putchar('!');
    api_putchar('\n');
    api_putstr0("Hello,World!\n");
    api_putstr1("How are you?\n", 13);
#endif
#if 0
    /* tomo_getmouse */
    static char* mouse_state[5] = {
        "NONE",
        "MOUSE_RELEASED",
        "MOUSE_PRESSED",
        "MOUSE_MOVED",
        "MOUSE_DRAGGED"
    };
    MOUSE_INFO mouse_info;
    tomo_getmouse(0/*ê‚ëŒç¿ïW*/, &mouse_info);
    printf("mouse.x = %d\n", mouse_info.x);
    printf("mouse.y = %d\n", mouse_info.y);
    printf("mouse.button = %d\n", mouse_info.button);
    printf("mouse.state = %s\n", mouse_state[mouse_info.state]);
    
    /* tomo_gettick */
    printf("tick = %d\n", tomo_gettick());
    
    /* tomo_sysinfo */
    SYS_INFO sys_info;
    tomo_sysinfo(&sys_info);
    printf("bpps = %d\n",     sys_info.bpps);
    printf("screen_x = %d\n", sys_info.screen_x);
    printf("screen_y = %d\n", sys_info.screen_y);
    printf("vram = 0x%x\n",   sys_info.vram);
    printf("os_type = %d\n",  sys_info.os_type);
    
    /* tomo_systime */
    TIME_INFO time_info;
    tomo_systime(&time_info);
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", 
        time_info.year, time_info.month, time_info.day, 
        time_info.hour, time_info.minutes, time_info.second);
#endif
    api_end();
}
