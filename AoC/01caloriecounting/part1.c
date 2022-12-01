#include <stdio.h>
#include <stdlib.h>

#define LEN 10

int main (void){
    /* buf contains each line */
    char buf[LEN];
    /* num contains current line calories */
    int num = 0;
    /* curr contains current count for given elf */
    int curr = 0;
    /* max contains highest calorie count */
    int max = 0;

    /* open input file */
    FILE *fp = fopen("./input", "r");
    /* whilst we are able to read a line */
    while(fgets(buf, LEN, fp) != 0){
        /* convert line char -> int */
        num = atoi(buf);
        /* add to running total */
        curr += num;

        /* if num is 0 its a new elf */
        if(!num){
            /* check to see current is more than max
             * if so save current as max */
            max = curr > max ? curr : max;
            /* reset curr for new elf */
            curr = 0;
        }
    }
    printf("Max :%d\n", max);
    return 0;
}
