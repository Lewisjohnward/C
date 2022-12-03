#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (void){
    FILE *fp;
    char buf[100];
    char delim[] = "\n";
    char *ptr;
    int len = 0;
    unsigned int score = 0;

    if((fp = fopen("input", "r")) == 0){
        puts("Fopen");
        exit(-1);
    }
    while(fgets(buf, 100, fp)){
        ptr = strtok(buf, delim);
        len = strlen(ptr);
        for(int i = 0; i < len / 2; i++){
            for(int j = len / 2; j < len; j++){
                if(ptr[i] == ptr[j])
                {
                    printf("%d %c %d %c", i, ptr[i], j, ptr[j]);
                    if(ptr[i] < 91)
                    {
                        score += ptr[i] - 38;
                        printf("%c %d\n", ptr[i], ptr[i] - 38);
                    }
                    else
                    {
                        score += ptr[i] - 96;
                        printf("%c %d\n", ptr[i], ptr[i] - 96);
                    }
                    printf("score: %d\n", score);
                }
            }
        }
    }

    printf("%d\n", score);

    return 0;
}
