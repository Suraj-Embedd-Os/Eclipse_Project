/*
 ============================================================================
 Name        : exec_family.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	printf("running ps with execlp\n");
	execlp("ps","ps","-ax",NULL);
	return EXIT_SUCCESS;
}
