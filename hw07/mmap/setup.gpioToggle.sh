#!/bin/bash
# Set up gpio 7 to read and gpio 3 to write
cd /sys/class/gpio
echo 115 > export
echo 113 > export
echo in  > gpio113/direction
echo out > gpio115/direction
