/*************************************************************************
    > File Name: server.cpp
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年07月18日 星期一 22时24分47秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

int set_socket_nonblocking(int sfd) {
    int flags;

    flags = fcntl(sfd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(sfd, F_SETFL, flags);
    return 0;
}

int main()
{
    /* 生成socket fd */
    int sfd;
    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sfd) cout<<"Failed to create the socket fd" << endl;

    /* 将socket fd 与本地地址绑定 */
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(struct sockaddr_in));

    server_addr.sin_family      = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port        = htons(8765);

    int bind_val = bind(sfd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in));
    if (-1 == bind_val) cout << "Failed to bind" << endl;

    /* 绑定完了就该listen了 */
    listen(sfd, 10);

    /* 将socket fd设置为nonblocking模式 */
    set_socket_nonblocking(sfd);

    /* 开始搞epoll那一套 */
    int efd = epoll_create1(0);

    struct epoll_event event;
    struct epoll_event *events;

    /* 注册第一个事件, 就是sfd监听 */
    event.data.fd = sfd;
    event.events = EPOLLIN | EPOLLET;
    
    epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event);

    int maxsize = 100;

    calloc(100, sizeof(event));

    /* 准备工作做完了, 开始主循环 */
    int n;
    while (1) {
        n = epoll_wait(efd, events, maxsize, -1);
        /* 有n个事件响应了, 对这n个事件处理吧 */
        for (int i = 0; i < n; ++i) {
            if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!(events[i].events & EPOLLIN))) {
                cout << "epoll err" << endl;
                close(events[i].data.fd);
            }
        }
    }
    
    return 0;
}
