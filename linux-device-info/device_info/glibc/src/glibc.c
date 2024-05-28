/*
 ============================================================================
 Name        : glibc.c
 Author      : suraj dev pandit
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 *
 *     //**********scanf********************
 *     int scanf(const char *format, ...);
       int fscanf(FILE *stream, const char *format, ...);
       int sscanf(const char *str, const char *format, ...);

       #include <stdarg.h>

       int vscanf(const char *format, va_list ap);
       int vsscanf(const char *str, const char *format, va_list ap);
       int vfscanf(FILE *stream, const char *format, va_list ap);

//**********printf********************
       int printf(const char *format, ...);
       int fprintf(FILE *stream, const char *format, ...);
       int dprintf(int fd, const char *format, ...);
       int sprintf(char *str, const char *format, ...);
       int snprintf(char *str, size_t size, const char *format, ...);

       #include <stdarg.h>

       int vprintf(const char *format, va_list ap);
       int vfprintf(FILE *stream, const char *format, va_list ap);
       int vdprintf(int fd, const char *format, va_list ap);
       int vsprintf(char *str, const char *format, va_list ap);
       int vsnprintf(char *str, size_t size, const char *format, va_list ap);

        //
         * fgetc, fgets, getc, getchar, ungetc


 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>

void my_printf(const char *format,...)
{
	va_list args;
	va_start(args,format);

	vprintf(format,args);

	va_end(args);
}

void my_fprintf(FILE *stream, const char *format, ...)
{
	va_list args;
	va_start(args,format);

	vfprintf(stream,format,args);

	va_end(args);
}

void my_sprintf(char *str, const char *format, ...)
{
	va_list args;
	va_start(args,format);

	vsprintf(str,format,args);

	va_end(args);
}

void my_scanf(const char *format, ...)
{
	va_list args;
	va_start(args,format);
	vscanf(format,args);
	va_end(args);
}


int main(void) {

	/*int fd = open("./testfile",O_WRONLY|O_CREAT);

	if(fd == -1)
	{
		printf("una\n");
		return -1;
	}
	int d=5;
	dprintf(fd,"test string %d",d);

	close(fd);*/

	/*FILE *fp = fopen("./testfile","r");

	if(fp == NULL)
	{
		perror("fopen");
		return -1;

	}

	char arr[20];
	fscanf(fp,"%s",arr);

	printf("%s",arr);*/

	/*char a[]="hello 123";
	char buff[20];
	int b;

	sscanf(a,"%s %d",buff,&b);

	printf("%s %d ",buff,b);*/

	int a,b;
	my_printf("enter two number ");
	my_scanf("%d %d",&a,&b);



	my_printf("%d %d ",a,b);

	return EXIT_SUCCESS;
}
