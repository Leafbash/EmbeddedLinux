import Adafruit_BBIO.ADC as ADC
 
ADC.setup()
value = ADC.read("AIN0")
value = ADC.read("AIN0")
println(value)