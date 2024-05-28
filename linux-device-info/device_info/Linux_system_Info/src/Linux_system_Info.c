/*
 ============================================================================
 Name        : Linux_system_Info.c
 Author      : suraj dev pandit
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "system_info.h"

int main(void) {
	struct bios_info b_info;
	struct os_info   o_info;
	struct cpu_info  c_info;
	struct disk_drive_info d_info;

	printf("*******************OS info ************\n\r");
	get_os_info(&o_info);

	printf("*******************BIOS info ************\n\r");
	get_bios_info(&b_info);

	printf("*******************CPU info ************\n\r");
	get_cpu_info(&c_info);

	printf("*******************Disk Driver info ************\n\r");
	get_disk_drive_info(&d_info);

	return EXIT_SUCCESS;
}
