#include <stdio.h>    
#include <unistd.h>   
#include <sys/time.h>    
#include <time.h>  /*要包含的头文件*/

void foo1()
{
    long cnt=0;
    for(long i=0; i<10000000; ++i)
    {
        cnt += 1;
    }
    printf("cnt: %ld\n", cnt);
}

void foo2()
{
    sleep(2);
}

void test1()
{
    time_t start,stop;
    start = time(NULL);
    foo1();           // 执行foo1消耗的时间
    stop = time(NULL);
    printf("foo1 Use Time:%ld\n",(stop-start));

    start = time(NULL);
    foo2();           // 执行foo1消耗的时间
    stop = time(NULL);
    printf("foo2 Use Time:%ld\n",(stop-start));
}

void test2()
{
    clock_t start, end;
    double seconds;

    start = clock();  // 记录起始时间
    foo1();           // 执行foo1消耗的时间
    end = clock();    // 记录结束时间
    seconds  =(double)(end - start)/CLOCKS_PER_SEC;
    printf("foo1 spend: %f\n", seconds);
    
    start = clock();  // 记录起始时间
    foo2();           // 执行foo2消耗的时间
    end = clock();    // 记录结束时间
    seconds  =(double)(end - start)/CLOCKS_PER_SEC;
    printf("foo2 spend: %f\n", seconds);
}

void test3()
{
    struct timeval tpstart, tpend;
    float timeuse;
 
    gettimeofday(&tpstart, NULL);
    foo1();
    gettimeofday(&tpend, NULL);
    timeuse = CLOCKS_PER_SEC * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
    timeuse /= CLOCKS_PER_SEC;
    printf("foo1 Used Time: %f seconds\n", timeuse);

    gettimeofday(&tpstart, NULL);
    foo2();
    gettimeofday(&tpend, NULL);
    timeuse = CLOCKS_PER_SEC * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
    timeuse /= CLOCKS_PER_SEC;
    printf("foo2 Used Time: %f seconds\n", timeuse);
}

int main(int argc, char *argv[])
{
    test1();
    test2();
    test3(); 
    return 0;
}

