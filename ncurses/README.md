# Ncurses

Escape character 0x1B

NCURSES not only creates a wrapper over terminal capabilities, but also gives a robust framework to creat nice looking UIs in text mode. It provides functions to create windows etc. Its sister libraries panel, menu and form provide an extension to the basic curses library.


initscr() - To do any screen manipulation this has to be called first. initialises the terminal in curses mode. In some implementations, it clears the screen and presents a blank screen.h.
raw() - disable line buffering. Characters are passed directly to the terminal without generating a signal.
cbreak() - disable line buffering. Characters are passed directly to terminal.
echo()
noecho()
keypad()
halfdelay()

COLS contains # of columns
LINES contains # of lines

move(y, x) - Move cursor to (x, y)
mvprintw(y, x, string) - Move to (y, x) then print string.
wprintw(window, "string") - Print on window window at present cursor position in the window.
mvwprintw(win, y, x, string) - Move to y, x relative to window coords & print.
wrefresh(win)

addch()
printw()
addstr()

box(local_win, 0, 0)
wborder(local_win, '-', '-', '-','-','-','-','-','-');
curs_set(0: invis, 1: normal, 2: v vis)

attron()
attroff()

move(row, col)
addch(ch)

mvaddch(row, col, ch)

newwin( height, width, starty, startx) - Creates a new window. returns a pointer to structure WINDOW
box(window, 0, 0);
wrefresh(window);



printw() - Analogous to to printf except is prints the data on a window called stdscr at current y x coords.
refresh() - Dump contents on screen.
endwin() - Frees the memory taken by ncurses sub-system & its data structures and puts the terminal in normal mode.
