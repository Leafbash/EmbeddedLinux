import Adafruit_BBIO.GPIO as GPIO
import time
import math

rate=60
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

def rotateAmount(pins,steps):
    for k in range(steps):
        for index in range(len(pins)):
            onePhase(pins,index)
            time.sleep(1/rate) #60 steps per second

def main():
    GPIO.cleanup()

    setup(pins)
    setAllLow(pins)




if __name__ == "__main__":
    main()