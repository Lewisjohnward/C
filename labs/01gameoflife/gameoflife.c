/*
 *
 * GAME OF LIFE
 *
 * Input file structure
 *
 * Number of grid rows
 * Number of grid cols
 * Number of iterations to simulate
 * Number of coordinate pairs that follow
 * i j
 * i j
 * ..
 *
 * At each descrete time step, every cell in the 2D grid gets a new value 
 * based on the current value of its eight neighbours.
 *
 * A live cell with zero or one live neighbors dies from loneliness
 * A live cell with four or more live neighbors dies due to overpopulation
 * A dead cell with exactly three live neighbors becomes alive
 * All other cells remain in the same state between rounds
 */
#include "gol.h"


int main (int argc, char *argv[]){

    int m = 0;
    char input[50];

    FILE *fp;

    /* check correct amount of args */
    if(argc != 3){
        fprintf(stderr, "Incorrect usage ./gol <inputfile> <mode>\n./gol file1.txt 0\n");
        exit(-1);
    }

    /* copy argv[1] to input */
    strncpy(input, argv[1], 50);

    /* open input file for parsing */
    if((fp = fopen(input, "r")) != 0){
        fprintf(stderr, "Error: fopen\n");
        exit(-1);
    }

    /* convert argv[2] to int */
    m = atoi(argv[2]);

    /* check mode is valid */
    if(m < 0 || m > 1){
        fprintf(stderr, "Error: incorrect mode\n");
        exit(-1);
    }

    /*
     * mode 0 gol with no input
     * mode 1 gol with ascii animations
     */







    rungol();

    return 0;
}


