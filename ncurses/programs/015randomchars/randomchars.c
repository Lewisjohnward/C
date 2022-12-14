#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/*
 * Places random chars onto screen at random positions
 * gcc randomchars.c -lncurses
 *
 * rand() % (max + 1 - min ) + min;
 */

int main (void){
    char alphabet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    size_t len = strlen(alphabet);
    int randint, randx, randy;

    /* seed rand */
    srand(time(NULL));

    /* start ncurses */
    initscr();
    /* raw mode */
    cbreak();
    /* turn off cursor */
    curs_set(0);

    for(int i = 0; i < 100000; i++){
        /* generate random number between 0 and length of alphabet */
        randint = rand() % ((len - 1) + 1);
        /* generate random x coord between 0 and COLS*/
        randx = rand() % ((COLS - 1) + 1);
        /* generate random y coord between 0 and LINES*/
        randy = rand() % ((LINES - 1) + 1);
        /* move cursor to new position */
        move(randy, randx);
        /* print char */
        printw("%c", alphabet[randint]);
        /* refresh display */
        refresh();
        /* sleep 1000 microseconds */
        usleep(1000);
    }

    /* program will wait here for user input before exiting */
    getch();

    /* end ncurses */
    endwin();
    return 0;




}
