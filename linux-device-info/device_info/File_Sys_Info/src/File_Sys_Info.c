#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <errno.h>

void get_filesystem_info(const char *path) {
    struct statvfs vfs;

    if (statvfs(path, &vfs) != 0) {
        perror("statvfs");
        exit(EXIT_FAILURE);
    }

    unsigned long total_space = vfs.f_blocks * vfs.f_frsize;
    unsigned long free_space = vfs.f_bfree * vfs.f_frsize;
    unsigned long used_space = total_space - free_space;

    printf("Volume Capacity: %lu Mbytes\n", total_space/(1024*1024));
    printf("Volume Free Space: %lu Mbytes\n", free_space/(1024*1024));
    printf("Volume Used Space: %lu Mbytes\n", used_space/(1024*1024));
}

char* get_volume_uuid(const char *device) {
    char command[128];
    snprintf(command, sizeof(command), "blkid -s UUID -o value %s", device);

    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    static char uuid[128];
    if (fgets(uuid, sizeof(uuid), fp) != NULL) {
        uuid[strcspn(uuid, "\n")] = 0;  // Remove newline character
    }

    pclose(fp);
    return uuid;
}

int main() {
    const char *mount_point = "/";  // Root file system mount point
    const char *device = "/dev/sda3";  // Adjust this to your actual device

    get_filesystem_info(mount_point);

    char *uuid = get_volume_uuid(device);
    printf("Volume Serial Number (UUID): %s\n", uuid);

    return 0;
}
