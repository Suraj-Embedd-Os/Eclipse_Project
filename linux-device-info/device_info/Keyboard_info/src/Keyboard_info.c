#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>

#define DEVICE_PATH "/dev/input/event6"  // Replace with the correct event device path

void get_device_info(const char *device_path) {
    int fd = open(device_path, O_RDONLY,777);
    if (fd == -1) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }

    // Get device name
    char name[256] = "Unknown";
    if (ioctl(fd, EVIOCGNAME(sizeof(name)), name) < 0) {
        perror("Error getting device name");
    } else {
        printf("Device Name: %s\n", name);
    }

    // Get device ID
    struct input_id device_info;
    if (ioctl(fd, EVIOCGID, &device_info) < 0) {
        perror("Error getting device ID");
    } else {
        printf("Vendor ID: 0x%04x\n", device_info.vendor);
        printf("Product ID: 0x%04x\n", device_info.product);
        printf("Version: 0x%04x\n", device_info.version);
    }

    // Get supported event types
    unsigned long ev_bits[(EV_MAX + 7) / 8] = {0};
    if (ioctl(fd, EVIOCGBIT(0, EV_MAX), ev_bits) < 0) {
        perror("Error getting event types");
    } else {
        printf("Supported event types:\n");
        for (int i = 0; i < EV_MAX; i++) {
            if (ev_bits[i / 8] & (1 << (i % 8))) {
                printf("  Event type %d\n", i);
            }
        }
    }

    // Get supported keys
    unsigned long key_bits[(KEY_MAX + 7) / 8] = {0};
    if (ioctl(fd, EVIOCGBIT(EV_KEY, KEY_MAX), key_bits) < 0) {
        perror("Error getting supported keys");
    } else {
        printf("Supported keys:\n");
        for (int i = 0; i < KEY_MAX; i++) {
            if (key_bits[i / 8] & (1 << (i % 8))) {
                printf("  Key %d\n", i);
            }
        }
    }

    close(fd);
}

int main() {
    get_device_info(DEVICE_PATH);
    return 0;
}
