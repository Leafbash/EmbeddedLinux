--description--
This is an etch-a-sketch program.
Prompts ask for window height, width and input method.
keyboard x, will exit the program.
In keyboard mode, w,a,s,d are used for movement.
--hardware setup--
A fritzing file is included to show how to set up the hardware.
pull up resistors must be used on the inputs.
The following pins are used
Up button -- P9_23
Down Button -- P9_15
Right Button -- P8_26
Left Button -- P9_12

--installation--
run install.sh to compile the program
--required libraries--
Derek Molloy's GPIO library is used and included in the compile script
The ncurses library is also used.
--run--
sudo ./etchv2.o
