#include <stdio.h>
#include <sys/utsname.h>

int main() {
    struct utsname unameData;

    if (uname(&unameData) == -1) {
        perror("uname");
        return 1;
    }

    printf("Operating System Name: %s\n", unameData.sysname);
    printf("Node Name: %s\n", unameData.nodename);

    return 0;
}
