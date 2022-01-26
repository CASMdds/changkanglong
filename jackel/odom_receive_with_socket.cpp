
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sstream>
#include <pthread.h>
#include <errno.h>
#include <iomanip>

struct UdpPosePack {
    char head[2];
    double x;
    double y;
    double z;
    float qx;
    float qy;
    float qz;
    float qw;
};

struct UdpPosePack udpPack;

int main(int argc, char **argv)
{
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock_fd >= 0);

    struct sockaddr_in addr_serv, addr_client;
    int len;
    memset(&addr_serv, 0, sizeof(struct sockaddr_in)); 
    addr_serv.sin_family = AF_INET; 
    addr_serv.sin_port = htons(atoi(argv[1]));
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);
    len = sizeof(addr_serv);

    if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0)
    {
        perror("bind error:");
        exit(1);
    }


    int recv_num;
    char recv_buf[100];

    while(1)
    {
        printf("server wait:\n");

        recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&addr_client, (socklen_t *)&len);

        if(recv_num < 0)
        {
            perror("recvfrom error:");
            exit(1);
        }
        if(int(recv_buf[0])==int(0x55) && int(recv_buf[1])==int(0x33))
        {
            memcpy(&udpPack, recv_buf, sizeof(UdpPosePack));
            
            std::cout << std::setprecision(12) << udpPack.x << " " << udpPack.y << " " << udpPack.z << " " << udpPack.qx << " " << udpPack.qy << " " << udpPack.qz << " " << udpPack.qw << std::endl;
        }

    }

    close(sock_fd);

    return 0;
}


