#include<stdio.h>
#include <sys/wait.h>
#include<unistd.h>
#include<string.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
int numChildren, j;
pid_t childPid;
if (argc > 1 && strcmp(argv[1], "--help") == 0){
	printf("%s [num-children]\n", argv[0]);
	return -1;
	}
numChildren = (argc > 1) ? atoi(argv[1]): 1;
setbuf(stdout, NULL);
/* Make stdout unbuffered */
for (j = 0; j < numChildren; j++) {
switch (childPid = fork()) {
case -1:
perror("fork");
exit(-1);
case 0:
printf("%d child\n", j);
_exit(0);
default:
printf("%d parent\n", j);
wait(NULL);
break;
}
/* Wait for child to terminate */
}
exit(EXIT_SUCCESS);
}
