#include <stdio.h>
#include <libudev.h>

/*
 *   *-firmware
       description: BIOS
       vendor: Acer
       physical id: 0
       version: P21-A1
       date: 02/08/2021
       size: 64KiB
       capacity: 16MiB
 *
 *
 */

int main() {
    // Create a udev context
    struct udev *udev = udev_new();
    if (!udev) {
        fprintf(stderr, "Failed to create udev context\n");
        return 1;
    }

    // Create a udev enumerator
    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    if (!enumerate) {
        fprintf(stderr, "Failed to create udev enumerator\n");
        udev_unref(udev);
        return 1;
    }

    // Add a match for the subsystem "dmi"
    udev_enumerate_add_match_subsystem(enumerate, "dmi");

    // Scan the devices
    udev_enumerate_scan_devices(enumerate);
    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;
    udev_list_entry_foreach(entry, devices) {
        const char *syspath = udev_list_entry_get_name(entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, syspath);
        if (dev) {
            const char *prop = udev_device_get_sysattr_value(dev, "bios_date");
            if (prop)
                printf("BIOS Release Date: %s\n", prop);
            else
                printf("BIOS Release Date: Not available\n");

            prop = udev_device_get_sysattr_value(dev, "bios_version");
            if (prop)
                printf("BIOS Version: %s\n", prop);
            else
                printf("BIOS Version: Not available\n");

            udev_device_unref(dev);
        } else {
            fprintf(stderr, "Failed to get device\n");
        }
    }

    // Cleanup
    udev_enumerate_unref(enumerate);
    udev_unref(udev);

    return 0;
}
