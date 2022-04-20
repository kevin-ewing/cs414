/*
 * maximum-resident.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define TOTAL_BYTES 65536

void wait_for_input(void);


int
main(int argc, char *argv[]){
    pid_t mypid;
    mypid = getpid();
    printf("my pid is %d\n", mypid);
    fflush(stdout);

    char vmcmd[32];
    snprintf(vmcmd, 32, "procstat vm %d", mypid);

    printf("Before malloc\n");
    fflush(stdout);
    system(vmcmd);
    wait_for_input();

    char *p = malloc(TOTAL_BYTES);
    if(p == NULL) {
        perror("malloc");
        exit(1);
    }

    printf("After malloc but before forcing to be resident\n");
    fflush(stdout);
    system(vmcmd);
    wait_for_input();

    for (int i = 0; i < TOTAL_BYTES; i += 4096){
        *(p + i) = 0;
    }

    printf("After forcing to be resident\n");
    fflush(stdout);
    system(vmcmd);
    wait_for_input();

    free(p);
}

void
wait_for_input(void)
{
    char buf[2];
    read(0, buf, 2);
}