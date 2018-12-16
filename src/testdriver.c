#include "lib/powermanager.h"
#include <stdio.h>

#define TEST_SUCCESS 1
#define TEST_FAIL -1

int test_powermanager(){
    int option = 0;
    printf("\nPOWERMANAGER Test\n");
    printf("1. Shutdown 2. Reboot 3. Suspend 4. Hibernate 5. Hybrid Sleep\n");
    printf("Option? ");
    scanf("%d", &option);
    switch (option){
        case 1:
            shutdown_system();
            break;
        case 2:
            reboot_system();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            printf("Sorry that was an invalid input\n");
    }
    return TEST_SUCCESS;
}

int main(){
    test_powermanager();
    return 0;
}
