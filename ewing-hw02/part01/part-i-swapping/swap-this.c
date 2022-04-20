/*
 * swap-this.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define TOTAL_BYTES 4000000000

void wait_for_input(void);


int
main(int argc, char *argv[]){
    pid_t mypid;
    mypid = getpid();
    printf("my pid is %d\n", mypid);
    fflush(stdout);

    char vmcmd[32];
    snprintf(vmcmd, 32, "procstat vm %d", mypid);

    char * vmstatcmd = "vmstat -s";

    printf("Before malloc\n");
    fflush(stdout);
    system(vmcmd);
    system(vmstatcmd);
    wait_for_input();
    fflush(stdout);


    char * p = malloc(TOTAL_BYTES);
    if(p == NULL) {
        perror("malloc");
        exit(1);
    }

    for (uint64_t i = 0; i < TOTAL_BYTES; i += 4096){
        *(p + i) = 0;
    }

    printf("After forcing swapping\n");
    fflush(stdout);
    system(vmcmd);
    system(vmstatcmd);
    wait_for_input();
    fflush(stdout);

    free(p);
}

void
wait_for_input(void)
{
    char buf[2];
    read(0, buf, 2);
}
