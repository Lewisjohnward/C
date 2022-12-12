/*
 * Advent of Code 2022 day 9: Rope bridge
 * Part 2
 * time taken: WIP
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CELLS 1000
#define NUMKNOTS 10


typedef struct coords{
    unsigned int x;
    unsigned int y;
    char dir;
}coords;

int main (void){
    /* declare file pointer */
    FILE *fp;

    /* declare CELL columns to hold head and tail*/
    char *lines[CELLS];
    char instruction[100];

    /* initialise head & tail to middle of board */
    coords knot[NUMKNOTS];

    /* visited is an array of coords that tail has visited */
    coords visited[100000];
    int positions = 0;
    for(int i = 0; i < NUMKNOTS; i++){
        knot[i].x = 499;
        knot[i].y = 499;
    }

    /* declare CELL rows */
    for(int i = 0; i < CELLS; i++){
        lines[i] = malloc(sizeof(char) * CELLS);
    }

    /* open file */
    if((fp = fopen("input", "r")) == 0){
        puts("Error: fopen");
        exit(-1);
    }

    /* direction holds char direction i.e. 'L' */
    char direction;
    /* spaces holds number of times to move direction */
    int spaces = 0;
    /* read line of instruction */
    while(fgets(instruction, 100, fp)){
        /* remove newline */
        instruction[strcspn(instruction, "\n")] = 0;
        /* parse instruction */
        direction = instruction[0];
        strtok(instruction, " ");
        spaces = atoi(strtok(NULL, ""));

        /* record direction of knot[0] */
        knot[0].dir = direction;
        for(int i = 0; i < spaces; i++){
            /* move knot[0] first */
            switch(direction){
                case 'L':
                    knot[0].x -= 1;
                    break;
                case 'R':
                    knot[0].x += 1;
                    break;
                case 'U':
                    knot[0].y += 1;
                    break;
                case 'D':
                    knot[0].y -= 1;
                    break;
            }

            for(int i = 1; i < NUMKNOTS; i++){
                /* move each knot along the array */
                /* if tail is not adjacent to head */
                if((knot[i - 1].x -1 != knot[i].x &&
                            knot[i - 1].x != knot[i].x &&
                            knot[i - 1].x + 1 != knot[i].x) || (
                                knot[i - 1].y -1 != knot[i].y &&
                                knot[i - 1].y != knot[i].y &&
                                knot[i - 1].y + 1 != knot[i].y)){
                    switch(knot[i - 1].dir){
                        case 'L':
                            knot[i].x = knot[i - 1].x + 1;
                            knot[i].y = knot[i - 1].y;
                            break;
                        case 'R':
                            knot[i].x = knot[i - 1].x - 1;
                            knot[i].y = knot[i - 1].y;
                            break;
                        case 'U':
                            knot[i].x = knot[i - 1].x;
                            knot[i].y = knot[i - 1].y - 1;
                            break;
                        case 'D':
                            knot[i].x = knot[i - 1].x;
                            knot[i].y = knot[i - 1].y + 1;
                            break;
                    }
                }
            }

            /* update visited array */
            visited[positions].x = knot[9].x;
            visited[positions++].y = knot[9].y;
        }
    }

    /* initialise unique count */
    int unique = 0;

    /* find unique positions - set duplicate positions to zero */
    for(int i = 0; i < positions; i++)
        for(int j = i + 1; j < positions; j++)
            if(visited[i].x == visited[j].x && visited[i].y == visited[j].y)
            { visited[j].x = 0; visited[j].y = 0; }

    /* count the non zero coords */
    for(int i = 0; i < positions; i++)
        if(visited[i].x != 0) unique++;

    /* print unique positions */
    printf("Unique: %d\n", unique);

    /* free memory previously allocated */
    for(int i = 0; i < CELLS; i++){
        free(lines[i]);
    }

    return 0;
}
