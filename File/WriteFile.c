/*************************************************************************
    > File Name: WriteFile.c
    > Author: tjy-cool
    > Mail: tjuyuan@163.com 
    > Created Time: 二  1/22 23:08:24 2019
 ************************************************************************/
#include <stdio.h>

int main()
{
    FILE *fp = NULL;
    fp = fopen("test.txt", "w+");
    if(fp == NULL)  // 打开文件失败
    {
        printf("open failed\n");
    }
    char buffer[] = "this is a line";
    int nWrite = fwrite(buffer, sizeof(char), sizeof(buffer), fp);
    printf("write %d char\n", nWrite);  // 打印写入的个数
    fclose(fp);
    return 0;
}


