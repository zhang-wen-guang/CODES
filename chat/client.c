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

int main(int argc, char **argv)
{
    int client_socket_fd;
    struct sockaddr_in server_addr;

    /* step 1: create socket fd */
    client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8765);
    if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
    printf("inet_pton error for %s\n",argv[1]);
    exit(0);
    }

    return 0;
}
