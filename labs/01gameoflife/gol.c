#include "gol.h"


void rungol(void){
    //void srand(SEED);
    //int rand();

    unsigned int rows, cols;
    world world;
    /* if there are 2 command line args then atoi argv[2] otherwise use 30 */
    world.rows = world.cols = 30;
    //world.rows = world.cols = argc == 2 ? atoi(argv[1]) : 30;

    int livecells = 0;

    unsigned int iterations = 10000;
    init init;
    init.x = init.y = 3;
    struct timeval start_time, end_time;

    /* init modifications */
    modifications modifications;
    modifications.count = 0;
    /* allocate memory for X rows */
    world.grid = malloc(sizeof(int *) * world.rows);
    /* allocate memory for X cols */
    for(int i = 0; i < world.rows; i++){
        world.grid[i] = malloc(sizeof(int) * world.cols);
    }

    /* init world */
    world.grid[init.x][init.y] = 1;
    world.grid[0][0] = 1;
    world.grid[9][9] = 1;
    world.grid[init.x-3][init.y] = 1;
    world.grid[init.x - 1][init.y - 1] = 1;
    world.grid[init.x + 1][init.y + 1] = 1;
    world.grid[init.x + 2][init.y + 1] = 1;
    world.grid[init.x + 2][init.y] = 1;
    world.grid[init.x + 2][init.y+2] = 1;

    /* populate struct timeval struct start_time with time since epoch */
    gettimeofday(&start_time, NULL);
    puts("Start");
    printworld(&world);
    for(int i = 0; i < iterations; i++){
        /* for each live cell are there 0 or 1 neighbours ?*/
        findlivecell(&world, &modifications, &livecells);
        finddeadcell(&world, &modifications);
        printworld(&world);
        printlivecells(livecells);
        livecells = 0;

        //finddeadwithneighbours

        /* prints modifications */
        //printmodifications(&modifications);


        /* modify world with modifications */
        updateworld(&world, &modifications);

        //printworld(&world);
        //usleep(100000);  // sleep for 100,000 micro seconds (0.1 seconds)
        //sleep(1);
    }


    /* populate struct timeval struct end_time with time since epoch */
    gettimeofday(&end_time, NULL);
    puts("End");
    printworld(&world);


    /* free allocated memory */
    for(int i = 0; i < world.rows; i++){
        free(world.grid[i]);
    }
    free(world.grid);


    /* calculate difference in time */
    printf("Time taken: %lu,  %d iterations\n", end_time.tv_usec - start_time.tv_usec, iterations);
}

int iscelllonely(world *world, int x, int y){
    /* keep count of number of neighbours */
    int neighbours = 0;
    /* loop over section of world to find neighbours */
    for(int i = -1; i < 2; i++)
        for(int j = -1; j < 2; j++){
            /* when x = 0 & j = 0 we're looking at already known cell so skip */
            if(i == 0 && j == 0) continue;
            /* wraps around world */
            int xt, yt;
            xt = x + i < 0 ? world->rows - 1 : x + i == world->rows ? 0 :  x + i;
            yt = y + j < 0 ? world->cols - 1 : y + j == world-> cols ? 0 : y + j;
            /* if life is present inc neighbours */
            if(world->grid[xt][yt])
                neighbours++;
            /* if neighbours greater than 1 cell is not lonely */
            if(neighbours > 1)
                return 0;
        }
    /* if we reach here cell is lonely */
    return 1;
}

int iscelloverpopulated(world *world, int x, int y){
    /* keep count of number of neighbours */
    int neighbours = 0;
    /* loop over section of world to find neighbours */
    for(int i = -1; i < 2; i++)
        for(int j = -1; j < 2; j++){
            /* when x = 0 & j = 0 we're looking at already known cell so skip */
            if(i == 0 && j == 0) continue;
            /* wraps around world */
            int xt, yt;
            xt = x + i < 0 ? world->rows - 1 : x + i == world->rows ? 0 :  x + i;
            yt = y + j < 0 ? world->cols - 1 : y + j == world-> cols ? 0 : y + j;
            /* if life is present inc neighbours */
            if(world->grid[xt][yt])
                neighbours++;
            /* if neighbours greater than 3 cell is overpopulated*/
            if(neighbours > 3)
                return 1;
        }
    /* if we reach here cell is not overpopulated */
    return 0;
}


void addmodification(modifications *modifications, int life, int y, int x){
    modifications->mods[modifications->count].x = x;
    modifications->mods[modifications->count].y = y;
    modifications->mods[modifications->count].life = life;
    modifications->count++;
}

void findlivecell(world *world, modifications *modifications, int *livecells){
    /* iterate over world to find live cells */
    for(int j = 0; j < world->cols; j++)
        for(int k = 0; k < world->rows; k++){
            if(world->grid[j][k] == 1){
                /* add to livecell count */
                (*livecells)++; 
                /* are there 0 or 1 neighbours ? */
                if (iscelllonely(world, j, k)){
                    /* update modification array */
                    addmodification(modifications, 0, j, k);
                }else if(iscelloverpopulated(world, j, k)){
                    /* update modification array */
                    addmodification(modifications, 0, j, k);
                }
            }
        }
}

int hasliveneighbours(world *world, int x, int y){
    /* keep count of number of neighbours */
    int neighbours = 0;
    /* loop over section of world to find neighbours */
    for(int i = -1; i < 2; i++)
        for(int j = -1; j < 2; j++){
            /* when x = 0 & j = 0 we're looking at already known cell so skip */
            if(i == 0 && j == 0) continue;
            /* wraps around world */
            int xt, yt;
            xt = x + i < 0 ? world->rows - 1 : x + i == world->rows ? 0 :  x + i;
            yt = y + j < 0 ? world->cols - 1 : y + j == world-> cols ? 0 : y + j;
            /* if life is present inc neighbours */
            if(world->grid[xt][yt])
                neighbours++;
            /* if neighbours greater than 3 cell is overpopulated*/
            if(neighbours > 3)
                return 0;
        }
    /* if we reach here cell is not overpopulated */
    if(neighbours == 3){
        return 1;
    }else
        return 0;

}


void finddeadcell(world *world, modifications *modifications){
    /* iterate over world to find dead cells */
    for(int j = 0; j < world->cols; j++)
        for(int k = 0; k < world->rows; k++){
            if(world->grid[j][k] == 0){
                /* does dead cell have exactly three live neighbours? */
                if(hasliveneighbours(world, j, k)){
                    /* update modification array */
                    addmodification(modifications, 1, j, k);
                }
            }
        }
}


void printmodifications(modifications *modifications){
    /* loops through modifications array and prints modification */
    for(int i = 0; i < modifications->count; i++){
        printf("x: %d y: %d life: %d\n", modifications->mods[i].x, modifications->mods[i].y, modifications->mods[i].life);
    }
}

void updateworld(world *world, modifications *modifications){
    /* loops through modification array and updates world */
    for(int i = 0; i < modifications->count; i++){
        world->grid[modifications->mods[i].y][modifications->mods[i].x] = 
            modifications->mods[i].life;
    }
    /* set modifications count to zero after updates */
    modifications->count = 0;
}

void printworld(world *world){
    /* print world */
    for(int i = 0; i < world->rows; i++){
        for(int j = 0; j < world->cols; j++)
            /* prints @ for live cell and . for dead cell for ease of viewing */
            printf("%c ", world->grid[i][j] ? '@' : '.');
        puts("");
    }
}

void printlivecells(int livecells){
    printf("Live cells: %d\n", livecells);
}
