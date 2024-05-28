

#ifndef __GET_BIOS_INFO_H__
#define __GET_BIOS_INFO_H__

#define DATA_SIZE 100


struct bios_info{
	//bios informations
	char bios_date[DATA_SIZE];
	char bios_release[DATA_SIZE];
	char bios_vendor[DATA_SIZE];
	char bios_version[DATA_SIZE];
	char board_asset_tag[DATA_SIZE];
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

#endif
