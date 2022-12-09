/*
 * Advent of Code 2022 day 9: Rope bridge
 * Part 1
 * time taken: WIP
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

    /* H can cover T */
    /* COUNT ALL POSITIONS TAIL VISITED AT LEAST ONCE */
    /* Tail is always adjacent to head */

    int count = 0;
    char direction;
    int spaces = 0;
    int prevvert = 0;
    int prevhoriz = 0;
    char prevdir;
    /* read line of instruction */
    while(fgets(instruction, 100, fp)){
        /* remove newline */
        instruction[strcspn(instruction, "\n")] = 0;
        /* parse instruction */
        direction = instruction[0];
        strtok(instruction, " ");
        spaces = atoi(strtok(NULL, ""));

        //puts(instruction);
        printf("%c %d\n", instruction[0], spaces);

        for(int i = 0; i < spaces; i++){
            /* move head first */
            switch(direction){
                case 'L':
                    head.x -= 1;
                    /* if tail not adjacent move tail */
                    if(prevvert == 0 && prevdir != 'R'){
                        if(head.x + 1 != tail.x){
                            tail.x -= 1;
                        }
                    }else if (prevvert == 2){
                        tail.x = head.x + 1;
                        tail.y = head.y;
                        prevvert = 0;
                    }
                    if(prevvert != 0){
                        prevvert++;
                    }
                    prevdir = 'L';

                    prevhoriz = 1;
                    break;

                case 'D':
                    head.y -= 1;
                    if(prevhoriz == 0 && prevdir != 'U'){
                        if(head.y + 1 != tail.y){
                            tail.y -= 1;
                        }
                    }else if (prevhoriz == 2){
                        tail.y = head.y + 1;
                        tail.x = head.x;
                        prevhoriz = 0;
                    }
                    if(prevhoriz != 0){
                        prevhoriz++;
                    }
                    prevvert = 1;
                    prevdir = 'D';
                    break;

                case 'R':
                    head.x += 1;
                    if(prevvert == 0 && prevdir != 'L'){
                        if(head.x - 1 != tail.x){
                            tail.x += 1;
                        }
                    }else if (prevvert == 2){
                        tail.x = head.x - 1;
                        tail.y = head.y;
                        prevvert = 0;
                    }
                    if(prevvert != 0){
                        prevvert++;
                    }

                    prevhoriz = 1;
                    prevdir = 'R';
                    break;

                case 'U':
                    head.y += 1;
                    if(prevhoriz == 0 && prevdir != 'D'){
                        if(head.y - 1 != tail.y){
                            tail.y += 1;
                        }
                    }else if (prevhoriz == 2){
                        tail.y = head.y - 1;
                        tail.x = head.x;
                        prevhoriz = 0;
                    }
                    if(prevhoriz != 0){
                        prevhoriz++;
                    }
                    prevvert = 1;
                    prevdir = 'U';
                    break;
            }

            visited[positions].x = tail.x;
            visited[positions++].y = tail.y;
        }
        //count++;
        //if(count == 10) break;
    }
    puts("Finishing position");
    printf("head: %d %d\n", head.x, head.y);
    printf("tail: %d %d\n", tail.x, tail.y);

    puts("Positions visited");
    for(int i = 0; i < positions; i++){
        printf("%i %d %d\n", i, visited[i].x, visited[i].y);
    }

    int unique = 0;

    for(int i = 0; i < positions; i++){
        for(int j = i + 1; j < positions; j++){
            if(visited[i].x == visited[j].x && visited[i].y == visited[j].y)
            {
                visited[j].x = 0;
                visited[j].y = 0;
            }
        }
    }

    for(int i = 0; i < positions; i++){
        if(visited[i].x != 0)
            unique++;
    }
    printf("unique: %d\n", unique);

    /* free memory previously allocated */
    for(int i = 0; i < CELLS; i++){
        free(lines[i]);
    }

    return 0;
}
