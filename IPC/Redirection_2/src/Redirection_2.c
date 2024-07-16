/*
 ============================================================================
 Name        : Redirection_2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc ,char *argv[]) {

	char *filename;
	if(argc != 2){
		fprintf(stderr,"Usage error upperfile file case\n");
		exit(1);
	}

	filename=argv[1];

	if(!freopen(filename,"r",stdin)){
		fprintf(stderr,"could not redirect stdin from file %s\n",filename);
	}

	execl("./upper","upper",0);
	perror("could not exec ./upper");
	exit(3);

	return EXIT_SUCCESS;
}
