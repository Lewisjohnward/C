#include <ncurses.h>


int main (void){
    initscr();

    printw("Normal");
    attron(A_STANDOUT);
    printw("Standout");
    attroff(A_STANDOUT);
    attron(A_UNDERLINE);
    printw("Underline");
    attroff(A_UNDERLINE);
    refresh();
    getch();

    endwin();

    return 0;

}
