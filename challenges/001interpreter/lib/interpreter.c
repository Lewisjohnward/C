#include "interpreter.h"


void interpreter(size_t n, char const *program[], int registers[]){
  char buf[50];
  char delim[] = " ";

  char *ins[3];


  /* Iterate over *program[] */
  for(int i = 0; i < n; i++) {
      printf("i: %d\n", i);

    printf("%d:%s\n", i, program[i]);
    strcpy(buf, program[i]);

    /* splits the instruction up
     * ins[0] op
     * ins[1] dest
     * ins[2] source
     */
    for(int j = 0; j < 3; j++){
      if (j == 0)
          ins[j] = strtok(buf, delim);
      else
        ins[j] = strtok(NULL, delim);
    }

    /* conditional statement that
     * register[**(ins+1)] is the value in dest
     * register[**(ins+2)] is the value in source
     *
     * The Codewars challenge indexes the array using
     * a-z but this implementation transforms a->0 
     * z-> 26 hence the -97
     */

    if(!strcmp(ins[0], "mov")) {
      if(atoi(ins[2]))
        registers[**(ins+1) - 97] = atoi(ins[2]);
      else
        registers[**(ins+1) - 97] = registers[**(ins+2) - 97];
    } else if(!strcmp(ins[0], "inc")) {
      registers[**(ins+1) - 97]++;
    } else if(!strcmp(ins[0], "dec")) {
      registers[**(ins+1) - 97]--;
    } else if(!strcmp(ins[0], "jnz")) {
        /* Ensures that instruction is valid */
        if(atoi(ins[1]) || registers[**(ins+1) - 97])
        {
            int val =  atoi(*(ins+2)) ? atoi(*(ins+2)) : registers[**(ins+2) - 97];
                /* -1 needed, cancel out +1 of loop */
                i = i + val - 1;
        }
    }

    /* prints out registers & their values */
    for(int j = 0; j < 26; j++)
      printf("%c ", 97 + j);
    puts("");
    for(int j = 0; j < 26; j++)
      printf("%d ", registers[j]);
    puts("\n");
  }
}

