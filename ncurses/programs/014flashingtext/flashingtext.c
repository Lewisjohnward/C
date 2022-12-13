#include <ncurses.h>
#include <unistd.h>

int main (void){

    /* start curses */
    initscr();
    /* raw mode */
    cbreak();
    /* turn off echo */
    noecho();
    curs_set(0);


    printw("%d", COLS);
    printw("x");
    printw("%d", LINES);
    attron(A_BLINK);
    mvprintw(25,25, "Blink");
    attroff(A_BLINK);
    attron(A_DIM);
    mvprintw(26,25, "Dim");
    attroff(A_DIM);
    attron(A_CHARTEXT);
    mvprintw(27,25, "Bold");
    attroff(A_CHARTEXT);
    refresh();
    getch();





    /* end curses */
    endwin();
}
