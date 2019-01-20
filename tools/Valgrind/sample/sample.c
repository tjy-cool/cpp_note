#include <stdio.h>
#include <stdlib.h>

/*************************************************
 * gcc -g -O0 sample.c -o sample
 ************************************************/

void fun()
{
    int *p = (int*)malloc(10*sizeof(int));
    p[10]=10;   //problem 1: heap block overrun
                //problem 2: memory leak -- x not freed
}

int main(int argc, char *argv[])
{
    fun();
    return 0;
}