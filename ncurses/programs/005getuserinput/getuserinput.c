/*
 * Get user input
 *
 * gcc getuserinput.c -lncurses
 */



#include <ncurses.h>
#include <string.h>

int main (void){
    char msg[] = "Enter a string: ";
    char str[80];
    int row, col;

    /* Start ncurses mode */
    initscr();
    /* Get screen dimensions */
    getmaxyx(stdscr, row, col);
    /* Print msg in center of screen */
    mvprintw(row/2, (col-strlen(msg))/2, "%s", msg);

    /* Get user string */
    getstr(str);
    /* Print user string bottom left */
    mvprintw(LINES - 2, 0, "You entered: %s", str);
    /* Wait until user input before ending */
    getch();
    /* End ncurses mode */
    endwin();
    return 0;

}
