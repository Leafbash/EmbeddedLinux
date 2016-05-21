#include <stdlib.h>
#include "i2c-dev.h"
#include "TMP101Sensor.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <errno.h>
#include <cstring>
#include <linux/types.h>
#include <inttypes.h>

#define MAX_BUS 64
#define TMPREG 0x40
#define TMPADDRESS 0x40
#define POINTERREG 0x00
using namespace std;

TMP101Sensor::TMP101Sensor(int bus, int address)
{
	i2cbus = bus;
	i2caddress = address;
	char filename[20];
	
}
int TMP101Sensor::ReadTemp()
{
	char *end;
	int res,res2,size, file;
	int daddress=0;
	//char filename[20];

	size = I2C_SMBUS_BYTE;

	sprintf(filename, "/dev/i2c-%d", i2cbus);
	file = open(filename, O_RDWR);
	if (file<0) {
		if (errno == ENOENT) {
			fprintf(stderr, "Error: Could not open file "
				"/dev/i2c-%d: %s\n", i2cbus, strerror(ENOENT));
		} else {
			fprintf(stderr, "Error: Could not open file "
				"`%s': %s\n", filename, strerror(errno));
			if (errno == EACCES)
				fprintf(stderr, "Run as root?\n");
		}
		exit(1);
	}

	if (ioctl(file, I2C_SLAVE, i2caddress) < 0) {
		fprintf(stderr,
			"Error: Could not set i2caddress to 0x%02x: %s\n",
			i2caddress, strerror(errno));
		return -errno;
	}

	res = i2c_smbus_write_byte(file, daddress);
	if (res < 0) {
		fprintf(stderr, "Warning - write failed, filename=%s, daddress=%d\n",
			filename, daddress);
	}

	res = i2c_smbus_read_byte_data(file, daddress);
	close(file);

	if (res < 0) {
		fprintf(stderr, "Error: Read failed, res=%d\n", res);
		exit(2);
	}

	printf("0x%02x",res);


    return 0;
}
int TMP101Sensor::SetTempLimit(uint16_t *high, uint16_t low)
{
		char *end;
	int file;
	int res,res2,size;
	int daddress=0;
	InitI2c(&file);
	res = i2c_smbus_write_byte(file, ADDR_CONFIG);
		if (res < 0) {
		fprintf(stderr, "1Warning - write failed, filename=%s, daddress=%d\n",
			filename, daddress);
	}
	res = i2c_smbus_write_byte(file,MODE_TM);
	if (res < 0) {
		fprintf(stderr, "2Warning - write failed, filename=%s, daddress=%d\n",
			filename, daddress);
	}
	
	res = i2c_smbus_write_i2c_block_data(file,ADDR_THIGH, 16, (uint8_t *) high);
	if (res < 0) {
		fprintf(stderr, "4Warning - write failed,high=0x%02x filename=%s, daddress=%d\n",
			filename, daddress);
	}
	close(file);
	return 0;
}


int TMP101Sensor::InitI2c(int *file)
{
	//char filename[20];
	sprintf(filename, "/dev/i2c-%d", i2cbus);
	*file = open(filename, O_RDWR);
	if (*file<0) {
		if (errno == ENOENT) {
			fprintf(stderr, "Error: Could not open file "
				"/dev/i2c-%d: %s\n", i2cbus, strerror(ENOENT));
		} else {
			fprintf(stderr, "Error: Could not open file "
				"`%s': %s\n", filename, strerror(errno));
			if (errno == EACCES)
				fprintf(stderr, "Run as root?\n");
		}
		exit(1);
	}

	if (ioctl(*file, I2C_SLAVE, i2caddress) < 0) {
		fprintf(stderr,
			"Error: Could not set i2caddress to 0x%02x: %s\n",
			i2caddress, strerror(errno));
		return -errno;
	}

}
// // Writes block of data to the display
// static int write_block(int file, __u16 *data) {
// 	int res;
// #ifdef BICOLOR
// 	res = i2c_smbus_write_i2c_block_data(file, 0x00, 16, 
// 		(__u8 *)data);
// 	return res;
// #else
// /*
//  * For some reason the single color display is rotated one column, 
//  * so pre-unrotate the data.
//  */
// 	int i;
// 	__u16 block[I2C_SMBUS_BLOCK_MAX];
// //	printf("rotating\n");
// 	for(i=0; i<8; i++) {
// 		block[i] = (data[i]&0xfe) >> 1 | 
// 			   (data[i]&0x01) << 7;
// 	}
// 	res = i2c_smbus_write_i2c_block_data(file, 0x00, 16, 
// 		(__u8 *)block);
// 	return res;
// #endif
// }