#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
int main()
{
	int piped[2];
	char some_data[]="hello world";
	char buffer[BUFSIZ + 1];

	memset(buffer,0,sizeof(buffer));

	if(pipe(piped) == 0){
		int fork_create = fork();
		if(fork_create == -1){
			perror("fork_create");
			exit(EXIT_FAILURE);
		}
		else if(fork_create == 0)
		{
			//close(piped[1]);
			sprintf(buffer,"%d",piped[0]);
			execl("pipe4","pipe4",buffer,0);
			exit(EXIT_FAILURE);
		}
		else{
			//close(piped[0]);
			int wr_data = write(piped[1],some_data,sizeof(some_data));
			printf("Number of %d bytes written\n",wr_data);
		}

	}


	exit(EXIT_FAILURE);
}
