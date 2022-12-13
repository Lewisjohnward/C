/*
 * HELLO WORLD using ncurses
 *
 * compile and link gcc helloworld.c -lncurses
 */

#include <ncurses.h>

int main (void){
    /* Start curses mode */
    initscr();
    /* Print hello world */
    printw("Hello World !!!!");
    /* Print it on to the real screen */
    refresh();
    /* Wait for user input */
    getch();
    /* End curses mode */
    endwin();

    return 0;
}
