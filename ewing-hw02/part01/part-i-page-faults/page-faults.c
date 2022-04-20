/*
 * page-faults.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>


int
main(int argc, char *argv[])
{
    char * mmap_pointer;
   
    mmap_pointer = mmap(NULL, 8192, PROT_READ | PROT_WRITE, MAP_ANONYMOUS, -1, 0);

    printf("mmap pointer: %p\n", mmap_pointer);
    fflush(stdout);
    strcpy(mmap_pointer, "Page should fault");
    strcpy(mmap_pointer + 200, "Page should not fault");

    printf("MMap pointer + 4096: %p\n", mmap_pointer + 4096);
    fflush(stdout);
    strcpy(mmap_pointer + 4096, "Page should fault with no seg fault");

    printf("MMap pointer + 8192: %p\n", mmap_pointer + 8192);
    fflush(stdout);
    strcpy(mmap_pointer + 8192, "Page should fault and seg fault should happen");
}