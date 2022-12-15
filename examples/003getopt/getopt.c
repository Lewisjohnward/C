#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * Example usage of getopt
 *
 * getopt
 * aflag = 0, bflag = 0, cvalue = (NULL)
 *
 * getopt -a -b
 * aflag = 1, bflag = 1, cvalue = (NULL)
 *
 * getopt -c foo
 * aflag = 0, bflag = 0, cvalue = foo
 */


int main (int argc, char *argv[]){

    int aflag = 0;
    int bflag = 0;
    char *cvalue = NULL;
    int c;

    while ((c = getopt (argc, argv, "abc:")) != -1){
        switch(c){
            case 'a':
                aflag = 1;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'c':
                cvalue = optarg;
                break;
            case '?':
                if (optopt == 'c')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if(isprint (optopt))
                    fprintf(stderr, "Unkown option -%c \n", optopt);
                else
                    fprintf(stderr, "Unkown character %x\n", optopt);
                return 1;
            default:
                abort();
        }
    }

    printf("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);

    for(int i = optind; i < argc; i++)
        printf("Non-option argument %s\n", argv[i]);
    return 0;
}
