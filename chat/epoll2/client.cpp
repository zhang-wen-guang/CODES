/*************************************************************************
    > File Name: client.cpp
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年07月18日 星期一 22时33分23秒
 ************************************************************************/

/* 想了一下, client还是需要多线程实现 */
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void* send_msg(void * a_sfd) {
    int sfd = *(int*)a_sfd;
    char buf[1024];

    while (cin.getline(buf, 1024, '\n')) {
        send(sfd, buf, strlen(buf), 0);
    }
    close(sfd);
    exit(0);
}

int main(int argc, char **argv)
{
    /* 同样, 第一步弄一个socket号 */
    int sfd;
    sfd = socket(AF_INET, SOCK_STREAM, 0);

    /* 然后bind */
    struct sockaddr_in server_addr;

    /* 注意, 这里用的还是server的地址和prot */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(8765);
    inet_pton(AF_INET, argv[1], &(server_addr.sin_addr));

    /* 现在开始connect */
    connect(sfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    /* 发送名字 */
    send(sfd, argv[2], strlen(argv[2]), 0);

    /* 创建一个新的线程用于处理发送信息 */
    pthread_t pth_send;
    pthread_create(&pth_send, NULL, send_msg, &sfd);

    /* 处理收到的消息 */
    int len_recv;
    char buf[1024];
    while (len_recv = recv(sfd, buf, 1024, 0)) {
        buf[len_recv] = '\0';
        printf("%s", buf);
    }
    
    return 0;
}
