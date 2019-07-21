# socket API

## TCP套接字编程

```c
#include <sys/socket.h>
int socket(int family, int type, int protocal);

int connect(int sockfd, const struct sockaddr* servaddr, socklen_t servaddr_len);

int bind(int sockfd, const struct sockaddr* address, socklen_t address_len);

int accept(int sockfd, struct sockaddr* cliaddr, socklen_t addrlen);

int getsockname(int sockfd, struct sockaddr* localaddr, socklen_t* addrlen);

int getpeername(int sockfd, struct sockaddr* peeraddr, socklen_t* addrlen);
```

```c
#include <unistd.h>
int close(int sockfd);
```

## UDP套接字编程

```c
#include <sys/socktd.h>
ssize_t recvfrom(int sockfdf, void* buff, size_t nbytes, int flags,
                 struct sockaddr* from, socklen_t* addrlen);

ssize_t sendto(int sockfd, const void* buff, size_t nbytes, int flags,
                const struct sockaddr* to, socklen_t addrlen);
```

- 按照 套接字地址 **传递方向**进行分类

> 进程 --> 内核： bind、connect、sendto
>
> 内核 --> 进程： accept、recvfrom、getsockname、getpeername

## 字节排序函数

```c
#include <netinet/in.h>
uint16_t htons(uint16_t host16bitvalue);

uint32_t htonl(uint32_t host32bitvalue);

uint16_t ntohs(uint16_t net16bitvalue);

uint32_t ntohs(uint32_t net32bitvalue);
```

## 字节操作函数

- 字节函数

```c
#include <string.h>
void bzero(void* dest, size_t nbytes);

void bcopy(const void* src, void* dest, size_t nbytes);

// 相等为0，否则为正或负
int bcmp(const void* ptr1, const void* ptr2, size_t nbytes);
```

- 内存函数

```c
#include <string.h>
void* memset(void* dest, int c, size_t len);

void* memcpy(void* dest, const void* src, size_t nbytes);

// 相等为0，否则为正或负
int memcmp(const void* ptr1, const void* ptr2, size_t nbytes);
```

> 记忆： dest = src;

## 跨平台函数

|  原函数  |  安全函数 |
| :-----: | :------: |
| sprintf | snprintf |
| gets    | fgets    |
| strcat  | strncat  |
| strcpy  | strncpy  |
