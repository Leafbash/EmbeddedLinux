/* A Simple GPIO application
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <ncurses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "GPIO.h"
#include<iostream>

using namespace exploringBB;
using namespace std;

int main(){
   GPIO outGPIO(49), inGPIO(45);

   // Basic Output - Flash the LED 10 times, once per second
   outGPIO.setDirection(OUTPUT);
   for (int i=0; i<10; i++){
      outGPIO.setValue(HIGH);
      usleep(500000); //micro-second sleep 0.5 seconds
      outGPIO.setValue(LOW);
      usleep(500000);
   }
   // Basic Input example
   inGPIO.setDirection(INPUT);
   cout << "The value of the input is: "<< inGPIO.getValue() << endl;

   // Fast write to GPIO 1 million times
   outGPIO.streamOpen();
   for (int i=0; i<1000000; i++){
      outGPIO.streamWrite(HIGH);
      outGPIO.streamWrite(LOW);
   }
   outGPIO.streamClose();

   return 0;
}
