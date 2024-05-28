

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include<string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include<string.h>
#include <dirent.h>
#include <sys/types.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
#include "system_info.h"

static int readFromFile(char const *file_name,char *buffer,size_t size)
{
	FILE *file = fopen(file_name,"r");
	if(file == 0)
	{
		printf("unable to open %s ",file_name);
		perror("");
		return -1;
	}

	fgets(buffer,size,file);
	fclose(file);
	//removing new line
    buffer[strcspn(buffer, "\n")] = 0;

	return 0;
}

static int readFromFile2(char const *file_name,char *buffer,size_t size)
{
	int fd=open(file_name,O_RDONLY);

	if(fd == -1)
	{
		printf("unable to open %s ",file_name);
		perror("");
		return -1;
	}

	size_t read_size=0;
	if((read_size=read(fd,buffer,size)) == -1 )
	{
		printf("unable to read from %s ",file_name);
		perror("");
		return -1;
	}
	buffer[read_size]='\0';

	return 0;

}

void get_bios_info(struct bios_info *bios)
{
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

			printf("bios_date :%s \n",bios->bios_date);
			printf("bios_release :%s \n",bios->bios_release);
			printf("bios_vendor :%s \n",bios->bios_vendor);
			printf("bios_version :%s \n",bios->bios_version);
			printf("board_name :%s \n",bios->board_name);
			printf("board_serial :%s \n",bios->board_serial);
			printf("board_vendor :%s \n",bios->board_vendor);
			printf("board_vendor :%s \n",bios->board_version);
			printf("product_family :%s \n",bios->product_family);
			printf("product_name :%s \n",bios->product_name);
			printf("product_serial :%s \n",bios->product_serial);
			printf("product_version :%s \n",bios->product_version);
}

void get_os_info(struct os_info *os){

	struct utsname ust;

	if(uname(&ust) != 0)
	{
		perror("uname()");
		exit(-1);
	}

	strcpy(os->sysname,ust.sysname);
	strcpy(os->nodename,ust.nodename);
	strcpy(os->release,ust.release);
	strcpy(os->version,ust.version);
	strcpy(os->machine,ust.machine);

	printf("Operating system name: %s\n",os->sysname);
	printf("nodename name: %s\n",os->nodename);
	printf("Operating system release: %s\n",os->release);
	printf("OOperating system version: %s\n",os->version);
	printf("Hardware identifier: %s\n",os->machine);
}

void get_cpu_info(struct cpu_info *cpu)
{
	// Read CPU information from /proc/cpuinfo
	    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
	    if (cpuinfo == NULL) {
	        perror("Error opening file /proc/cpuinfo");
	        return;
	    }
	    char line[DATA_SIZE];
	    char cpu_name[DATA_SIZE];
	    while (fgets(line, DATA_SIZE, cpuinfo) != NULL) {
	            if (strncmp(line, "model name", 10) == 0) {
	            	//fgets(cpu_name,DATA_SIZE,cpuinfo);
	                //readFromFile("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", cpu_name, DATA_SIZE);
	            	strcpy(cpu_name,line+12);
	            } else if (strncmp(line, "cpu cores", 9) == 0) {
	                sscanf(line, "cpu cores : %d", &cpu->num_core);
	            } else if (strncmp(line, "siblings", 8) == 0) {
	                sscanf(line, "siblings : %d", &cpu->num_thread);
	            }
	        }
	    strcpy(cpu->cpu_name,cpu_name);
	    fclose(cpuinfo);



	    // Read max qualified speed from /proc/cpuinfo
	    readFromFile("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", cpu_name, DATA_SIZE);
	    sscanf(cpu_name, "%f", &cpu->max_qualified_speed);

	    // Read max turbo boost speed from /proc/cpuinfo
	    readFromFile("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", cpu_name, DATA_SIZE);
	    sscanf(cpu_name, "%f", &cpu->max_turbo_boost_speed);

	    // Print CPU information
	    printf("Name: %s\n", cpu->cpu_name);
	    printf("Cores: %d\n", cpu->num_core);
	    printf("Threads: %d\n", cpu->num_thread);
	    printf("Max Qualified Speed: %.2f MHz\n", cpu->max_qualified_speed);
	    printf("Max Turbo Boost Speed: %.2f MHz\n", cpu->max_turbo_boost_speed);


}


void get_mem_info(struct mem_info *mem)
{

}

void get_disk_drive_info(struct disk_drive_info *disk)
{

	//DIR *opendir(const char *name);
	DIR *dir =opendir("/sys/block");

	if(dir == NULL)
	{
		perror("unable to open /sys/block");
		return ;
	}

	//struct dirent *readdir(DIR *dirp);
	 /* struct dirent {
	               ino_t          d_ino;
	               off_t          d_off;
	               unsigned short d_reclen;
	               unsigned char  d_type;

	               char           d_name[256];
	           };*/


	struct dirent * entry;

	while((entry = readdir(dir)) != NULL)
	{
		if(strcmp(entry->d_name,".") == 0 ||strcmp(entry->d_name,"..") == 0 || \
		  strncmp(entry->d_name,"loop",strlen("loop"))==0)
			continue;

		// Print device name
		 printf("Device: %s\n", entry->d_name);
		 char vendor[DATA_SIZE];
		 char model[DATA_SIZE];
		 char serial[DATA_SIZE];
		 char firmware[DATA_SIZE];
		 char size[DATA_SIZE];
		 char test_buffer[DATA_SIZE];

		 snprintf(vendor,DATA_SIZE,(const char *)"/sys/block/%s/device/vendor",entry->d_name);
		 snprintf(model,DATA_SIZE,(const char *)"/sys/block/%s/device/model",entry->d_name);
		 snprintf(serial,DATA_SIZE,(const char *)"/sys/block/%s/device/serial",entry->d_name);
		 snprintf(firmware,DATA_SIZE,(const char *)"/sys/block/%s/device/firmware",entry->d_name);
		 snprintf(size,DATA_SIZE,(const char *)"/sys/block/%s/size",entry->d_name);

		 if( readFromFile2(vendor,disk->vendor,DATA_SIZE) != -1)
		 {
			 printf("vendor name :%s\n",disk->vendor);
		 }
		 if( readFromFile2(model,disk->model_number,DATA_SIZE) != -1)
		 {
			 printf("model name :%s\n",disk->model_number);
		 }
		 if( readFromFile2(serial,disk->vendor,DATA_SIZE) != -1)
		 {
			 printf("serial_no :%s\n",disk->serial_no);
		 }
		 if( readFromFile2(size,test_buffer,DATA_SIZE) != -1)
		 {
			 disk->size_bytes = strtoull(test_buffer, NULL, 10);
			  printf("Size: %llu bytes\n",  disk->size_bytes);

			    // Convert size to human-readable format (MB)
			  disk->marketed_size =  disk->size_bytes / (1024.0 * 1024.0);
			  printf("Marketed Size: %.2f MB\n", disk->marketed_size);
		 }

	}

}


