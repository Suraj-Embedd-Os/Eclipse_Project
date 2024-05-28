#include <stdio.h>
#include <libudev.h>

int main() {
    // Initialize udev context
	struct udev *udev = udev_new();
    if (!udev) {
        fprintf(stderr, "Failed to initialize udev\n");
        return 1;
    }

    // Create udev enumeration object and filter by power_supply subsystem
    struct udev_enumerate *enumerate = udev_enumerate_new(udev);
    if (!enumerate) {
        fprintf(stderr, "Failed to create udev enumeration object\n");
        udev_unref(udev);
        return 1;
    }
    udev_enumerate_add_match_subsystem(enumerate, "power_supply");

    // Scan devices
    udev_enumerate_scan_devices(enumerate);
    struct udev_list_entry *devices = udev_enumerate_get_list_entry(enumerate);
    struct udev_list_entry *entry;
    udev_list_entry_foreach(entry, devices) {
        const char *path = udev_list_entry_get_name(entry);
        struct udev_device *dev = udev_device_new_from_syspath(udev, path);
        if (dev) {
            const char *name = udev_device_get_property_value(dev, "POWER_SUPPLY_NAME");
            const char *manufacturer = udev_device_get_property_value(dev, "POWER_SUPPLY_MANUFACTURER");
            const char *capacity = udev_device_get_property_value(dev, "POWER_SUPPLY_CHARGE_FULL_DESIGN");
            const char *charge = udev_device_get_property_value(dev, "POWER_SUPPLY_CAPACITY");

            if (name && manufacturer && capacity && charge) {
                printf("Battery Name: %s\n", name);
                printf("Manufacturer: %s\n", manufacturer);
                printf("Designed Capacity Percentage: %s%%\n", capacity);
                printf("Current Charge Percentage: %s%%\n", charge);
                printf("\n");
            }

            udev_device_unref(dev);
        }
    }

    // Cleanup
    udev_enumerate_unref(enumerate);
    udev_unref(udev);
    return 0;
}
