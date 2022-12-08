/*
 * Advent of Code 2022 day 8: Treetop Tree House
 * Part 1
 * time taken: WIP
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROWS 99 

int main (void){
    FILE *fp;
    char *treerow[ROWS];


    /* open input file */
    if((fp = fopen("input", "r")) == 0){
        puts("Error: fopen");
    }

    /* allocate treerow */
    for(int i = 0; i < ROWS; i++){
        treerow[i] = malloc(sizeof(char) * (ROWS + 2));
    }

    /* put each line into treerows 
     * remove newline */
    for(int i = 0; i < ROWS; i++){
        char *ptr = treerow[i];
        fgets(ptr, (ROWS + 2), fp);
        ptr[strcspn(ptr, "\n")] = 0;
    }

    int visible = 0;
    /* Is the tree visible from outside grid from any direction ? */
    for(int i = 0; i <= ROWS; i ++){
        /* for each row print all trees */
        char *ptr = treerow[i];

        /* this loop iterates over each tree on a row */
        for(int j = 0; j < ROWS; j++){
            /* top edge / bottom edge */
            if(i == 0 || i == 98){
                visible++;
                continue;
            }
            /* side edge trees are visible */
            if(j == 0 || j == 98){
                visible++;
                continue;
            }

            /* each tree only has to be visible from one side to be counted */
            /* look from top */
            for(int k = 0; k < i; k++){
                char *ptr1 = treerow[k];
                if(ptr1[j] < ptr[j])
            }





        }
    }
    printf("%d\n", visible);


    return 0;
}
