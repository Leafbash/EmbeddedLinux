--Hardware--
1. This program is designed to work with the ULN2003 single pole stepper motor controller (with a single pole stepper)
2. Connect the ULN2003 with the following configuration
"1N1" --> "P8_11"
"1N2" --> "P8_12"
"1N3" --> "P8_15"
"1N4" --> "P8_16"

--Required software libraries--
1. python version 3.3
2. The Adafruit GPIO library for the beaglebone (specifically: Adafruit_BBIO.GPIO)

--Run--
1. run: python stepperTrack.py