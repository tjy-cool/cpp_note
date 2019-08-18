#include <sys/mman.h>   // mmap munmap
#include <sys/types.h>  
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// 运行 ./mmap_file_copy aa.txt
int main(int argc, char* argv[])
{
    int fd;
    int flength = 1024;
    char* mmaped_mem, *p;
    void* start_addr = 0;

    if(argc < 2)
    {
        printf("args must be two, input filename\n");
        return -1;
    }

    fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    flength = lseek(fd, -1, SEEK_END);
    printf("flength: %d", flength);
    write(fd, "\0", 1);
    lseek(fd, 0, SEEK_SET);
    mmaped_mem = mmap(NULL, flength, PROT_READ, MAP_PRIVATE, fd, 0);
    printf("%s\n", mmaped_mem);
    munmap(mmaped_mem, flength);
    return 0;
}