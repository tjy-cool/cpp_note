/**
 * va_list ap;          // 定义一个指针, 用来定义一个表示参数表中各个参数的变量，即定义了一个指向参数的指针， 用于指示可选的参数.
 * va_start(ap, v);     // 初始化指针
 * va_arg(ap, type);    // 返回参数列表中指针ap所指的参数, 返回类型为type. 并使指针ap指向参数列表中下一个参数.返回的是可选参数, 不包括固定参数.
 * va_end(ap);          // 清空参数列表, 并置参数指针arg_ptr无效.
 */ 
#include <stdarg.h>
#include <stdio.h>

/*
void simple_va_fun(int i, ...);

int main(int argc, char* argv[])
{
    simple_va_fun(100);
    simple_va_fun(200, 201);
    simple_va_fun(300, 301, "a");
    return 0;
}

void simple_va_fun(int i, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, i);

    int j=va_arg(arg_ptr, int);
    char c = va_arg(arg_ptr, char);

    va_end(arg_ptr);
    printf("%d %d %c\n", i, j, c);

}
*/

//#define debug(format, args...) printf (format, ##args)
#define debug(format, ...) printf(format, ##__VA_ARGS__)

#include <stdio.h>
int main(){
    debug("Hello %s\n", "world");
    debug("hello world\n");
    return 0;
}
