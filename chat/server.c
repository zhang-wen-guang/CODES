/*************************************************************************
    > File Name: server.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 五  5/ 6 22:48:16 2016
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#define MAXLINE 1024

int main()
{
    int server_socket_fd;
    int tcp_no;
    struct sockaddr_in server_addr;
    char buf[MAXLINE];
    int msg_len;
    int bind_retval;

    /* step 1: create the socket */
    server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_fd == -1)
        printf("socket create failed\n");

    /* step 2: bind the socket to the address */
    memset(&server_addr, 0, sizeof(struct sockaddr_in));
    /*
       struct sockaddr_in {
           short   sin_family;
           u_short sin_port;
           struct  in_addr sin_addr;
           char    sin_zero[8];
       };
     */
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8765);
    bind_retval = bind(server_socket_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    if (-1 == bind_retval)
        printf("bind error\n");

    /* step 3: listen */
    listen(server_socket_fd, 10);

    /* step 4: accept */
    tcp_no = accept(server_socket_fd, (struct sockaddr*)NULL, NULL);
    if (-1 == tcp_no)
        printf("failed to accept\n");

    printf("tcp_no = %d\n", tcp_no);
    /* step 5: recieve msg */
    while ((msg_len = recv(tcp_no, buf, MAXLINE, 0)) != 0) {
        buf[msg_len] = '\0';
        printf("%s\n", buf);
    }
    
    return 0;
}
