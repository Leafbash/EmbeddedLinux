import Adafruit_BBIO.ADC as ADC
import time
# 9_32 Vdd // 9_34 GNDA

import Adafruit_BBIO.GPIO as GPIO
import time
import math
stepsPerRev=2048.0
rpm=4
rate=20
pins=["P8_11", "P8_12", "P8_15", "P8_16"]

def setAllLow(pins):
    for k in pins:
        GPIO.output(k, GPIO.LOW)

def setup(pins):
    for k in pins:
        GPIO.setup(k,GPIO.OUT)
    ADC.setup()

def onePhase(pins, index):
    for k in range(len(pins)):
        if k == index:
            GPIO.output(pins[k],GPIO.HIGH)
        else:
            GPIO.output(pins[k],GPIO.LOW)

def rotateAmount(pins,rpm,angle):
    index=0
    anglerange=int((angle/360.0)*stepsPerRev)
    print(anglerange)
    for k in range(abs(anglerange)):
        if(index>3):
            index=0
        if(index<0):
            index=3
        onePhase(pins,index)
        sleeptime=float(60.0/(stepsPerRev*rpm))
        time.sleep(sleeptime) #20 steps per second
        if(anglerange>0):
            index+=1
        else:
            index-=1

def main():
    GPIO.cleanup()
    
    setup(pins)
    setAllLow(pins)
    norm1=ADC.read_raw("AIN0")
    norm2=ADC.read_raw("AIN1")
    while(1):
        value1 = abs(ADC.read_raw("AIN1"))
        value2 = abs(ADC.read_raw("AIN0"))
        print(value1)
        print(value2)
        
        if(value2>value1):
            rotateAmount(pins,6,5) 

        else:
            rotateAmount(pins,6,-5)
        

if __name__ == "__main__":
    main()
