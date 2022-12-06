#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/*
 * Advent of Code 2022 day 6: Tuning Trouble
 * Part 2
 * time taken: 10 mins
 */

int main (void){
    FILE *fp;
    char *buf;
    struct stat st;
    const char inputstr[] = "input";
    /* Open file */
    if((fp = fopen(inputstr, "r")) == 0){
        puts("Error: fopen");
        exit(-1);
    }
    /* get file size for malloc allocation */
    stat(inputstr, &st);
    
    int size = st.st_size;

    /* malloc memory to hold str */
    buf = malloc(size);

    /* put string in buf */
    fgets(buf, size, fp);

    char seq[14] = {0};

    int i = 0;
    int invalid = 0;
    /* while buf[i + 3] != NULL */
    for(; buf[i + 13]; i++){
        /* assign elements */
        for(int j = 0; j < 14; j++)
            seq[j] = buf[i + j];

        ///* check no repetition */
        for(int j = 0; j < 14; j++)
            for(int k = j; k < 14; k++)
                if(seq[j] == seq[k + 1])
                    invalid = 1;

        /* if not invalid then break */
       if(invalid == 0) break;
        invalid = 0;
    }
    i += 14;

    printf("%d\n", i);
}
