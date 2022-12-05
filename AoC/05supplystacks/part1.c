#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Advent of Code 2022 day 5: Supply Stacks
 * Part 1
 * time taken: 1 hour
 */

int main (void){
    FILE *fp;

    /* buf will hold a line */
    char buf[50];
    /* declare ints used to data manipulation */
    int quantity, source, destination;
    char delim[] = "\n";

    /* set up an array of pointers for later iteration */
    char *ptr[10];

    /* initialise columns give them len 50 to allow additions*/
    char arr1[50] = "TDWZVP";
    char arr2[50] = "LSWVFJD";
    char arr3[50] = "ZMLSVTBH";
    char arr4[50] = "RSJ";
    char arr5[50] = "CZBGFMLW";
    char arr6[50] = "QWVHZRGB";
    char arr7[50] = "VJPCBDN";
    char arr8[50] = "PTBQ";
    char arr9[50] = "HGZRC";

    /* asign array of pointers to correct arr */
    ptr[1] = arr1;
    ptr[2] = arr2;
    ptr[3] = arr3;
    ptr[4] = arr4;
    ptr[5] = arr5;
    ptr[6] = arr6;
    ptr[7] = arr7;
    ptr[8] = arr8;
    ptr[9] = arr9;

    /* open file and asign to fp */
    if((fp = fopen("input", "r")) == NULL){
        puts("Error: fopen");
        exit(-1);
    }

    /* while there is a line to read, read it into buf */
    while(fgets(buf, 50, fp)){
        /* remove newline */
        buf[strlen(buf) - 1] = '\0';
        /* get needed values from line */
        sscanf(buf, "move %d from %d to %d", &quantity, &source, &destination);

        /* do quantitiy times */
        for(int i = 0; i < quantity; i++){
            /* move up destination NULL char by one postion */
            *(ptr[destination] + strlen(ptr[destination]) + 1) = '\0'; 
            /* put top of source in destination underneath new null*/
            *(ptr[destination] + strlen(ptr[destination])) =  *(ptr[source] + strlen(ptr[source]) - 1); 
            /* replace moved char with null character / decrement source */
            *(ptr[source] + strlen(ptr[source]) - 1) = '\0';
        }
    }

    /* print array horizontally */
    for(int i = 1; i < 10; i++){
        puts(ptr[i]);
    }

    return 0;
}
