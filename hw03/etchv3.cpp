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

#include <errno.h>


#include <stdlib.h>

#include "i2c-dev.h"
#include "i2cbusses.h"
#include <fcntl.h>
using namespace exploringBB;
using namespace std;

#define MAX_BUF 64
    __u16 screenState[]={0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void set_gpio(void);
void enable_outputs(void);
void initGpio(void);
int addToGrid(int x,int y,int file);
int initMatrix(int file);
int initI2c(int i2cbus,int address,int file);

GPIO UPBTN(49),DOWNBTN(48),RIGHTBTN(61),LEFTBTN(60); //GPIO objects, these are GPIO numbers(not pin numbers)

int main(){
    WINDOW *my_win;
    initscr();
    int y=0;
    int  x=0;
    int height, width,input_method,down_val,up_val,right_val,left_val;
    chtype str = 'X'; //Character to use for marking the screen  
    
    int maxx=0, maxy=0;
    //matrix values
    int res, i2cbus, address, file;
    
    file= initI2c(i2cbus,address,file);
	initMatrix(file);
    for(int i=0;i<8;i++)
    
    UPBTN.setDirection(INPUT);
    DOWNBTN.setDirection(INPUT);
    RIGHTBTN.setDirection(INPUT);
    LEFTBTN.setDirection(INPUT);
    width=8;
    height=8;
    noecho();
    
    my_win = create_newwin(height, width, 0, 0);
    getmaxyx(my_win,maxx,maxy); //get window size for boundaries
    
while(1)
{
    if(!UPBTN.getValue()) //check for a button press, active low
    {
        if(y>0)
        {
            y--;
            mvaddch(y, x, str);
            addToGrid(x,y,file);
        }
        while(!UPBTN.getValue()) //wait for button release to continue
        {

        }                
    }
    else if(!DOWNBTN.getValue())
    {
        if(y<maxy)
        {
            y++;
            mvaddch(y, x, str);
            addToGrid(x,y,file);  
        }
        while(!DOWNBTN.getValue())
        {

        }            
    }
    else if(!RIGHTBTN.getValue())
    {
        if(x<maxx)
        {
            x++;
            mvaddch(y, x, str);
            addToGrid(x,y,file);
        }
        while(!RIGHTBTN.getValue())
        {

        }  
    }
    else if(!LEFTBTN.getValue())
    {
        if(x>0)
        {
            x--;
            mvaddch(y, x, str);
            addToGrid(x,y,file);
        }
        while(!LEFTBTN.getValue())
        {

        }  
    }
refresh();
}

    refresh();
    getch();
    endwin();
    return 0;
}

/**
create_newin creates a window of specified size
Note: This function was pulled from 
http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/windows.html
**/
WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}
/**
destroy_win removes the specified window
Note: This function was pulled from 
http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/windows.html
**/
void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}
//matrix functions below
static int write_block(int file, __u16 *data) {
	int res;
#ifdef BICOLOR
	res = i2c_smbus_write_i2c_block_data(file, 0x00, 16, 
		(__u8 *)data);
	return res;
#else
/*
 * For some reason the single color display is rotated one column, 
 * so pre-unrotate the data.
 */
	int i;
	__u16 block[I2C_SMBUS_BLOCK_MAX];
//	printf("rotating\n");
	for(i=0; i<8; i++) {
		block[i] = (data[i]&0xfe) >> 1 | 
			   (data[i]&0x01) << 7;
	}
	res = i2c_smbus_write_i2c_block_data(file, 0x00, 16, 
		(__u8 *)block);
	return res;
#endif
}
int initI2c(int i2cbus,int address,int file)
{
	char filename[20];
	i2cbus = 2;
	address=0x70;
	sprintf(filename, "/dev/i2c-%d", i2cbus);
	file = open(filename, O_RDWR);
	if (file<0) {
		if (errno == ENOENT) {
			fprintf(stderr, "Error: Could not open file "
				"/dev/i2c-%d: %s\n", i2cbus, strerror(ENOENT));
		} else {
			fprintf(stderr, "Error: Could not open file "
				"`%s': %s\n", filename, strerror(errno));
			if (errno == EACCES)
				fprintf(stderr, "Run as root?\n");
		}
		exit(1);
	}

	if (ioctl(file, I2C_SLAVE, address) < 0) {
		fprintf(stderr,
			"Error: Could not set i2caddress to 0x%02x: %s\n",
			address, strerror(errno));
		return -errno;
	}
	return file;
}
int addToGrid(int x,int y,int file)
{
    if(x>7 || y>7)
    return 0;
    int mody = y;
	screenState[x] |= 0x0001 << mody;
    
	//printf("this: 0x%02x",screenState[i]);
	write_block(file,screenState);
	usleep(100000);
	return 0;
}
int initMatrix(int file)
{
	i2c_smbus_write_byte(file, 0x21); // Start oscillator (p10)
	i2c_smbus_write_byte(file, 0x81); // Disp on, blink off (p11)
	i2c_smbus_write_byte(file, 0xe7); // Full brightness (page 15)
    write_block(file,screenState);
	return 0;
}
