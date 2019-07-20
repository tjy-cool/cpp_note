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
    if (sockfd == -1)
    {
        perror("socket failed");
    }

    // 2.准备地址
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    //inet_aton("127.0.0.1", &addr.sin_addr);

    // 3. socket addr 绑定
    int res = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(res == -1)
    {
        perror("bind failed");
        exit(-1);
    }
    
    // 4. 进行通信
    char buf[100] = {0};
    while(1)
    {
        struct sockaddr_in fromaddr;
        socklen_t len = sizeof(fromaddr);
        fd_set rdset;
        FD_ZERO(&rdset);
        FD_SET(sockfd, &rdset);
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 100000;
        res = select(sockfd+1, &rdset, NULL, NULL, &timeout);
        if(res == -1)
        {
            perror("select error");
            return -1;
        }
        else if(res == 0)
        {
            //printf("timeout...\n");
            continue;
        }
        else
        {
            printf("select ok\n");
            if(FD_ISSET(sockfd, &rdset))
            {
                printf("ok\n");
                recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *) &fromaddr, &len);
                printf("recv_from: %s\n", buf);

                char *str = "send from server.";
                sendto(sockfd, str, strlen(str), 0, (struct sockaddr *)&fromaddr, sizeof(fromaddr));
            }
        }
        
    }
    close(sockfd);
    return 0;
}
