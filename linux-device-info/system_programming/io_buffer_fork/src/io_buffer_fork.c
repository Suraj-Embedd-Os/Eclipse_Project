#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


int
main(int argc, char *argv[])
{
	printf("Hello world\n");
	write(STDOUT_FILENO, "Ciao\n", 5);
	if (fork() == -1){
	perror("fork");
	exit(-1);
	}
	/* Both child and parent continue execution here */
	exit(EXIT_SUCCESS);
}
