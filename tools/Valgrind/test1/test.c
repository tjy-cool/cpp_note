// // 使用未初始化的内存
// #include <stdio.h>

// // gcc -o test -g -c test.c

// int main()
// {
//     int x;
//     if(x == 0)
//     {
//         printf("x is zero\n");
//     }
//     return 0;
// }

#include <stdlib.h>

int main()
{
    char *x = (char*)malloc(20);
    char *y = (char*)malloc(20);
    x=y;
    free(x);
    free(y);
    return 0;
}