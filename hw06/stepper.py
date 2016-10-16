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
    for k in range(anglerange):
            if(index>3):
                index=0
            onePhase(pins,index)
            sleeptime=float(60.0/(stepsPerRev*rpm))
            time.sleep(sleeptime) #20 steps per second
            index+=1

def main():
    GPIO.cleanup()
    
    setup(pins)
    setAllLow(pins)
    while(1):
        rotateAmount(pins,8,45)
        time.sleep(2)



if __name__ == "__main__":
    main()