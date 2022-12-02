#include <stdio.h>
#include <stdlib.h>

/*
 * time taken = 20 mins
 */

int main (void){
    FILE *fp;
    char buf[5];
    char myfist;
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
        /* 23 is the numerical difference in ASCII from A - X */
        if(buf[2] == 'Y'){
            score += 3;
            myfist = buf[0] + 23;
        }
        else if(buf[2] == 'Z'){
            score += 6;
            if(buf[0] == 'A')
                myfist = 'Y';
            else if(buf[0] == 'B')
                myfist = 'Z';
            else
                myfist = 'X';
        }
        else{
            score += 0;
            if(buf[0] == 'A')
                myfist = 'Z';
            else if(buf[0] == 'B')
                myfist = 'X';
            else
                myfist = 'Y';

        }

        switch(myfist){
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
