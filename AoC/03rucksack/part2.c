#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * time taken = 30 mins
 *
 */

int main (void){
    FILE *fp;
    char buf0[100];
    char buf1[100];
    char buf2[100];
    char delim[] = "\n";
    //char *ptr;
    int score = 0;

    char *bptr[3];
    bptr[0] = buf0;
    bptr[1] = buf1;
    bptr[2] = buf2;

    char buf[50];
    memset(buf, 0, 50);
    char *ptr;
    ptr = buf;


    /* open file to read */
    if((fp = fopen("input", "r")) == 0){
        puts("Fopen");
        exit(-1);
    }

    /* infinite loop */
    while(1){
        /* get 3 lines */
        for(int i = 0; i < 3; i++){
            if(fgets(bptr[i], 100, fp) == 0)
                /* when fp gets to end of file jump to exit */
                goto exit;
            /* remove newline */
            bptr[i] = strtok(bptr[i], delim);
        }

        /* find common objects between line 1 & line 2 and store in buf*/
        for(int i = 0; buf0[i]; i++)
            for(int j = 0; buf1[j]; j++)
                if(buf0[i] == buf1[j]){
                    *ptr++ = buf0[i];
                    *ptr = '\0';
                }

        /* clear char array to store common items */
        memset(buf0, 0, 100);
        ptr = buf0;

        /* find common objects remaining in line 3 */
        for(int i = 0; buf[i]; i++)
            for(int j = 0; buf2[j]; j++)
                if(buf[i] == buf2[j]){
                    *ptr++ = buf2[j];
                    *ptr = '\0';
                }

        /* calculate score */
        if(buf0[0] < 91)
            score += buf0[0] - 38;
        else
            score += buf0[0] - 96;

        /* reset pointers & items buffers */
        ptr = buf;
        memset(buf, 0, 50);
        for(int i = 0; i < 3; i++)
            memset(bptr[i], 0, 100);
    }

exit:
    printf("Score: %d\n", score);
    return 0;
}
