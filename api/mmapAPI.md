# mmapp相关操作

## api介绍

```c
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);
```

### mmap返回值

成功执行时，mmap()返回被映射区的指针。
失败时，mmap()返回MAP_FAILED[其值为(void *)-1]，
error被设为以下的某个值：

### mmap参数

- addr： 映射区的开始地址， 一般为NULL。
- length: 映射区的长度。
- port: 期望的内存保护标志。

```c
#define	PROT_NONE	0x00	/* [MC2] no permissions */
#define	PROT_READ	0x01	/* [MC2] pages can be read */
#define	PROT_WRITE	0x02	/* [MC2] pages can be written */
#define	PROT_EXEC	0x04	/* [MC2] pages can be executed */
```

- flags：指定映射对象的类型, 映射选项和映射页是否可以共享.

```c
#define	MAP_SHARED	0x0001		/* [MF|SHM] share changes */
#define	MAP_PRIVATE	0x0002		/* [MF|SHM] changes are private */
```

```c
// mapping type
#define	MAP_FILE	0x0000	/* map from file (default) */
#define	MAP_ANON	0x1000	/* allocated from memory, swap space */
```

- fd: 有效的文件描述符。如果MAP_ANONYMOUS被设定，为了兼容问题，其值应为-1
- offset：被映射对象内容的起点，一般为0。

### munmap的返回值及参数

该调用在进程地址空间中解除一个映射关系。当映射关系解除后，对原来映射地址的访问将导致段错误发生。

- addr：调用mmap()时返回的地址
- len： 是映射区的大小

```c
fd=open(name, flag, mode);
if(fd<0)
　　...
ptr=mmap(NULL, len , PROT_READ|PROT_WRITE, MAP_SHARED , fd , 0); 
```
