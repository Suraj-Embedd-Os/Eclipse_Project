/*
 ============================================================================
 Name        : network_card_info.c
 Author      : suraj dev pandit
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <libudev.h>
#include <stdint.h>
#include <linux/ethtool.h>

#define BUFF 128
struct network_card_info{
	char mac_address[BUFF];
	char ip_address[BUFF];
	char gateway_ip_address[BUFF];
	char driver_version[BUFF];
	uint32_t speed;

};

/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <net/if_arp.h>
#include <ifaddrs.h>
#include <sys/socket.h>
  #include <netdb.h>


// Function to retrieve network card information
void getNetworkCardInfo() {
    struct ifaddrs *ifaddr, *ifa;
    char host[NI_MAXHOST];

    // Get list of network interfaces
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return;
    }

    // Iterate through each interface
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) {
            continue;
        }

        // Check if it's an IPv4 interface
        if (ifa->ifa_addr->sa_family == AF_INET) {
            // Print interface name
            printf("Interface: %s\n", ifa->ifa_name);

            // Print MAC address
            struct ifreq ifr;
            int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            if (sockfd >= 0) {
                strncpy(ifr.ifr_name, ifa->ifa_name, IFNAMSIZ - 1);
                if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) != -1) {
                    printf("MAC Address: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
                           (unsigned char)ifr.ifr_hwaddr.sa_data[0],
                           (unsigned char)ifr.ifr_hwaddr.sa_data[1],
                           (unsigned char)ifr.ifr_hwaddr.sa_data[2],
                           (unsigned char)ifr.ifr_hwaddr.sa_data[3],
                           (unsigned char)ifr.ifr_hwaddr.sa_data[4],
                           (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
                }
                close(sockfd);
            }

            // Print IP address
            if (getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) == 0) {
                printf("IP Address: %s\n", host);
            }

            // Print gateway IP address (if available)
            // Note: This requires further processing, such as parsing routing table
            //       For simplicity, we skip printing the gateway IP address here.

            // Print current speed and driver version
            // Not implemented in this example due to complexity and system-specific differences

            printf("\n");
        }
    }

    // Free memory
    freeifaddrs(ifaddr);
}

int main() {
    getNetworkCardInfo();
    return 0;
}*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <net/if_arp.h>
#include <ifaddrs.h>
#include <sys/socket.h>
 #include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <net/if_arp.h>
#include <ifaddrs.h>

// Function to retrieve the gateway IP address associated with a network interface
int getGatewayIpAddress(const char *ifName, char *gatewayIp) {
    FILE *fp = fopen("/proc/net/route", "r");
    if (fp == NULL) {
        perror("fopen");
        return -1;
    }

    // Skip the first line (header)
    char line[256];
    fgets(line, sizeof(line), fp);

    // Iterate through each line in the routing table
    while (fgets(line, sizeof(line), fp) != NULL) {
        char iface[IF_NAMESIZE];
        unsigned long dest, gw;
        int flags, refcnt, use, metric, mask, mtu, window, irtt;

        // Parse the line
        if (sscanf(line, "%s %lx %lx %x %d %d %d %lx %d %d %d\n", iface, &dest, &gw, &flags,
                   &refcnt, &use, &metric, &mask, &mtu, &window, &irtt) != 11) {
            continue;
        }

        // Check if the destination IP is 0.0.0.0 (default route) and the interface matches
        if (dest == 0 && strcmp(iface, ifName) == 0) {
            struct in_addr addr;
            addr.s_addr = gw;
            strcpy(gatewayIp, inet_ntoa(addr));
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    return -1; // Gateway IP not found
}

// Function to retrieve the current speed of a network interface
int getCurrentSpeed(const char *ifName) {
    FILE *fp;
    char path[256], line[256];

    // Construct the path to the ethtool command output file
    snprintf(path, sizeof(path), "/tmp/%s_ethtool_info", ifName);

    // Run the ethtool command and store the output in a file
    snprintf(line, sizeof(line), "ethtool %s > %s", ifName, path);
    system(line);

    // Open the file and parse the output to find the current speed
    fp = fopen(path, "r");
    if (fp == NULL) {
        perror("fopen");
        return -1;
    }

    int speed = -1;
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, "Speed:") != NULL) {
            sscanf(line, "Speed: %d", &speed);
            break;
        }
    }

    fclose(fp);
    remove(path); // Remove the temporary file

    return speed;
}

// Function to retrieve the driver version of a network interface
int getDriverVersion(const char *ifName, char *driverVersion) {
    FILE *fp;
    char path[256], line[256];

    // Construct the path to the ethtool command output file
    snprintf(path, sizeof(path), "/tmp/%s_ethtool_info", ifName);

    // Run the ethtool command and store the output in a file
    snprintf(line, sizeof(line), "ethtool -i %s > %s", ifName, path);
    system(line);

    // Open the file and parse the output to find the driver version
    fp = fopen(path, "r");
    if (fp == NULL) {
        perror("fopen");
        return -1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, "driver:") != NULL) {
            // Extract the driver version from the "driver:" line
            char *versionStart = strchr(line, ':') + 2; // Skip "driver: " prefix
            strcpy(driverVersion, versionStart);
            break;
        }
    }

    fclose(fp);
    remove(path); // Remove the temporary file

    return 0;
}

// Function to retrieve network card information
void getNetworkCardInfo() {
    struct ifaddrs *ifaddr, *ifa;
    char host[NI_MAXHOST];

    // Get list of network interfaces
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return;
    }

    // Iterate through each interface
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL || ifa->ifa_addr->sa_family != AF_INET) {
            continue;
        }

        // Print interface name
        printf("Interface: %s\n", ifa->ifa_name);

        // Print MAC address
        struct ifreq ifr;
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd >= 0) {
            strncpy(ifr.ifr_name, ifa->ifa_name, IFNAMSIZ - 1);
            if (ioctl(sockfd, SIOCGIFHWADDR, &ifr) != -1) {
                printf("MAC Address: %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
                       (unsigned char)ifr.ifr_hwaddr.sa_data[0],
                       (unsigned char)ifr.ifr_hwaddr.sa_data[1],
                       (unsigned char)ifr.ifr_hwaddr.sa_data[2],
                       (unsigned char)ifr.ifr_hwaddr.sa_data[3],
                       (unsigned char)ifr.ifr_hwaddr.sa_data[4],
                       (unsigned char)ifr.ifr_hwaddr.sa_data[5]);
            }
            close(sockfd);
        }

        // Print IP address
        if (getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST) == 0) {
            printf("IP Address: %s\n", host);
        }

        // Print gateway IP address
        char gatewayIp[NI_MAXHOST];
        if (getGatewayIpAddress(ifa->ifa_name, gatewayIp) == 0) {
            printf("Gateway IP Address: %s\n", gatewayIp);
        } else {
            printf("Gateway IP Address: Not available\n");
        }

        // Print current speed
        int speed = getCurrentSpeed(ifa->ifa_name);
        if (speed != -1) {
            printf("Current Speed: %d Mbps\n", speed);
        } else {
            printf("Current Speed: Not available\n");
        }

        // Print driver version
        char driverVersion[256];
        if (getDriverVersion(ifa->ifa_name, driverVersion) == 0) {
            printf("Driver Version: %s", driverVersion);
        } else {
            printf("Driver Version: Not available\n");
        }

        printf("\n");
    }

    // Free memory
    freeifaddrs(ifaddr);
}

int main() {
    getNetworkCardInfo();
    return 0;
}

