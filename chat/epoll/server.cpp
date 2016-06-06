/*************************************************************************
    > File Name: server.cpp
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: Sun Jun  5 21:45:08 2016
 ************************************************************************/

#include <iostream>
#include <sys/socket.h>

int create_socket(int port) {
    int server_socket;

    /* 创建server端socket号 */
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == server_socket) {
        std::cout<<"Failed to create server socket"<<std::end;
        exit(1);
    }

    /* 绑定server端socket与server的地址 */
    struct sockaddr_in server_addr;
    memset(&server_addr, sizeof(server_addr), 0);
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
    server_addr.sin_port = htons(port);

    int bind_retval;
    bind_retval = bind(server_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    if (-1 == bind_retval) {
        std::cout<<"Failed to bind()" <<std::endl;
    }
}

int main()
{
    int server_socket;


    std::cout<<"Hello"<<std::endl;
    return 0;
}
