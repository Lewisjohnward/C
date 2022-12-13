/*
 * print string at center of screen & display widith and height of terminal
 * 
 * compile and link gcc printwexamplc.c -lncurses
 */

/* ncurses.h includes stdio.h */  
#include <ncurses.h>			
#include <string.h> 
 
int main()
{
 char mesg[]="Just a string";
 int row,col;				

 initscr();
 /* put size of stdscr in row and col */
 getmaxyx(stdscr,row,col);
 /* print mesg center of stdscr */
 mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
                         
 mvprintw(row-2,0,"This screen has %d rows and %d columns\n",row,col);
 printw("Try resizing your window(if possible) and then run this program again");
 refresh();
 getch();
 endwin();

 return 0;
}
