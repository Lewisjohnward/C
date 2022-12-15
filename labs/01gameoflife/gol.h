#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#ifndef GOL_H
#define GOL_H

/* contains initial live cell */
typedef struct init{
    int x;
    int y;
}init;

/* contains each change to world after each iteration */
typedef struct mods{
    int x;
    int y;
    int life;
} mods;

/* contains mods & count for updating after iteration */
typedef struct modifications {
    int count;
    mods mods[1000];
} modifications;

/* the grid */
typedef struct world {
    unsigned int rows;
    unsigned int cols;
    int **grid;
}world;


void rungol(void);
void printworld(world *world);
void printlivecells(int livecells);
void printmodifications(modifications *modifications);
void findlivecell(world *world, modifications *modifications, int *livecells);
int iscelllonely(world *world, int x, int y);
int iscellloverpopulated(world *world, int x, int y);
void finddeadcell(world *world, modifications *modifications);
int hasliveneighbours(world *world, int x, int y);
void addmodification(modifications *modifications, int life, int x, int y);
void updateworld(world *world, modifications *modifications);

#endif
