#include "parser.h"

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

void printregisters(char *registers, int zf, int gf){
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
    char delim[] = " ";

    char opcode[4];
    char dest;
    char source;

    int jmpdest = 0;

    int count = 0;
    int instruction = 0;

    char msgbuffer[100];
    /* while instruction is not "end" execute */
    while(strcmp(line[instruction], "end")){
        /* print line for debugging */
        printf("%d:%s\n", instruction, line[instruction]);

        /* splits the instruction up
         * ins[0] op
         * ins[1] dest
         * ins[2] source
         */

        /* for debugging */
        //if(count == 52) break;

        /* sscanf parses line and places in respective variables */
        sscanf(line[instruction], "%s %c, %c", opcode, &dest, &source);
        /* print variables for debugging */
        printf("%s %c %c\n", opcode, dest, source);

        /* conditional statement that
         * register[**(ins+1)] is the value in dest
         * register[**(ins+2)] is the value in source
         *
         * The Codewars challenge indexes the array using
         * a-z but this implementation transforms a->0 
         * z-> 26 hence the -97
         */

        if(!strcmp(opcode, "jmp")){
            char *ptr = line[instruction];
            ptr += strlen("jmp") + 1;
            jmpdest = atoi(ptr);
        }



        if(!strcmp(opcode, "mov")) {
            if(source - 97 < 0)
                registers[dest - 97] = source - 48;
            else
                registers[dest - 97] = registers[source - 97];
        } else if(!strcmp(opcode, "inc")) {
            registers[dest - 97]++;
        } else if(!strcmp(opcode, "dec")) {
            registers[dest - 97]--;
        } else if(!strcmp(opcode, "jmp")){
            instruction = jmpdest - 1;
        } else if(!strcmp(opcode, "mul")){
            registers[dest - 97] = registers[source - 97] * registers[dest - 97];
        } else if(!strcmp(opcode, "cmp")){
            if(source - 97 < 0){
                if(registers[dest - 97] - (source - 48) > 0){
                    gf = 1;
                }else
                    gf = 0;
                if(registers[dest - 97] - (source - 48) == 0){
                    zf = 1;
                }else
                    zf = 0;
            }
            else{
                if(registers[dest - 97] - registers[source - 97] > 0){
                    gf = 1;
                }else
                    gf = 0;
                if(registers[dest - 97] - registers[source - 97] == 0)
                    zf = 1;
                else
                    zf = 0;
            }
        } else if(!strcmp(opcode, "jne")){
            if(!zf)
                instruction = dest - 48 - 1;
        } else if(!strcmp(opcode, "msg")){
            char msg[50];
            char *msgptr = msg;
            /* pointer to instruction */
            char *ptr = line[instruction];
            /* increment pointer to remove msg*/
            while(*ptr++ != ' ');

            while(*ptr != '\0'){
                if(*ptr > 96 && *ptr < 123){
                    printf("%c\n", registers[*ptr - 97] + '0');
                    *msgptr++ = registers[*ptr - 97] + '0';
                    *msgptr = '\0';
                    puts(msg);
                }
                /* start of string */
                if(*ptr == '\''){
                    /* first char of string */
                    *ptr++;
                    /* while not pointing to end of string */
                    while(*ptr != '\''){
                        *msgptr++ = *ptr;
                        *msgptr = '\0';
                        *ptr++;
                    }
                }
                *ptr++;
            }
            puts(msg);
            strcpy(msgbuffer, msg);
            /*
             *   print:\n\
             *    msg   a, '! = ', c ; output text\n\
             *    ret\n\
             *  ", "5! = 120");
             */

        } else{
            puts("INSTRUCTION NOT RECOGNISED!!\nending program");
            break;
        }
        printregisters(registers, zf, gf);



        count++;
        instruction++;
    }
    puts("end");
    printregisters(registers, zf, gf);
    printf("%s\n", msgbuffer);
}

int main (void){
    char *line[100];
    char buf[20];
    int ins = 0;

    /* allocate space for instructions arr */
    for(int i = 0; i < 100; i++) 
        line[i] = malloc(100 * sizeof(char));

    /* parse string program and place instructions in line[] */
    parseinstructions(myprog1, line, &ins);

    /* execute instructions a line at a time */
    executeinstructions(line, ins);


    for(int j = 0; j < ins; j++)
    {
        printf("%02d: ", j);
        puts(line[j]);
    }
}


