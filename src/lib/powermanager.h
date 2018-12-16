#include <unistd.h>
#include <sys/reboot.h>
#include <linux/reboot.h>
#include <errno.h>

#define shutdown_system() call_reboot(LINUX_REBOOT_CMD_POWER_OFF)
#define reboot_system() call_reboot(LINUX_REBOOT_CMD_RESTART)

int call_reboot(int cmd);

int hibernate_system();

int suspend_system();

int hybridsleep_system();

void handle_reboot_errno();
