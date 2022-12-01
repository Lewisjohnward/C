#include <stdio.h>
#include <stdlib.h>

#define LEN 10

int sort(const void *a, const void *b){
     int int_a = * ((int*) a );
     int int_b = * ((int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

int main (void){
    /* buf contains each line */
    char buf[LEN];
    /* num contains current line calories */
    unsigned int num = 0;
    /* curr contains current count for given elf */
    unsigned int curr = 0;
    /* max contains array of top 3 calorie count */
    unsigned int max[3] = {0};

    /* open input file with read flag*/
    FILE *fp = fopen("./input", "r");
    /* whilst we are able to read a line */
    while(fgets(buf, LEN, fp) != 0){
        /* convert line char -> int */
        num = atoi(buf);
        /* add to running total */
        curr += num;
        /* if num is 0 its a new elf */
        if(!num){
            /* check to see current is more than max[i]
             * if so save current as max */
            /* reset curr for new elf */
            for(int i = 0; i < 3; i++){
                if(max[i] < curr){
                    max[i] = curr;
                /* sort arr so that lowest always replaced */
                    qsort(max, 3, sizeof(int), sort);
                    break;
                }
            }
            /* set running count to 0 */
            curr = 0;
        }
    }
    /* store sum in num to find total */
    num = 0;
    for(int i = 0; i < 3; i++)
        num += max[i];

    printf("Total top 3: %d\n", num);
    return 0;
}
