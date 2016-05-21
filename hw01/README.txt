--Summary--
This is a simple Etch-a-Sketch program written in C

--Required libraries--
ncurses

--Installation--
compile using the following command

g++ etch.c -o etchc -l ncurses

--Run the program--
./etchc


==========
Comments by Prof. Yoder
The etchc file runs fine.
The g++ command get the following error:
g++ etch.c -o etchc -lncurses
etch.c:11:25: fatal error: /lib/GPIOoo.h: No such file or directory
 #include </lib/GPIOoo.h>
 
 What am I missing?
 
Grade:  9/10

Fix the g++ command and I'll fix your grade.
