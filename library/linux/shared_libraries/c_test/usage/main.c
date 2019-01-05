#include <stdio.h>

extern void printHello();
extern int add(int a, int b);
extern int subtract(int a, int b);
extern int multiply(int a, int b);
extern int divide(int a, int b);

int main()
{
    int a = 12;
    int b = 3;

    printHello();
    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", add(a, b));
    printf("a - b = %d\n", subtract(a, b));
    printf("a * b = %d\n", multiply(a, b));
    printf("a / b = %d\n", divide(a, b));
    return 0;
}