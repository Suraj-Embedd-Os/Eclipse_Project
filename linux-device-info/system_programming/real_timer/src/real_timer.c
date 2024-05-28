/*
 ============================================================================
 Name        : real_timer.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include<stdbool.h>
#include <time.h>

static volatile sig_atomic_t gotAlarm = 0;

static void displayTimes(const char *msg, bool includeTimer);
static void sigalrmHandler(int sig);

int main(int argc, char *argv[]) {

	struct itimerval itv;
	clock_t prevClock;
	int maxSigs;
	int sigCnt;
	struct sigaction sa;
	if (argc > 1 && strcmp(argv[1], "--help") == 0) {
	printf("%s [secs [usecs [int-secs [int-usecs]]]]\n", argv[0]);
	return 1;
	}

	sigCnt = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigalrmHandler;
	if (sigaction(SIGALRM, &sa, NULL) == -1){
		perror("sigaction");
		return 1;
	}

	/* Set timer from the command-line arguments */
	itv.it_value.tv_sec = (argc > 1) ? atol(argv[1]) : 2;
	itv.it_value.tv_usec = (argc > 2) ? atol(argv[2]) : 0;
	itv.it_interval.tv_sec = (argc > 3) ? atol(argv[3]) : 0;
	itv.it_interval.tv_usec = (argc > 4) ? atol(argv[4]) : 0;

	maxSigs = (itv.it_interval.tv_sec == 0 &&  \
	itv.it_interval.tv_usec == 0) ? 1 : 3;

	displayTimes("START:", false);

	if (setitimer(ITIMER_REAL, &itv, 0) == -1){
		perror("setitimer");
		exit(1);
	}
	prevClock = clock();

		while(1){
			while (((clock() - prevClock) * 10 / CLOCKS_PER_SEC) < 5) {
				if (gotAlarm) {
					gotAlarm = 0;
					displayTimes("START:", true);

				sigCnt++;
				if (sigCnt >= maxSigs) {
				printf("That's all folks\n");
				exit(EXIT_SUCCESS);
				}
			}
		}
			prevClock = clock();
			displayTimes("Main: ", true);
	}
	return EXIT_SUCCESS;
}

static void
displayTimes(const char *msg, bool includeTimer){
	struct itimerval itv;
	static struct timeval start;
	struct timeval curr;
	static int callNum = 0;
	if (callNum == 0)/* Initialize elapsed time meter */
	if (gettimeofday(&start, NULL) == -1){
		perror("gettimeofday");
		exit(1);
	}
	if (callNum % 20 == 0)
		printf("	Elapsed Value nterval\n");

	if (gettimeofday(&curr, NULL) == -1){
			perror("gettimeofday");
			exit(1);
		}
	printf("%-7s %6.2f", msg, curr.tv_sec - start.tv_sec + \
	(curr.tv_usec - start.tv_usec) / 1000000.0);

	if (includeTimer) {
	if (getitimer(ITIMER_REAL, &itv) == -1){
		perror("getitimer");
		exit(1);
	}
	printf(" %6.2f %6.2f", \
	itv.it_value.tv_sec + itv.it_value.tv_usec / 1000000.0, \
	itv.it_interval.tv_sec + itv.it_interval.tv_usec / 1000000.0);
	}

	printf("\n");
	callNum++;

}

static void
sigalrmHandler(int sig)
{
	gotAlarm =1;
}

