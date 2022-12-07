/*
 * Advent of Code 2022 day 7: No Space Left On Device
 * Part 1
 * time taken: WIP
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct dir{
    /* this points to parent dir */
    struct dir *parent;
    /* contains current dir name */
    char currentdir[50];
    /* contains an array of pointers to childen dirs */
    struct dir *child[50];
    /* contains the number of children directories */
    int children;
    /* contains an array of file sizes */
    int files[100];
    /* contains total size */
    int totalsize;
} dir;

int main (void){
    FILE *fp;
    dir root;
    dir *cwd;
    cwd = &root;

    char tmp[50];
    char buf[100];
    /* 0 files array in root */
    memset(root.files, 0, 100); memset(root.child, 0, 50);

    /* user starts in top level dir '/' */
    /* init root dir */
    strcpy(root.currentdir, "/");
    root.children = 0;
    root.totalsize = 0;


    /* open file to read */
    if((fp = (fopen("input", "r")) )== 0){
        puts("Error: fopen");
        exit(-1);
    }

    int count = 0;
    /* get a line of input into buf*/
    /* when while loop is finished file system structure has been mapped */
    while(fgets(buf, 100, fp) != 0){
        //puts(cwd->currentdir);

        /* remove newline from buf */
        buf[strcspn(buf, "\n")] = 0;

        /* first line puts us in root '/' can ignore */
        if(strcmp("$ cd /", buf) == 0)
            continue;

        if(buf[0] == '$'){
            if(buf[2] == 'c'){
                /* if cd .. go up dir */
                if(buf[5] == '.'){
                    /* point to parent dir */
                    cwd = cwd->parent;
                }else{
                    /* cd to relative dir */
                    char *ptr;
                    strcpy(tmp, buf);
                    ptr = tmp;
                    *(ptr+= 5);
                    /* ptr points to beginning of dir name */
                    /* dirname starts at tmp[5] */
                    for(int i = 0; i < cwd->children; i++){
                        if(!strcmp(cwd->child[i]->currentdir, ptr))
                            /* point to child */
                            cwd = cwd->child[i];
                    }
                }
            }
        }

        /* buf contains a dir listing */
        if(buf[0] == 'd'){
            char *ptr;
            ptr = buf;
            /* remove 'dir' from beginning */
            *(ptr+=4);
            /*update dir struct */
            /* add child dir */
            cwd->child[cwd->children] = malloc(sizeof(dir));
            /* cpy child dir name */
            strcpy(cwd->child[cwd->children]->currentdir, ptr);
            /* 0 files array */
            memset(cwd->child[cwd->children]->files, 0, 100);
            cwd->child[cwd->children]->parent = cwd;
            cwd->child[cwd->children]->totalsize = 0;
            cwd->children++;
        }

        /* buf contains a file listing */
        if(buf[0] > 48 && buf[0] < 58){
            /* ptr points to beginning of files arr */
            int *ptr = cwd->files;
            /* move pointer to empty arr */
            while(*ptr != 0)
                *ptr++;
            /* assign element to file size */
            *ptr = atoi(buf);
            cwd->totalsize += atoi(buf);
        }
    }

    puts(root.currentdir);

    for(int i = 0; i < root.children; i++){
      puts(root.child[i]->currentdir);
    }

    for(int i = 0; i < root.child[1]->children; i++){
      puts(root.child[1]->child[i]->currentdir);
    }









    return 0;


}
