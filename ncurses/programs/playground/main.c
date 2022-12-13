#include <ncurses.h>


WINDOW *create_newwin(int height, int width, int starty, int startx);

int main (void){
    WINDOW *my_win;
    int startx, starty, width, height;
    int ch;
    int x, y;

    height = 3;
    width = 10;

    initscr();
    cbreak();
    noecho();
	keypad(stdscr, TRUE);		/* I need that nifty F1 	*/

    /* calculate coords for center placement */
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2;
    refresh();
    printw("starty: %d, startx: %d", starty, startx);

    /* create window */
    my_win = create_newwin(height, width, starty, startx);

    while((ch = getch()) != 'q'){
        mvwprintw(my_win, 3, 1, "a");
        refresh();
    }

    //printw("%d", LINES);
    //move(0, 5);
    //printw("%d", COLS);
    //move(2, 4);
    //printw("Press any key to exit");
    //mvprintw(10, 10, "hello from mvprintw");
    //refresh();
    //getch();
    //clear();
    getch();
    endwin();
    return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}
