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

int main()
{
    int server_socket_fd;
    int tcp_no;
    struct sockaddr_in server_addr;

    /* step 1: create the socket */
    server_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

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
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8765);
    bind(server_socket_fd, &server_addr, sizeof(struct sockaddr_in));

    /* step 3: listen */
    listen(server_socket_fd, 10);

    /* step 4: accept */
    tcp_no = accept(server_socket_fd, (struct sockaddr*)NULL, NULL);
    
    return 0;
}
