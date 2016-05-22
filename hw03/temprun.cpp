#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include "TMP101Sensor.h"

int main()
{
	TMP101Sensor tempSensor(2,0x40);
	tempSensor.ReadTemp();
}