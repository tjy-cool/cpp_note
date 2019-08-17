#include <stdio.h>        // for printf()
#include <sys/time.h>    // for gettimeofday()
#include <unistd.h>        // for sleep(), usleep

/**
 struct timezone{
		int tz_minuteswest;  //格林威治时间往西方的时差
		int tz_dsttime;  	 //DST 时间的修正方式
	}
	
  struct timeval{
		long int tv_sec; // 秒数
		long int tv_usec; // 微秒数
	}	
 */
// usleep(time);// 百万分之一秒

int main()
{
    struct timeval start, end;
    gettimeofday( &start, NULL );
    printf("start : %ld.%d\n", start.tv_sec, start.tv_usec);
    // sleep(1);    // 单位为秒
	usleep(1000 * 1000);   // 单位为微妙，10^6us = 1s
    gettimeofday( &end, NULL );
    printf("end   : %ld.%d\n", end.tv_sec, end.tv_usec);

    return 0;
}