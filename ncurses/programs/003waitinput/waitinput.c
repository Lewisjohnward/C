/*
 * Waiting for input NCURSES example
 * every keyboard press prints a letter from the alphabet
 *
 * compile and link gcc waitinput.c -lncurses
 */

#include <ncurses.h>
#include <string.h>

int main(){	
    char *arr = "abcdefghijklmnopqrstuvwxyz";
    size_t len = strlen(arr);
    int i = 0;
    int ch;
    /* Start curses mode 		*/
	initscr();			
    /* Line buffering disabled  */
	raw();				
    /* We get F1, F2 etc..      */
	keypad(stdscr, TRUE);		
    /* Don't echo() while we do getch */
	noecho();			

    /* move cursor to given point */
    move(25, 50);
    while(i != len){
        ch = getch();
        if(ch == 'q') break;
		attron(A_BOLD);
        printw("%c", arr[i]);
		attroff(A_BOLD);
        refresh();			/* Print it on to the real screen */
        i++;
    }

	endwin();			/* End curses mode		  */

	return 0;
}
