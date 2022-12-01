/*
 * Codewars: Assembler interpreter (part 2)
 * https://www.codewars.com/kata/58e61f3d8ff24f774400002c
 *
 * time taken: 3h:30min ( so far)
 *
 */

/*
 *
 * WORK IN PROGRESS: WILL NOT WORK
 *
 */


#include <string.h>
#include <stdlib.h>

#define MAXBUF 1024
#define MAXLINE 200
#define MAXREG 26

char* assembler_interpreter (const char* program) {
  /* contains register values */
  int registers[MAXREG] = {0};
  /* buf contains program copy */
  char buf[MAXBUF];
  /* each line points to instruction */
  char *line[MAXLINE];
  char delim[] = "\n";
  
  char *op;
  char *dest;
  char *src;
  
  char *funname;
  
  /* copy string to buf as strtok mutates and 
   * program is const
   */  
  strcpy(buf, program);
  
  
  /* tokenise program and point assign to line[i] */
  int i = 0;
  line[i++] = strtok(buf, delim);
  while(line[i] = strtok(NULL, delim))
    {i++;}
  printf("total lines: %d\n", i);
  
  int pos = 0;
  /* iterate lines to replace call with line numbers */
  for(int j = 0,  k = 0; j < i; j++){
    if(*line[j] == 'c'){
      strtok(line[j], " ");
      funname = strtok(NULL, " ");
      for(int l = j; l < i; l++){
        if(strcmp(funname, line[l]) == -58)
          sprintf(line[j], "jmp %c", l + 1 + 48);
        for(int r = l; r < i; r++){
          if(!strcmp("    ret", line[r]))
          {
            sprintf(line[r], "jmp %c", j + 1 + 48);
            break;
          }
        }
      }
    }
  }
  
  for(int j = 0; j < i; j++)
    printf("%02d : %s\n", j, line[j]);

  for(int j = 0; j < 4; j++){
    puts(line[j]);
    /* skip iteration if line starts with ; 
    * equivalent **(lines + j) == *line[j] 
    */
    if(*line[j] == ';')
      continue; 

    /* tokenise line */
    op = strtok(line[j], " ");
    dest = strtok(NULL, ",");
    src = strtok(NULL, " ");

    /* Increment pointer to get rid of whitespace */
    /* some programs have different width between ins */
    dest += 1;

    //puts(op);
    //puts(dest);
    //puts(src);

    switch(op[0]){
      case 'm':
        if(atoi(src))
          registers[dest[0] - 97] = atoi(src);
        else
          registers[dest[0] - 97] = registers[src[0] - 97];
        break;
        case 'i':
          registers[dest[0] - 97]++;
        break;
        case 'd':
          registers[dest[0] - 97]--;
        break;
        case'j':
          for(int t = 0; t < 20; t++)
            printf("%c", *(line[j] + t));
        break;
    }


    /* print registers */
    for(int j = 0; j < MAXREG; j++)
      printf("%c  ", j + 97);
    puts("\n");
    for(int j = 0; j < MAXREG; j++)
      printf("%d  ", registers[j]);
    puts("\n");
  }

}
