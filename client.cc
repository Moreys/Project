#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void do_service(int sockfd);

int main(int argc, const char *argv[])
{
    int peerfd = socket(PF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
  //  addr.sin_addr.s_addr = inet_addr("47.106.165.214"); //localhost
    addr.sin_addr.s_addr = inet_addr("172.17.42.252"); //localhost
    //addr.sin_addr.s_addr = INADDR_ANY; //localhost
   // 172.17.42.252
    addr.sin_port = htons(8989);
    socklen_t len = sizeof addr;
    if(connect(peerfd, (struct sockaddr*)&addr, len) == -1)
        ERR_EXIT("Connect");

	//char buf[1024 * 1024];
	//memset(buf, 0, sizeof(buf));
	//read(peerfd, buf, sizeof(buf));
	//printf("%s\n", buf);

    do_service(peerfd);
    return 0;
}



void do_service(int sockfd)
{
    char recvbuf[1024 * 1024 * 1] = {0};
    char sendbuf[1024] = {0};
    while(1)
    {
        fgets(sendbuf, sizeof sendbuf, stdin);
        cout << "发送：" << sendbuf;
        write(sockfd, sendbuf, strlen(sendbuf));

        //read
        //
        int length = 0;

        int nread = read(sockfd, recvbuf, sizeof(length));
        printf("nread = %d\n", nread);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("read");
        }
        else if(nread == 0) //代表链接断开
        {
            printf("server close!\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }
        printf("收到的消息大小 : %d\n", length);
        nread = read(sockfd, recvbuf, length);
        printf("收到的消息内容为: %s\n", recvbuf);
        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
    }
}




