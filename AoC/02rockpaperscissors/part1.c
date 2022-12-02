#include <stdio.h>
#include <stdlib.h>

/*
 * time taken = 35 mins
 */

int main (void){
    FILE *fp;
    char buf[5];
    int score = 0;


    /* open file */
    if((fp = fopen("input", "r")) == NULL){
        puts("Error: fopen");
        exit(-1);
    }

    /* Read file 1 line at a time storing into buf[5]
     * after each read calculate score
     */
    while(fgets(buf, 5, fp) != 0){
        printf("buf: %s", buf);
        if(buf[0] == 'A' && buf[2] == 'Y')
            score += 6;
        else if(buf[0] == 'B' && buf[2] == 'Z')
            score += 6;
        else if(buf[0] == 'C' && buf[2] == 'X')
            score += 6;
        /* 23 is the numerical difference in ASCII from A - X */
        else if (buf[0] == (buf[2] - 23))
            score += 3;
        else
            score += 0;

        switch(buf[2]){
            case 'X':
                score += 1;
                break;
            case 'Y':
                score += 2;
                break;
            case 'Z':
                score += 3;
                break;
        }
    printf("Score: %d\n", score);
    }
    return 0;
}
