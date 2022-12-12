/*
 * Advent of Code 2022 day 9: Rope bridge
 * Part 1
 * time taken: 3.5 hours
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CELLS 1000


typedef struct coords{
    unsigned int x;
    unsigned int y;
}coords;

int main (void){
    /* declare file pointer */
    FILE *fp;

    /* declare CELL columns to hold head and tail*/
    char *lines[CELLS];
    char instruction[100];

    /* initialise head & tail to middle of board */
    coords head;
    coords tail;

    /* visited is an array of coords that tail has visited */
    coords visited[100000];
    int positions = 0;
    head.x = head.y = tail.x = tail.y = 499;

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

        for(int i = 0; i < spaces; i++){
            /* move head first */
            switch(direction){
                case 'L':
                    head.x -= 1;
                    break;
                case 'R':
                    head.x += 1;
                    break;
                case 'U':
                    head.y += 1;
                    break;
                case 'D':
                    head.y -= 1;
                    break;
            }

            /* move tail */
            /* if tail is not adjacent to head */
            if((head.x -1 != tail.x &&
                    head.x != tail.x &&
                    head.x + 1 != tail.x) || (
                    head.y -1 != tail.y &&
                    head.y != tail.y &&
                    head.y + 1 != tail.y)){
                switch(direction){
                    case 'L':
                        tail.x = head.x + 1;
                        tail.y = head.y;
                        break;
                    case 'R':
                        tail.x = head.x - 1;
                        tail.y = head.y;
                        break;
                    case 'U':
                        tail.x = head.x;
                        tail.y = head.y - 1;
                        break;
                    case 'D':
                        tail.x = head.x;
                        tail.y = head.y + 1;
                        break;
                }
            }

            /* update visited array */
            visited[positions].x = tail.x;
            visited[positions++].y = tail.y;
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
