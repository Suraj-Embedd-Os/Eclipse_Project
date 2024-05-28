#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;
    char flags;
    char templet[] = "/tmp/testXXXXXX"; // Ensure the template ends with six 'X' characters

    setbuf(stdout, NULL);

    fd = mkstemp(templet);

    if(fd == -1) {
        perror("mkstemp");
        return -1;
    }

    printf("File offset before fork(): %lld\n", (long long)lseek(fd, 0, SEEK_CUR));

    // Get the current file status flags
    flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("fcntl");
        return 1;
    }
    printf("O_APPEND flag before fork() is: %s\n", (flags & O_APPEND) ? "on" : "off");

    switch(fork()) {
        case -1:
            perror("fork");
            exit(-1);

        case 0: // Child process
            if (lseek(fd, 1000, SEEK_SET) == -1) {
                perror("lseek");
                exit(-1);
            }

            flags = fcntl(fd, F_GETFL);
            if (flags == -1) {
                perror("fcntl");
                exit(-1);
            }

            flags |= O_APPEND;
            if (fcntl(fd, F_SETFL, flags) == -1) {
                perror("fcntl");
                exit(-1);
            }
            _exit(EXIT_SUCCESS); // Terminate child process

        default: // Parent process
            if (wait(NULL) == -1) {
                perror("wait");
                exit(-1);
            }
            printf("Child has exited\n");
            printf("File offset in parent: %lld\n", (long long)lseek(fd, 0, SEEK_CUR));

            // Get the current file status flags
            flags = fcntl(fd, F_GETFL);
            if (flags == -1) {
                perror("fcntl");
                exit(-1);
            }
            if (fcntl(fd, F_SETFL, flags) == -1) {
                perror("fcntl");
                exit(-1);
            }
            printf("O_APPEND flag in parent is: %s\n", (flags & O_APPEND) ? "on" : "off");
            exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}
