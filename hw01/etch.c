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

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define MAX_BUF 64

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void set_gpio(void);
void enable_outputs(void);


int main(int argc, char *argv[]){
    WINDOW *my_win;
    initscr();
    int y=0;
    int  x=0;
    int height, width,input_method,down_val,up_val,right_val,left_val;
    chtype str = 'X';  
    int maxx=0, maxy=0;

    printf ("Enter the desired window width please: \n");
    scanf ("%d", &width);
    printf ("Now enter the desired window height: \n");
    scanf ("%d", &height);
    noecho();
my_win = create_newwin(height, width, 0, 0);
    getmaxyx(my_win,maxx,maxy);
    

        while(1)
        {
            int c = getch();
            switch (c)
            {
                case 'w':
                if(y>0)
                {
                    y--;
                    mvaddch(y, x, str);
                }
                    break;
                case 's':
                if(y<maxy)
                {
                    y++;
                    mvaddch(y, x, str);
                }
                    break;
                case 'a':
                if(x>0)
                {
                    x--;
                    mvaddch(y, x, str);
                }
                    break;
                case 'd':
                if(x<maxx)
                {
                    x++;
                    mvaddch(y, x, str);
                }
                    break;
                case 'x':
                    destroy_win(my_win);
                    endwin();
                    return 0;
                default:
                    refresh();
                    break;
            }   
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
