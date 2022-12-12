/*
 * Number of grid rows
 * Number of grid cols
 * Number of iterations to simulate
 * Number of coordinate pairs that follow
 * i j
 * i j
 * ..
 *
 *
 * It can be assumed that the grid will have at least four rows and four columns
 */

/*
 * At each descrete time step, every cell in the 2D grid gets a new value 
 * based on the current value of its eight neighbours.
 *
 * A live cell with zero or one live neighbors dies from loneliness
 * A live cell with four or more live neighbors dies due to overpopulation
 * A dead cell with exactly three live neighbors becomes alive
 * All other cells remain in the same state between rounds
 */

/*
 * timeval{
 *  time_t tv_sec;
 *  susecondts_t tv_usec;
 * }
 */

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>


/* contains initial live cell */
typedef struct init{
    int x;
    int y;
}init;


typedef struct mods{
    int x;
    int y;
    int life;
} mods;

typedef struct modifications {
    int count;
    mods mods[100];
} modifications;

void printmodifications(modifications *modifications);
void removelonelycells(int **world, int rows, modifications *modifications);

int main (int argc, char *argv[]){
    //void srand(SEED);
    //int rand();
    unsigned int rows, cols;
    /* if there are 2 command line args then atoi argv[2] otherwise use 30 */
    rows = cols = argc == 2 ? atoi(argv[1]) : 30;
    unsigned int iterations = 1;
    init init;
    init.x = init.y = 3;
    struct timeval start_time, end_time;


    modifications modifications;
    modifications.count = 0;
    /* declare a pointer to an array of int pointers */
    int **world;
    /* container for world when calculating updates */
    int **tmpworld;
    /* allocate memory for X rows */
    world = malloc(sizeof(int *) * rows);
    tmpworld = malloc(sizeof(int *) * rows);
    /* allocate memory for X cols */
    for(int i = 0; i < rows; i++){
        world[i] = malloc(sizeof(int) * cols);
        tmpworld[i] = malloc(sizeof(int) * cols);
    }
    /* init world */
    world[init.x][init.y] = 1;
    world[init.x-3][init.y] = 1;
    world[init.x - 1][init.y - 1] = 1;
    world[init.x + 1][init.y + 1] = 1;
    world[init.x + 2][init.y + 1] = 1;
    world[init.x + 2][init.y] = 1;

    for(int i = 0; i < iterations; i++){
        removelonelycells(world, rows, &modifications);
        /* for each live cell are there 0 or 1 neighbours ?*/
        printmodifications(&modifications);
    }






    /* print world */
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++)
            printf("%c ", world[i][j] ? '@' : '.');
        puts("");
    }



    /* populate struct timeval struct start_time with time since epoch */
    gettimeofday(&start_time, NULL);













    /* populate struct timeval struct end_time with time since epoch */
    gettimeofday(&end_time, NULL);

    /* calculate difference in time */
    printf("Time taken: %ld\n", end_time.tv_usec - start_time.tv_usec);
    return 0;
}

int iscelllonely(int **world, int rows, int x, int y){
    /* keep count of number of neighbours */
    int neighbours = 0;
    /* loop over section of world to find neighbours */
    for(int i = -1; i < 2; i++)
        for(int j = -1; j < 2; j++){
            /* when x = 0 & j = 0 we're looking at already known cell so skip */
            if(i == 0 && j == 0) continue;
            /* wraps around world */
            int xt, yt;
            xt = x + i < 0 ? rows + i : x + i;
            yt = y + j < 0 ? rows + j : y + j;
            /* if life is present inc neighbours */
            if(world[xt][yt])
                neighbours++;
            /* if neighbours greater than 1 cell is not lonely */
            if(neighbours > 1)
                return 0;
        }
    /* if we reach here cell is lonely */
    return 1;
}


void removelonelycells(int **world, int rows, modifications *modifications){
    /* grid is a square */
    int cols = rows;
    /* iterate over world to find live cells */
    for(int j = 0; j < cols; j++)
        for(int k = 0; k < rows; k++){
            if(world[j][k] == 1){
                /* are there 0 or 1 neighbours ? */
                if (iscelllonely(world, rows, j, k)){
                    printf("is lonely: %d %d\n", j, k);
                    modifications->mods[modifications->count].x = k;
                    modifications->mods[modifications->count].y = j;
                    modifications->mods[modifications->count].life = 0;
                    modifications->count++;
                }
            }
        }
}


void printmodifications(modifications *modifications){
    for(int i = 0; i < modifications->count; i++){
        printf("x: %d y: %d life: %d\n", modifications->mods[i].x, modifications->mods[i].y, modifications->mods[i].life);
    }
}
