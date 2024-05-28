#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/hdreg.h>

int main() 
{
    int fd;
    struct hd_driveid id;

    // Open device file
    fd = open("/dev/sda", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open device file");
        return 1;
    }

    // Get drive ID
    if (ioctl(fd, HDIO_GET_IDENTITY, &id) < 0) {
        perror("Failed to get drive identity");
        close(fd);
        return 1;
    }

    // Close device file
    close(fd);

    // Print disk drive information
    printf("Vendor: %d\n", id.vendor0);
    printf("Model Number: %s\n", id.model);
    printf("Serial Number: %s\n", id.serial_no);
    printf("Firmware Revision: %s\n", id.fw_rev);

    return 0;
}
