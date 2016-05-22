class TMP101Sensor{
    private:
        int I2CBUS;
        int I2CADDRESS;

    public:
        TMP101Sensor(int bus, int address);
        int ReadTemp();
};