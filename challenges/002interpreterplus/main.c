/*
 * Codewars: Assembler interpreter (part 2)
 * https://www.codewars.com/kata/58e61f3d8ff24f774400002c
 *
 * time taken: 6h:20min ( so far)
 *
 */

/*
 * WORK IN PROGRESS: WILL NOT WORK
 */

#include "parser.h"
#include "interpreter.h"
#include "exampleprogs.h"

#include <string.h>
#include <stdlib.h>

#define MAXBUF 1024
#define MAXLINE 200
#define MAXREG 26

void printregisters(char *registers, int zf, int gf, int count){
    printf("count: %d\n", count);
    printf("gf: %d zf: %d\n", gf, zf);
    /* prints out registers & their values */
    for(int j = 0; j < 26; j++)
        printf("%c ", 97 + j);
    puts("");
    for(int j = 0; j < 26; j++)
        printf("%d ", registers[j]);
    puts("\n");
}

void executeinstructions(char *line[], int ins){
    /* array of registers to hold register values */
    char registers[26] = { 0 };
    /* zero flag */
    int zf = 0;
    /* greater than flag */
    int gf = 0;

    /* counts instruction number - for debuging */
    int count = 0;
    /* current instruction */
    int instructionpointer = 0;
    /* msgbuffer contains print statements */
    char msgbuffer[100] = { 0 };
    /* while instruction is not "end" execute */
    while(strcmp(line[instructionpointer], "end")){
        /* print line for debugging */
        printf("%d:%s\n", instructionpointer, line[instructionpointer]);

        /* for debugging */
        if(count == 70) break;

        /* interpret instruction and update registers */
        interpretinstruction(&instructionpointer, line[instructionpointer], registers, &gf, &zf, msgbuffer);

        /* conditional statement that
         * register[**(ins+1)] is the value in dest
         * register[**(ins+2)] is the value in source
         *
         * The Codewars challenge indexes the array using
         * a-z but this implementation transforms a->0 
         * z-> 26 hence the -97
         */

        /* print registers */
        printregisters(registers, zf, gf, count);

        count++;
        instructionpointer++;
    }
    //puts("end");
    printregisters(registers, zf, gf, count);
    printf("%s\n", msgbuffer);
}

int main (void){
    char *line[100];
    char buf[20];
    int ins = 0;

    /* allocate space for instructions arr */
    for(int i = 0; i < 100; i++) 
        line[i] = malloc(1000 * sizeof(char));

    /* parse string program and place instructions in line[] */
    parseinstructions(myprog2, line, &ins);

    for(int j = 0; j < ins; j++)
    {
        printf("%02d: ", j);
        puts(line[j]);
    }

    /* execute instructions a line at a time */
    //executeinstructions(line, ins);


}
