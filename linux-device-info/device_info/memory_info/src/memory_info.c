#include <stdio.h>
#include <stdlib.h>
#include <libudev.h>
#include <sys/sysinfo.h>

/*int countMemoryModules();

int main() {
    struct sysinfo info;

    if (sysinfo(&info) != 0) {
        perror("Error retrieving system information");
        return 1;
    }

    printf("Total RAM: %lu MB\n", info.totalram/(1024*1024));
    printf("Total Swap: %lu MB\n", info.totalswap/(1024*1024));
    //printf("Total freehigh: %lu MB\n", info.freehigh/(1024*1024));
   // printf("Number of RAM devices: %lu\n", info.nr_devices);
   // printf("Number of swap devices: %u\n", info.nr_swap_pages);

    // Other memory-related information available in 'info' structure

    int num_modules = countMemoryModules();
    if (num_modules < 0) {
        fprintf(stderr, "Error counting memory modules\n");
        return 1;
    }

    printf("Total Number of Memory Modules: %d\n", num_modules);
    return 0;
}








#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

#define MAX_LINE_LENGTH 256

char g_maximum_Capacity[30]="125";
char g_number_of_devices[10]="145MB";

// Function to execute a shell command and capture its output
char* executeCommand(const char* command) {
    FILE* pipe = popen(command, "r");
    if (!pipe) {
        perror("Error executing command");
        return NULL;
    }

    static char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, pipe) != NULL) {
        if (strncmp("Maximum Capacity:", buffer, strlen("Maximum Capacity:")) == 0)
            strcpy(g_maximum_Capacity, buffer + strlen("Maximum Capacity:") + 1);
        else if (strncmp("Number Of Devices:", buffer, strlen("Number Of Devices:")) == 0)
            strcpy(g_number_of_devices, buffer + strlen("Number Of Devices:") + 1);

        printf("%s", buffer); // Print the buffer line by line
    }
    pclose(pipe);

    return buffer; // Return the last line read
}

int main() {
   // char* dmidecode_output = executeCommand("echo chetu123 | sudo -S dmidecode -t 16");

    //if (!dmidecode_output) {
       // fprintf(stderr, "Error executing dmidecode\n");
       // return 1;
    //}

    // Create JSON objects for storing data
    cJSON *root = cJSON_CreateObject();
    if(root == NULL)
    {
    	printf("unable to open\n");
    	return -1;
    }
    cJSON_AddStringToObject(root, "Maximum Capacity", g_maximum_Capacity);
    cJSON_AddStringToObject(root, "Number Of Devices", g_number_of_devices);

    // Convert JSON to string
    char *json_str = cJSON_Print(root);
    printf("JSON Data:\n%s\n", json_str);

    // Free memory
    cJSON_Delete(root);
    free(json_str);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

int main() {
    // Open the memory info file
    FILE* meminfo_file = fopen("/proc/meminfo", "r");
    if (meminfo_file == NULL) {
        perror("Error opening memory info file");
        return 1;
    }

    // Variables to store memory information
    long total_physical_memory = 0;
    long max_supported_memory = 0;
    int total_memory_modules = 0;
    int total_dimm_slots = 0;

    // Read lines from the memory info file
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, meminfo_file) != NULL) {
        // Check for total physical memory
        if (strstr(line, "MemTotal:") != NULL) {
            sscanf(line, "MemTotal: %ld kB", &total_physical_memory);
        }
        // For maximum supported memory, total number of memory modules, and total number of DIMM slots,
        // you may need to use other methods such as system calls or hardware-specific utilities.
        // Retrieving this information directly from a system file like /proc/meminfo is not feasible.

        // For demonstration purposes, let's set these values to arbitrary values.
        max_supported_memory = 64 * 1024 * 1024;  // 64 GB
        total_memory_modules = 4;
        total_dimm_slots = 8;
    }

    // Close the memory info file
    fclose(meminfo_file);

    // Print memory information
    printf("Total Physical Memory: %ld kB\n", total_physical_memory);
    printf("Maximum Supported Memory: %ld kB\n", max_supported_memory);
    printf("Total Number of Memory Modules: %d\n", total_memory_modules);
    printf("Total Number of DIMM slots: %d\n", total_dimm_slots);

    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Use popen to execute dmidecode command and capture its output
    FILE* fp = popen("echo chetu123 | sudo -S dmidecode -t memory", "r");
    if (fp == NULL) {
        perror("Error executing dmidecode");
        return 1;
    }

    // Variables to store memory-related information
    int total_memory_modules = 0;
    int total_dimm_slots = 0;
    unsigned long max_capacity = 0;

    // Parse dmidecode output to extract memory module and DIMM slot details
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Check for "Memory Device" section
        if (strstr(line, "Memory Device") != NULL) {
            total_memory_modules++;
            // Reset max capacity for each memory module
            max_capacity = 0;
        } else if (strstr(line, "Size:") != NULL) {
            // Extract size field to get capacity of each memory module
            unsigned long size;
            sscanf(line, " Size: %lu MB", &size);
            // Convert size from MB to bytes
            unsigned long capacity_bytes = size * 1024 * 1024;
            // Update max capacity if it's greater than current max capacity
            if (capacity_bytes > max_capacity) {
                max_capacity = capacity_bytes;
            }
        } else if (strstr(line, "Physical Memory Array") != NULL && strstr(line, "Number Of Devices") != NULL) {
            // Extract number of devices to get total DIMM slots
            int devices;
            sscanf(line, " Number Of Devices: %d", &devices);
            total_dimm_slots += devices;
        }
    }

    // Close the pipe
    pclose(fp);

    // Print memory-related information
    printf("Total Memory Modules: %d\n", total_memory_modules);
    printf("Total DIMM Slots: %d\n", total_dimm_slots);
    printf("Maximum Capacity of Each Memory Module: %lu bytes\n", max_capacity);

    return 0;
}






