/*
 ============================================================================
 Name        : pthread_create.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#define _REENTRANT
#define _POSIX_C_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include<unistd.h>


void *fun (void *args);

char message[] = "Hello World";

int main(void) {

	int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	                          void *(*start_routine) (void *), void *arg);

	pthread_t 	a_thread;
	int res;

	void  *thread_res;

	if(pthread_create(&a_thread,NULL,fun,message) !=0)
	{
		perror("pthread_create");
		exit(1);
	}

	printf("waiting to join thread\n");
	res= pthread_join(a_thread, &thread_res);

	if(res !=0)
	{
		perror("pthread_join failed");
		exit(1);
	}
	printf("Thread joined, it returned %s\n", (char *)thread_res);
	return EXIT_SUCCESS;
}


void *fun (void *args)
{
	printf("Thread function running args is %s \n,",(char*)args);
	sleep(3);
	strcpy(message, "Bye!");
	pthread_exit("Thank you for the CPU time");
}
