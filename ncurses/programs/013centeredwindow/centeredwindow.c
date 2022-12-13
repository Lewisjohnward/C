#include <ncurses.h>

typedef struct _win_border_struct {
    chtype ls, rs, ts, bs,
           tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_struct {
    int startx, starty;
    int height, width;
    WIN_BORDER border;
}WIN;


void init_win_params(WIN *p_win);
void print_win_params(WIN *p_win);
void create_box(WIN *p_win, bool flag);

int main (void){
    WIN win;
    int ch;
    /* Start ncurses */
    initscr();
    /* Start color functionalitiy */
    //start_color();
    /* Disable line buffering receive all keypresses*/
    cbreak();
    /* Don't echo input */
    noecho();

    /* Allows keypad chars */
    keypad(stdscr, TRUE);

    /* Turn off the cursor */
    curs_set(0);

    /* Init window params */
    init_win_params(&win);
    print_win_params(&win);
    /* Print message to window */
    printw("Press q to exit");
    /* Refresh to display message */
    refresh();
	create_box(&win, TRUE);

	while((ch = getch()) != KEY_F(1))
	{	switch(ch)
		{	case KEY_LEFT:
				create_box(&win, FALSE);
				--win.startx;
				create_box(&win, TRUE);
				break;
			case KEY_RIGHT:
				create_box(&win, FALSE);
				++win.startx;
				create_box(&win, TRUE);
				break;
			case KEY_UP:
				create_box(&win, FALSE);
				--win.starty;
				create_box(&win, TRUE);
				break;
			case KEY_DOWN:
				create_box(&win, FALSE);
				++win.starty;
				create_box(&win, TRUE);
				break;	
		}
        if(ch == 'q') break;
	}


    /* End curses mode */
    endwin();

    return 0;
}

void init_win_params(WIN *p_win)
{
    p_win->height = 30;
    p_win->width = 70;
    p_win->starty = (LINES - p_win->height)/2;  
    p_win->startx = (COLS - p_win->width)/2;

    p_win->border.ls = '|';
    p_win->border.rs = '|';
    p_win->border.ts = '-';
    p_win->border.bs = '-';
    p_win->border.tl = '+';
    p_win->border.tr = '+';
    p_win->border.bl = '+';
    p_win->border.br = '+';

}

void print_win_params(WIN *p_win)
{
#ifdef _DEBUG
	mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty, 
				p_win->width, p_win->height);
	refresh();
#endif
}
void create_box(WIN *p_win, bool flag)
{	int i, j;
	int x, y, w, h;

	x = p_win->startx;
	y = p_win->starty;
	w = p_win->width;
	h = p_win->height;

	if(flag == TRUE)
	{	mvaddch(y, x, p_win->border.tl);
		mvaddch(y, x + w, p_win->border.tr);
		mvaddch(y + h, x, p_win->border.bl);
		mvaddch(y + h, x + w, p_win->border.br);
		mvhline(y, x + 1, p_win->border.ts, w - 1);
		mvhline(y + h, x + 1, p_win->border.bs, w - 1);
		mvvline(y + 1, x, p_win->border.ls, h - 1);
		mvvline(y + 1, x + w, p_win->border.rs, h - 1);

	}
	else
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
				
	refresh();

}

