#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "TMP101Sensor.h"
#include <linux/types.h>
#include <inttypes.h>
int main()
{
	TMP101Sensor tempSensor(2,72);
	tempSensor.ReadTemp();
	uint16_t high = 0x1a00; 
	uint16_t low = 0x0100;
	tempSensor.SetTempLimit(high,low);
}