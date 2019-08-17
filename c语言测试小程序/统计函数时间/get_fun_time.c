#include <stdio.h>
#include <time.h>
#include <sys/time.h>  
#include <stdint.h>

uint64_t get_cur_time();
void test1();
void test2();

int main()
{
	test1();
	test2();
	return 0;
}

uint64_t get_cur_time()
{
	struct timeval tpstart;
	gettimeofday(&tpstart, NULL);
	return CLOCKS_PER_SEC * tpstart.tv_sec +  tpstart.tv_usec;
}

void test1()
{
	struct timeval tpstart, tpend;
    float timeuse;
 
    gettimeofday(&tpstart, NULL);
    
	// 这里是执行函数
	for(int i = 0; i < 100000; ++i)
	{
	}
	
    gettimeofday(&tpend, NULL);
    timeuse = CLOCKS_PER_SEC * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
    timeuse /= CLOCKS_PER_SEC;
	
    printf("foo1 Used Time: %f seconds\n", timeuse);
	
	timeuse = 1000 * timeuse;
	printf("foo1 Used Time: %.3f millsecond \n", timeuse);
	
}

void test2()
{
	uint64_t start_time = get_cur_time();

	// 这里是执行函数
	for(int i = 0; i < 100000; ++i)
	{
	}

	uint64_t end_time = get_cur_time();
	printf("test2 Used Time: %.3fms\n", (end_time - start_time) / 1000.0);
}