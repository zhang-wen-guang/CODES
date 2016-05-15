/*************************************************************************
    > File Name: client.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  5/ 7 14:45:26 2016
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

/* 宏定义 */
#define MAXLINE 1024

/* 全局变量 */
int client_socket_fd;
char buf[MAXLINE];

/* 自定义函数 */
void *handle_recv() {
    int msg_len;

    while ((msg_len = recv(client_socket_fd, buf, MAXLINE, 0)) != 0) {
        buf[msg_len] = '\0';
        printf("%s\n", buf);
    }
}

int main(int argc, char **argv)
{
    struct sockaddr_in server_addr;
    char s[MAXLINE];
    char buf[MAXLINE];
    int msg_len;
    //pid_t fpid;

    /* step 1: create socket fd */
    client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8765);
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr);

    /* step 2: connect to the server */
    connect(client_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    /* step 3: send msg */
    pthread_t recv_pthread; //多线程实现
    pthread_create(&recv_pthread, NULL, &handle_recv, NULL);

    while (EOF != scanf("%s", s)) {
        send(client_socket_fd, s, strlen(s), 0);
    }

    close(client_socket_fd);
    return 0;
}
