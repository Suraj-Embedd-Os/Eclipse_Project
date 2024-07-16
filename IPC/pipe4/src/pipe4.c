/*
 ============================================================================
 Name        : pipe4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc , char *argv[])
{
	int data_processed;
	char buffer[BUFSIZ + 1];
	int file_descriptor;
	memset(buffer,0, sizeof(buffer));
	sscanf(argv[1], "%d", &file_descriptor);

	data_processed = read(file_descriptor, buffer, BUFSIZ);
	printf("%d - read %d bytes: %s\n", getpid(), data_processed, buffer);

	return EXIT_SUCCESS;
}
