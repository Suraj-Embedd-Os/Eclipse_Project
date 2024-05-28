#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>


#define DATA_SIZE 256

// Function to read a string from a file
int readFromFile(const char *filename, char *buffer, size_t size) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
    ssize_t bytes_read = read(fd, buffer, size - 1);
    close(fd);
    if (bytes_read == -1) {
        perror("Error reading file");
        return 1;
    }
    buffer[bytes_read] = '\0'; // Null-terminate the string
    return 0;
}

int main() {
    // Define buffer to hold the data
    char buffer[DATA_SIZE];

    // List all block devices in the /sys/block directory
    DIR *dir;
    struct dirent *entry;
    dir = opendir("/sys/block");
    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // Read each block device
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || \
        		strncmp(entry->d_name, "loop",4) == 0 )
            continue;

        // Construct paths for device information
        char vendor_path[DATA_SIZE];
        char model_path[DATA_SIZE];
        char serial_path[DATA_SIZE];
        char size_path[DATA_SIZE];
        snprintf(vendor_path, DATA_SIZE, "/sys/block/%s/device/vendor", entry->d_name);
        snprintf(model_path, DATA_SIZE, "/sys/block/%s/device/model", entry->d_name);
        snprintf(serial_path, DATA_SIZE, "/sys/block/%s/device/serial", entry->d_name);
        snprintf(size_path, DATA_SIZE, "/sys/block/%s/size", entry->d_name);

        // Read device information
        if (readFromFile(vendor_path, buffer, DATA_SIZE) == 0) {
            printf("Device: %s\n", entry->d_name);
            printf("Vendor: %s", buffer);
        }
        if (readFromFile(model_path, buffer, DATA_SIZE) == 0) {
            printf("Model Number: %s", buffer);
        }
        if (readFromFile(serial_path, buffer, DATA_SIZE) == 0) {
            printf("Serial Number: %s", buffer);
        }
        if (readFromFile(size_path, buffer, DATA_SIZE) == 0) {
            unsigned long long size_bytes = strtoull(buffer, NULL, 10);
            printf("Size: %llu bytes\n", size_bytes);

            // Convert size to human-readable format (MB)
            double size_mb = size_bytes / (1024.0 * 1024.0);
            printf("Marketed Size: %.2f MB\n", size_mb);
        }

        printf("\n");
    }

    closedir(dir);
    return 0;
}
