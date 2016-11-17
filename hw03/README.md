--Setup--
--Etch-a-Sketch with matrix--
    0. The code for this is contained in etchv3.cpp
    1. wire up the system correctly.
        GPIO:
        UP_Button --> GPIO_49
        DOWN_Button --> GPIO_48
        RIGHT_Button --> GPIO_61
        LEFT_Button --> GPIO_60
    MATRIX:
        I2C2_SCL --> P9_19
        I2C2_SDA --> P9_20
    2. run "installMatrix.sh" to compile the program
    3. run "matrixruncpp" to 
--Temperature program--
    0. Wire up the system correctly
    TMP101:
        I2C2_SCL --> P9_19
        I2C2_SDA --> P9_20
        Note: ADD0 should be pulled high on one TMP101 chip and pulled low on the other
    1. To set the temperature limit of the tmp101 run "tempLimitSetBash"
    The following is the command structure
        ./tempLimitSetBash <tmpaddress> <lowlimit> <highlimit>
    tmp address will be either 0x48 or 0x40 depending on the state of ADD0.
    Enter each parameter as a hexvalue (0x notation)
    2. To read the temperature and wait for an alert run "tempReadConverBash"