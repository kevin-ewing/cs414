/*
 * page-size.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define TOTAL_BYTES 1000000

int
main(int argc, char *argv[]){
   
    char *p = malloc(TOTAL_BYTES);
    if(p == NULL) {
        perror("malloc");
        exit(1);
    }

    printf("malloc pointer: %p\n", p);
    fflush(stdout);

    memset(p, 0, TOTAL_BYTES);
}
