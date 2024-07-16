#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
int main()
{
	int piped[2];
	char some_data[]="hello world";
	char read_buff[20];

	memset(read_buff,0,sizeof(read_buff));

	if(pipe(piped) == 0){
		int fork_create = fork();
		if(fork_create == -1){
			perror("fork_create");
			exit(EXIT_FAILURE);
		}
		else if(fork_create == 0)
		{
			close(piped[1]);
			int rd_data = read(piped[0],read_buff,sizeof(read_buff));
			printf("Number of %d bytes read and data is %s \n",rd_data,read_buff);
		}
		else{
			close(piped[0]);
			int wr_data = write(piped[1],some_data,sizeof(some_data));
			printf("Number of %d bytes written\n",wr_data);
		}

	}


	exit(EXIT_FAILURE);
}
