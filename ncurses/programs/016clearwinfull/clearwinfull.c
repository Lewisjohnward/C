/*
 * NCURSES - creates a centered window that gets cleared when full
 */

#include <ncurses.h>
#include <unistd.h>

WINDOW *create_win(int height, int width, int starty, int startx);

int main (void){
    /* create WINDOW pointer */
    WINDOW *win;

    /* ch container */
    int ch;

    /* for window dimensions */
    int height, width, starty, startx;

    /* contains cursor coords */
    int x, y;

    /* init ncurses */
    initscr();

    /* enable raw mode */
    cbreak();

    /* disable cursor */
    curs_set(0);

    /* disable echo */
    noecho();

    /* calculate window positioning */
    height = 10;
    width = 50;
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2;

    /* print exit string dim */
    attron(A_DIM);
    printw("press q to quit");
    attroff(A_DIM);

    /* refresh screen */
    refresh();

    /* create window */
    win = create_win(height, width, starty, startx);

    /* move cursor to starting position */
    wmove(win, 1, 1);
    while((ch = getch()) != 'q'){
        if(x == 49) wmove(win, y + 1, 1);
        if(y == 1 && x == 49) {
            /* delete win */
            delwin(win);
            /* create new win */
            win = create_win(height, width, starty, startx);
            /* move cursor to 1, 1 */
            wmove(win, 1, 1);
        }
        /* print char */
        wprintw(win, "%c", ch);
        /* get x y coords to ensure inside window */
        getyx(win, y, x);
        /* refresh window to see updates */
        wrefresh(win);
    }
    /* end ncurses */
    endwin();
}

WINDOW *create_win(int height, int width, int starty, int startx){
    /* window pointer */
    WINDOW *local_win;

    /* create new window */
    local_win = newwin(height, width, starty, startx);

    /* create border */
    box(local_win, 0, 0);

    /* draw to screen */
    wrefresh(local_win);
    
    /* return pointer */
    return local_win;
}
