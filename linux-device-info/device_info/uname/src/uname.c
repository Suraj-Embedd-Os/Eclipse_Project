/*
 ============================================================================
 Name        : uname.c
 Author      : suraj dev pandit
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <unistd.h>

#if(0)
truct utsname {
               char sysname[];    /* Operating system name (e.g., "Linux") */
               char nodename[];   /* Name within "some implementation-defined
                                     network" */
               char release[];    /* Operating system release
                                     (e.g., "2.6.28") */
               char version[];    /* Operating system version */
               char machine[];    /* Hardware identifier */
           #ifdef _GNU_SOURCE
               char domainname[]; /* NIS or YP domain name */
           #endif
};
#endif

int main(void) {

	struct utsname ust;

	if(uname(&ust) != 0)
	{
		perror("uname()");
		exit(-1);
	}

	printf("Operating system name: %s\n",ust.sysname);
	printf("nodename name: %s\n",ust.nodename);
	printf("Operating system release: %s\n",ust.release);
	printf("OOperating system version: %s\n",ust.version);
	printf("Hardware identifier: %s\n",ust.machine);
	//pintf("IS or YP domain name %s :\n",ust.domainname);



	return EXIT_SUCCESS;
}
