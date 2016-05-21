import Adafruit_BBIO.ADC as ADC
import time
# 9_32 Vdd // 9_34 GNDA
ADC.setup()
time.sleep(0.25)
value = ADC.read_raw("AIN1")
time.sleep(0.25)
value = ADC.read_raw("AIN1")
time.sleep(0.25)
print(float(value))