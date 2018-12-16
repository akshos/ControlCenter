#include "powermanager.h"
#include <stdio.h>

void handle_reboot_errno(){
    switch (errno){
        case EFAULT:
           printf("ERROR: shutdown_system : Problem with getting user-space data\n");
           break;
        case EINVAL:
            printf("ERROR: shutdown_system : Bad magic number\n");
            break;
        case EPERM:
            printf("ERROR: shutdown_system : The calling process has insufficient privilege to call reboot()\n");
            break;
    }
}


int call_reboot(int cmd){
    int ret;

    //sync all caches and pending changes to filesystem
    sync();
    //poweroff
    ret = reboot(cmd);
    if (ret == -1){
        handle_reboot_errno();
        return -1;
    }
    return 0;
}

int hibernate_system(){
    return 0;
}

int suspend_system(){
    return 0;
}

int hybridsleep_system(){
    return 0;
}
