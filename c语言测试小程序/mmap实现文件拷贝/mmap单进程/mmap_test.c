#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 512

// 运行 ./mmap_test aa.txt
int main(int argc, char* argv[])
{
    int fd;
    struct stat sb;
    char* mmaped, buf[BUF_SIZE];

    for(int i = 0; i < BUF_SIZE; ++i)
    {
        buf[i] = '#';
    }

    // 
    if((fd=open(argv[1], O_RDWR)) < 0)
    {
        perror("open file");
    }

    if((fstat(fd, &sb)) == -1)
    {
        perror("stat error");
    }

    if((mmaped = (char*)mmap(NULL, 
    sb.st_size, 
    PROT_WRITE | PROT_READ, 
    MAP_SHARED, 
    fd, 
    0)) == (void*)(-1) )
    {
        perror("mmap error");
    }

    close(fd);

    printf("%s", mmaped);

    mmaped[20] = '#';
    if ((msync((void *)mmaped, sb.st_size, MS_SYNC)) == -1) {  
        perror("msync error");  
    } 

     /* 释放存储映射区 */  
    if ((munmap((void *)mmaped, sb.st_size)) == -1) {  
        perror("munmap");  
    }  

    return 0;
}