#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // strlen
#include <unistd.h>
#include <sys/socket.h> // socket
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h>  // inet_aton
#define PORT    8888

int main()
{
    // 1. 创建socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1)
    {
        perror("socket failed");
        exit(-1);
    }
    // 2. 准备地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_aton("127.0.0.1", &addr.sin_addr);

    // 3. 进行通讯
    char* str = "Hello";
    // 发送数据
    sendto(sockfd, str, strlen(str), 0, (struct sockaddr*)&addr, sizeof(addr));
    // 接收数据
    char buf[100] = {0};
    socklen_t len = 0;
    recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&addr, &len);
    printf("recv from server：%s\n", buf);

    // 关闭socket
    close(sockfd);
    return 0;
}