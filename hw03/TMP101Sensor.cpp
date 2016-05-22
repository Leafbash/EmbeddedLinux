#include <stdlib.h>
#include <linux/i2c.h>
#include<linux/i2c-dev.h>
#include "TMP101Sensor.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stropts.h>
#include <stdio.h>
#include <iostream>
#include <math.h>

#define MAX_BUS 64

using namespace std;

TMP101Sensor::TMP101Sensor(int bus, int address)
{
	I2CBUS = bus;
	I2CADDRESS = address;
	
}
int TMP101Sensor::ReadTemp()
{
	char namebuf[MAX_BUS];
	snprintf(namebuf, sizeof(namebuf), "/dev/i2c-%d", I2CBUS);
	int file;
    return 0;
}
