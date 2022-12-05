#include "parser.h"

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
}

void removemultiplewhitespacestr(char *str){
    char *dest = str;
    /* While we're not at the end of the string, loop... */
    while (*str != '\0')
    {
        /* Loop while the current character is a space, AND the next
         * character is a space
         */
        while (*str == ' ' && *(str + 1) == ' ')
            str++;  /* Just skip to next character */

       /* Copy from the "source" string to the "destination" string,
        * while advancing to the next character in both
        */
       *dest++ = *str++;
    }

    /* Make sure the string is properly terminated */
    *dest = '\0';
}

void removemultiplewhitespace(char *line[], int ins){
    for(int i = 0; i < ins; i++){
        removemultiplewhitespacestr(line[i]);
    }
}

void replacewithjmp(char *jmp, char *line, const int pos)
{
    /* replaces given line with jmp instructions */
    char fmtstr[50];
    sprintf(fmtstr, "%s %d", jmp, pos+1);
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
            for(int j = i; j < ins; j++){
                /* iterate to find function definition ':' = 58*/
                if(strcmp(line[i], line[j]) == -58){
                    //strcpy(line[j], "FUN");
                    replacewithjmp("jmp", line[i], j);
                    /* iterate to find function return */
                    for(int k = j; k < ins; k++)
                        if(!strcmp(line[k], "ret")){
                            replacewithjmp("jmp", line[k], i);
                            break;
                        }
                    /* CONDITIONAL JUMP HANDLING HERE */
                    for(int k = j; k < ins; k++)
                        if(*line[k] ==  'j' && *(line[k] + 1) != 'm' && *line[k] != 'J'){
                            strcpy(tmp, line[k]);
                            tk = strtok(tmp, delim);
                            strtok(NULL, "");
                            tk[0] = 'J';
                            replacewithjmp(tk, line[k], j);
                        }
                }
            }
        }
    }
    /* make upper case J lower case */
    for(int i = 0; i < ins; i++){
        if(*(line[i]) == 'J')
            *(line[i]) = 'j';
    }
}


/* parse string program and put into *line[] and count instructions */
void parseinstructions(char *program, char *line[], int *ins){
    parselines(program, line, ins);
    removemultiplewhitespace(line, *ins);
    replacefunctioncalls(line, *ins);
}
