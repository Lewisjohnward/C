#include <ncurses.h>

WINDOW *createwin(int height, int width, int starty, int startx);

int main (void){
    WINDOW *days, *rows, *cols, *world;
    int ch;

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    printw("Press q to exit");
    refresh();

    int textposx, textposy;
    int startx, starty;
    startx = 10;
    starty = 10;
    days = createwin(3, 15, starty, startx);
    textposx = startx - 5;
    textposy = (starty) + (3 / 2) ;
    mvprintw(textposy , textposx, "Days");
    //ch = getch();
    //mvwprintw(days, 1, 2, "%c", ch);
    //wrefresh(days);

    world = createwin(20, 55, 10, 40);


    getch();
    endwin();
    return 0;

}


WINDOW *createwin(int height, int width, int starty, int startx){
    WINDOW *localwin;
    localwin = newwin(height, width, starty, startx);
    box(localwin, 0, 0);
    wrefresh(localwin);
    return localwin;
}
