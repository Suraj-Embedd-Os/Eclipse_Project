

#ifndef __SYSTEM_INFO_H__
#define __SYSTEM_INFO_H__


#define DATA_SIZE 256


struct bios_info{
	//bios informations
	char bios_date[DATA_SIZE];
	char bios_release[DATA_SIZE];
	char bios_vendor[DATA_SIZE];
	char bios_version[DATA_SIZE];
	// Print motherboard information
	char board_name[DATA_SIZE];
	char board_serial[DATA_SIZE];
	char board_vendor[DATA_SIZE];
	char board_version[DATA_SIZE];
	char product_family[DATA_SIZE];
	char product_name[DATA_SIZE];
	char product_serial[DATA_SIZE];
	char product_version[DATA_SIZE];

};

struct os_info{
    char sysname[DATA_SIZE];    /* Operating system name (e.g., "Linux") */
    char nodename[DATA_SIZE];   /* Name within "some implementation-defined
                          network" */
    char release[DATA_SIZE];    /* Operating system release
                          (e.g., "2.6.28") */
    char version[DATA_SIZE];    /* Operating system version */
    char machine[DATA_SIZE];    /* Hardware identifier */
};

struct cpu_info{
	char cpu_name[DATA_SIZE];
	int num_core;
	int num_thread;
	float max_qualified_speed;
	float max_turbo_boost_speed;
};


struct mem_info{
	char tl_physical_mem[DATA_SIZE];
	char max_support_mem[DATA_SIZE];
	char no_of_mem_module[DATA_SIZE];
	char no_of_dimm_slots[DATA_SIZE];
};

struct disk_drive_info{
	char vendor[DATA_SIZE];
	char model_number[DATA_SIZE];
	char serial_no[DATA_SIZE];
	char firmware_rev[DATA_SIZE];
	unsigned long long size_bytes;
	double marketed_size;

};

void get_bios_info(struct bios_info *bios);
void get_os_info(struct os_info *os);
void get_cpu_info(struct cpu_info *cpu);
void get_mem_info(struct mem_info *mem);
void get_disk_drive_info(struct disk_drive_info *disk);
#endif

