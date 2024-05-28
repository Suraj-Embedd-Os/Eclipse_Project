/*
 ============================================================================
 Name        : get_bios_info.c
 Author      : suraj dev pandit
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "get_bios_info.h"

#define MAX_BUFF 256
#define DATA_SIZE 100



static int readFromFile(char const *file_name,char *buffer,size_t size);
static void get_bios_info(struct bios_info *bios);

int main(void)
{
	struct bios_info bios;

	get_bios_info(&bios);


	printf("bios_date :%s \n",bios.bios_date);
	printf("bios_release :%s \n",bios.bios_release);
	printf("bios_vendor :%s \n",bios.bios_vendor);
	printf("bios_version :%s \n",bios.bios_version);
	printf("board_asset_tag :%s \n",bios.board_asset_tag);
	printf("board_name :%s \n",bios.board_name);
	printf("board_serial :%s \n",bios.board_serial);
	printf("board_vendor :%s \n",bios.board_vendor);
	printf("board_vendor :%s \n",bios.board_version);
	printf("product_family :%s \n",bios.product_family);
	printf("product_name :%s \n",bios.product_name);
	printf("product_serial :%s \n",bios.product_serial);
	printf("product_version :%s \n",bios.product_version);



	return EXIT_SUCCESS;
}

static int readFromFile(char const *file_name,char *buffer,size_t size)
{

	/*if (chmod(file_name, 0444) != 0) {
	        perror("chmod");
	        return 1;
	    }*/

	FILE *file = fopen(file_name,"r");

	if(file == 0)
	{
		perror("file_name\n");
		return -1;
	}

	fgets(buffer,size,file);
	fclose(file);

	return 0;
}

static void get_bios_info(struct bios_info *bios)
{
	//
		if(readFromFile("/sys/class/dmi/id/bios_date",bios->bios_date,DATA_SIZE) !=0)
		{
			printf("unable to fetch bios_date\n");
			//return 1;
		}

		if(readFromFile("/sys/class/dmi/id/bios_release",bios->bios_release,DATA_SIZE) !=0)
		{
			printf("unable to fetch bios_release\n");
			//return 1;
		}
		if(readFromFile("/sys/class/dmi/id/bios_vendor",bios->bios_vendor,DATA_SIZE) !=0)
		{
			printf("unable to fetch bios_vendor\n");
			//return 1;
		}
		if(readFromFile("/sys/class/dmi/id/bios_version",bios->bios_version,DATA_SIZE) !=0)
		{
			printf("unable to fetch bios_version\n");
			//return 1;
		}
		if(readFromFile("/sys/class/dmi/id/board_asset_tag",bios->board_asset_tag,DATA_SIZE) !=0)
		{
			printf("unable to fetch board_asset_tag\n");
		}
		if(readFromFile("/sys/class/dmi/id/board_name",bios->board_name,DATA_SIZE) !=0)
		{
			printf("unable to fetch board_name\n");
		}
		if(readFromFile("/sys/class/dmi/id/board_serial",bios->board_serial,DATA_SIZE) !=0)
		{
			printf("unable to fetch board_serial\n");
		}
		if(readFromFile("/sys/class/dmi/id/board_vendor",bios->board_vendor,DATA_SIZE) !=0)
		{
			printf("unable to fetch board_vendor\n");
		}
		if(readFromFile("/sys/class/dmi/id/board_version",bios->board_version,DATA_SIZE) !=0)
		{
			printf("unable to fetch board_version\n");
		}
		if(readFromFile("/sys/class/dmi/id/product_family",bios->product_family,DATA_SIZE) !=0)
		{
			printf("unable to fetch product_family\n");
		}
		if(readFromFile("/sys/class/dmi/id/product_family",bios->product_name,DATA_SIZE) !=0)
		{
			printf("unable to fetch product_name\n");
		}
		if(readFromFile("/sys/class/dmi/id/product_serial",bios->product_serial,DATA_SIZE) !=0)
		{
			printf("unable to fetch product_serial\n");
		}
		if(readFromFile("/sys/class/dmi/id/product_version",bios->product_version,DATA_SIZE) !=0)
		{
			printf("unable to fetch product_version\n");
		}

		//return 0;
}
