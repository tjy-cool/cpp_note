// 获取链路层的数据包
#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/ether.h>

int main(int argc,char *argv[])
{
	unsigned char buf[1024] = {0};
	int sock_raw_fd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
 
	//获取链路层的数据包
	int len = recvfrom(sock_raw_fd, buf, sizeof(buf), 0, NULL, NULL);
	printf("len = %d\n", len);
 
	return 0;
}

// ssize_t recvfrom(  
//     int sockfd, 
//     void *buf, 
//     size_t nbytes,
//     int flags,
//     struct sockaddr *from, 
//     socklen_t *addrlen );
// sockfd:原始套接字
// buf：接收数据缓冲区
// nbytes:接收数据缓冲区的大小
// flags：套接字标志(常为0)
// from：这里没有用，写 NULL
// addrlen：这里没有用，写 NULL