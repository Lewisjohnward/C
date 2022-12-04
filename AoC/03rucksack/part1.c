#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* 
 * time taken: 30 mins
 */

int main (void){
    FILE *fp;
    char buf[100];
    char delim[] = "\n";
    char *ptr;
    int len = 0;
    int score = 0;

    if((fp = fopen("input", "r")) == 0){
        puts("Fopen");
        exit(-1);
    }
    int count = 0;
    int temp = 0;
    int found = 0;
    while(fgets(buf, 100, fp)){
        ptr = strtok(buf, delim);
        len = strlen(ptr);
        for(int i = 0; i < len / 2; i++){
            for(int j = len / 2; j < len; j++){
                if(ptr[i] == ptr[j]){
                    if(ptr[i] < 91)
                        score += ptr[i] - 38;
                    else
                        score += ptr[i] - 96;
                    goto cont;
                }
            }
        }
        cont:
        found = 0;
    }

    printf("%d\n", score);

    return 0;
}
