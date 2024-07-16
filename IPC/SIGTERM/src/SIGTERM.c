#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define NUM_CHILDREN 5

void child_process() {
    srand(getpid());  // Seed the random number generator with the child process ID
    int sleep_time = rand() % 10 + 1;  // Sleep for 1 to 10 seconds
    printf("Child %d sleeping for %d seconds.\n", getpid(), sleep_time);
    sleep(sleep_time);
    printf("Child %d waking up and exiting.\n", getpid());
    exit(0);
}

int main() {
    pid_t pids[NUM_CHILDREN];
    int status;

    // Fork child processes
    for (int i = 0; i < NUM_CHILDREN; i++) {
        pids[i] = fork();
        if (pids[i] < 0) {
            perror("fork");
            exit(1);
        } else if (pids[i] == 0) {
            // Child process
            child_process();
        }
    }

    // Parent process waits for the first child to terminate
    pid_t terminated_child = wait(&status);
    if (terminated_child < 0) {
        perror("wait");
        exit(1);
    }

    printf("Child %d terminated.\n", terminated_child);

    // Send SIGTERM to all remaining children
    for (int i = 0; i < NUM_CHILDREN; i++) {
        if (pids[i] != terminated_child) {
            kill(pids[i], SIGTERM);
        }
    }

    // Wait for all remaining children and verify they were terminated by SIGTERM
    for (int i = 0; i < NUM_CHILDREN - 1; i++) {
        pid_t terminated_child = wait(&status);
        if (terminated_child < 0) {
            perror("wait");
            exit(1);
        }
        if (WIFSIGNALED(status) && WTERMSIG(status) == SIGTERM) {
            printf("Child %d terminated by SIGTERM.\n", terminated_child);
        } else {
            printf("Child %d terminated by other means.\n", terminated_child);
        }
    }

    printf("Parent process exiting.\n");
    return 0;
}
