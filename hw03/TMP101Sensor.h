#include <inttypes.h>
#define TMP101_I2C_BUFFER 0x02
#define ADDR_TEMP 0x00
#define ADDR_CONFIG 0x01
#define ADDR_TLOW 0x02
#define ADDR_THIGH 0x03

#define MODE_SD 0x01 //shutdown mode
#define MODE_TM 0x02 //thermostat mode
#define MODE_POL 0x03 //Polarity
#define MODE_F0 0x04 //Fault queue
#define MODE_F1 0x05 //Fault queue
#define MODE_R0 0x06 //Converter resolution 9-12 bits
#define MODE_R1 0x07 //Converter resolution 9-12 bits

class TMP101Sensor{
    private:
        int i2cbus;
        int i2caddress;
        char filename[20];
        
    public:
        TMP101Sensor(int bus, int address);
        int ReadTemp();
        int SetTempLimit(uint16_t *high,uint16_t low);
        int InitI2c(int *file);
};