#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>

int get_mtu(const char *nic) {
    int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    strncpy(ifr.ifr_name, nic, IFNAMSIZ-1);   // eth0
    if (ioctl(fd, SIOCGIFMTU, &ifr)) {
        perror("ioctl");
        return -1;
    }
    close(fd);
    return ifr.ifr_mtu;
}

int main(int argc, const char * argv[]) {

    int mtu = get_mtu("eth0");
    printf("%d\n", mtu);
    
    return 0;
}
