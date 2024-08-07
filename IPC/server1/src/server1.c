/*
 ============================================================================
 Name        : server1.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

int main() {
    int server_sockfd, client_sockfd;
    socklen_t server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

    unlink("server_socket");
    server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);

    if (bind(server_sockfd, (struct sockaddr *)&server_address, server_len) < 0) {
        perror("bind");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_sockfd, 5) < 0) {
        perror("listen");
        close(server_sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        char ch;
        printf("server waiting\n");
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        if (client_sockfd < 0) {
            perror("accept");
            close(server_sockfd);
            exit(EXIT_FAILURE);
        }

        read(client_sockfd, &ch, 1);
        ch++;
        write(client_sockfd, &ch, 1);
        close(client_sockfd);
    }

    close(server_sockfd);
    return EXIT_SUCCESS;
}
