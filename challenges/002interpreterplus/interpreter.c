#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void interpretinstruction(int *instructionpointer, char *instruction, char *registers, int *gf, int *zf, char *msgbuffer){

    char opcode[4];
    char dest;
    char source;

    /* sscanf parses line and places in respective variables */
    sscanf(instruction, "%s %c, %c", opcode, &dest, &source);

    int jmpdest;
    if(!strcmp(opcode, "jmp")){
        char *ptr = instruction;
        ptr += strlen("jmp") + 1;
        jmpdest = atoi(ptr);
    }

    /* print variables for debugging */
    printf("op: %s dest: %c source: %c\n", opcode, dest, source);

    if(!strcmp(opcode, "mov")) {
        if(source - 97 < 0)
            registers[dest - 97] = source - 48;
        else
            registers[dest - 97] = registers[source - 97];
    } else if(!strcmp(opcode, "add")){
        if(source - 97 < 0)
            registers[dest - 97] = registers[dest - 97] + (source - 48);
        else
            registers[dest - 97] = registers[dest - 97] +registers[source - 97];
    } else if(!strcmp(opcode, "inc")) {
        registers[dest - 97]++;
    } else if(!strcmp(opcode, "dec")) {
        registers[dest - 97]--;
    } else if(!strcmp(opcode, "jmp")){
        *instructionpointer = jmpdest - 1;
    }else if(!strcmp(opcode, "jl")){
        if(!*gf)
            *instructionpointer = jmpdest - 1;
            
    } else if(!strcmp(opcode, "mul")){
        registers[dest - 97] = registers[source - 97] * registers[dest - 97];
    } else if(!strcmp(opcode, "cmp")){
        /* If source is less than 97 refers to constant */
        if(source - 97 < 0){
            if(registers[dest - 97] - (source - 48) > 0){
                *gf = 1;
            }else
                *gf = 0;
            if(registers[dest - 97] - (source - 48) == 0){
                *zf = 1;
            }else
                *zf = 0;
        }
        /* Source is a register */
        else{
            if(registers[dest - 97] - registers[source - 97] > 0){
                *gf = 1;
            }else
                *gf = 0;
            if(registers[dest - 97] - registers[source - 97] == 0)
                *zf = 1;
            else
                *zf = 0;
        }
    } else if(!strcmp(opcode, "jne")){
        if(!zf)
            *instructionpointer = dest - 48 - 1;
    }else if(!strcmp(opcode, "jle")){
        if (zf || *gf) *instructionpointer = dest - 48 - 1;
    } else if(!strcmp(opcode, "msg")){
        char msg[50];
        char buf[50];
        char *msgptr = msg;
        /* pointer to instruction */
        char *ptr = instruction;
        /* increment pointer to remove msg*/
        while(*ptr++ != ' ');

        while(*ptr != '\0'){
            if(*ptr > 96 && *ptr < 123){
                sprintf(buf, "%d", registers[*ptr - 97]);
                strcat(msgbuffer, buf);
            }
            /* start of string */
            if(*ptr == '\''){
                /* first char of string */
                *ptr++;
                /* while not pointing to end of string */
                while(*ptr != '\''){
                    printf("%c\n", *ptr);
                    *msgptr++ = *ptr;
                    *msgptr = '\0';
                    *ptr++;
                }
                printf("%s\n", msg);
                strcat(msgbuffer, msg);
                printf("%s\n", msgbuffer);
            }
            *ptr++;
        }
    } else if(!strcmp(opcode, "div")){
        /* an immediate not a register */
        if(source - 97 < 0)
            registers[dest - 97] = registers[dest - 97] / (source - 48);
        else
            registers[dest - 97] = registers[dest - 97] / registers[source - 97];
    }else if(strchr(instruction, ':')){
    
    }else{
        puts("INSTRUCTION NOT RECOGNISED!!\nending program");
        abort();
    }
}
