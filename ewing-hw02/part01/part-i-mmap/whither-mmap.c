/*
 * whither-mmap.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

void wait_for_input(void);

int
main(int argc, char *argv[])
{
    pid_t mypid;
    char * mmap_pointer;
    mypid = getpid();
    printf("my pid is %d\n", mypid);
    fflush(stdout);

    char vmcmd[32];
    snprintf(vmcmd, 32, "procstat vm %d", mypid);

    printf("Before mmap:\n");
    fflush(stdout);
    system(vmcmd);
    wait_for_input();
    
    mmap_pointer = mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);
    printf("MMap pointer: %p ", mmap_pointer);
    fflush(stdout);
    strcpy(mmap_pointer, "This should cause a page fault, making mmap mapping increase in size");

    printf("After first mmap:\n");
    fflush(stdout);
    system(vmcmd);
}

void
wait_for_input(void)
{
    char buf[2];
    read(0, buf, 2);
}

