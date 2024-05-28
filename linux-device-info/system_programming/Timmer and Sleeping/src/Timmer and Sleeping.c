/*
 ============================================================================
 Name        : Timmer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>


void alarm_handler_1(int args)
{
	printf("Timer expired\n");
}

void alarm_handler_2(int signum) {
    printf("Timeout occurred! Exiting...\n");
    // Perform any necessary cleanup and exit the program
    // For demonstration purposes, we simply exit here
    exit(1);
}
void setitimer_use_1();
void setitimer_use_2();
void long_running_operation() ;


int main(void) {

	setitimer_use_2();

	return EXIT_SUCCESS;
}

//int setitimer(int which, const struct itimerval *new_value,
  //                   struct itimerval *old_value);

void setitimer_use_1()
{
	struct itimerval timer;

		 //struct timeval it_interval; /* Interval for periodic timer */
		 //struct timeval it_value;    /* Time until next expiration */
	     // time_t      tv_sec;         /* seconds */
	     //suseconds_t tv_usec;        /* microseconds */

		 signal(SIGALRM, alarm_handler_1);

		 timer.it_interval.tv_sec = 1;
		 timer.it_interval.tv_usec = 0;

		 timer.it_value.tv_sec = 1;
		 timer.it_value.tv_usec = 0;





		if(setitimer(ITIMER_REAL,&timer,NULL) == -1)
		{
			perror("setitimer");
			return 1;
		}

		for(;;)
		{
			sleep(5);
		}
}
void long_running_operation() {
    // Simulate a long-running operation
    sleep(10); // Sleep for 10 seconds
}

void setitimer_use_2()
{
    struct itimerval timer;

    // Set up signal handler for SIGALRM
    signal(SIGALRM, alarm_handler_2);

    // Set timer to expire after 5 seconds
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;

    // Disable the timer after expiration
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    // Set the timer
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
        perror("setitimer");
        return 1;
    }

    printf("Starting long-running operation...\n");
    long_running_operation();

    // If the long-running operation completes before the timer expires,
    // the timer will be disabled and the program will continue execution.

    printf("Operation completed within timeout.\n");
}
