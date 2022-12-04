#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * In how many pairs overlap at all
 *
 * time taken: 1hr;
 */

int main (void){
    FILE *fp;
    char elfpair[100];
    char *elfptr1[2];
    char *elfptr2[2];

    if((fp = fopen("input", "r")) == 0){
        puts("Error: fopen");
        exit(-1);
    }

    int count = 0;

    /* read line into buf*/
    while(fgets(elfpair, 100, fp) != 0){
        printf("%s", elfpair);
            /* split the pairs up based on the comma */
            elfptr1[0] = strtok(elfpair, ",");
            elfptr2[0] = strtok(NULL, "\n");

            /* spit up ints in the first elf */
            elfptr1[0] = strtok(elfptr1[0], "-");
            elfptr1[1] = strtok(NULL, "");

            /* split the ints in the second elf */
            elfptr2[0] = strtok(elfptr2[0], "-");
            elfptr2[1] = strtok(NULL, "-");

            /* compare the pair of elves to see if there is any overlap*/
            if(atoi(elfptr1[0]) >= atoi(elfptr2[0]) && atoi(elfptr1[0]) <= atoi(elfptr2[1]) ||
                    atoi(elfptr1[1]) >= atoi(elfptr2[0]) && atoi(elfptr1[1]) <= atoi(elfptr2[1]))
                count++;
            else if(atoi(elfptr2[0]) >= atoi(elfptr1[0]) && atoi(elfptr2[0]) <= atoi(elfptr1[1]) ||
                    atoi(elfptr2[1]) >= atoi(elfptr1[0]) && atoi(elfptr2[1]) <= atoi(elfptr1[1]))
                    count++;

    }
        
        printf("Count: %d\n", count);


    return 0;

}
