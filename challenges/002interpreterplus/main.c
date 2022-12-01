#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 * Codewars: Assembler interpreter (part 2)
 * https://www.codewars.com/kata/58e61f3d8ff24f774400002c
 *
 * time taken: 6h:20min ( so far)
 *
 */

/*
 *
 * WORK IN PROGRESS: WILL NOT WORK
 *
 */

char myprog[] = 
"; My first program\n"
"mov  a, 5\n"
"inc  a\n"
"call    function\n"
"msg  '(5+1)/2 = ', a    ; output message\n"
"end\n"
"\n"
"function:\n"
"    div  a, 2\n"
"    ret\n";

char myprog1[] = 
"mov   a, 5\n"
"mov   b, a\n"
"mov   c, a\n"
"call  proc_fact\n"
"call  print\n"
"end\n"
"\n"
"proc_fact:\n"
"    dec   b\n"
"    mul   c, b\n"
"    cmp   b, 1\n"
"    jne   proc_fact\n"
"    ret\n"
"\n"
"print:\n"
"    msg   a, '! = ', c ; output text\n"
"    ret\n";



#include <string.h>
#include <stdlib.h>

#define MAXBUF 1024
#define MAXLINE 200
#define MAXREG 26


void parselines(char *prog, char *line[], int *ins){
    char ndelim[] = "\n";
    char *temp;

    temp = strtok(prog, ndelim);
    do{
        /* remove line comments & empty lines */
        if(temp[0] != ';' && temp[0] != '\n' && temp[0] != ' ')
            strcpy(line[(*ins)++], temp);
        /* increment temp to trim whitespace */
        else if(temp[0] == ' '){
            while(*temp == ' ')
            {*temp++;}
            strcpy(line[(*ins)++], temp);
        }
    }while(temp = strtok(NULL, ndelim));

    /* remove inline comments */
    for(int j = 0; j < *ins; j++){
        char cdelim[] = ";";
        temp = strtok(line[j], cdelim);
        strcpy(line[j], temp);
    }

    //for(int j = 0; j < *ins; j++)
    //    puts(line[j]);
}

void replacewithjmp(char *line, const int pos)
{
    /* replaces given line with jmp instructions */
    char fmtstr[50];
    sprintf(fmtstr, "jmp %d", pos+1);
    strcpy(line, fmtstr);
}

void replacefunctioncalls(char *line[], const int ins){
    char tmp[100];
    char delim[] = " ";
    char *tk;
    int jmpto = 0;

    for(int i = 0; i < ins; i++){
        /* if line starts will 'c'all & c'a'll to destinguish from cmp*/
        if(*line[i] == 'c' && *(line[i]+1) == 'a'){
            /*copy line to temp*/
            strcpy(tmp, line[i]);

            strtok(tmp, delim);
            /* tk contains function name e.g: call XX*/
            tk = strtok(NULL, "");
            /* while loop trims whitespace if present */
            while(*tk == ' '){*tk++;}
            /* copy function name senz white space (serves no purpose) */
            strcpy(line[i], tk);
            /* loop to find the function definition */
            for(int j = i; j < ins; j++)
                /* iterate to find function definition ':' = 58*/
                if(strcmp(line[i], line[j]) == -58){
                    //strcpy(line[j], "FUN");
                    replacewithjmp(line[i], j);
                    /* iterate to find function return */
                    for(int k = j; j < ins; k++)
                        if(!strcmp(line[k], "ret")){
                            replacewithjmp(line[k], i);
                            break;
                        }

                    /* NEEDS TO HANDLE CONDITIONAL JUMPS HERE */
                    /* FUNCTIONS CAN JUMP TO OTHER FUNCTIONS */

                    break;
                }
        }
    }
}

int main (void){
    char *line[100];
    char buf[20];
    int ins = 0;

    for(int i = 0; i < 100; i++) 
        line[i] = malloc(100 * sizeof(char));

    parselines(myprog1, line, &ins);
    replacefunctioncalls(line, ins);

    for(int j = 0; j < ins; j++)
    {
        printf("%02d: ", j);
        puts(line[j]);
    }
}


