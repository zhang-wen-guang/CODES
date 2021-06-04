/*************************************************************************
    > File Name: server.cpp
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年07月18日 星期一 22时24分47秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <map>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define MAX_MESSAGE  2048
#define MAX_NAME     100

using namespace std;

int set_socket_nonblocking(int sfd) {
    int flags;

    flags = fcntl(sfd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(sfd, F_SETFL, flags);
    return 0;
}

bool is_blank(char *s) {
    for (int i = 0; i < strlen(s); ++i) {
        if (!isspace(s[i]) && '\n' != s[i]) return false;
    }
    return true;
}

void pack_message_and_send(int sfd, map<int, string> clients2, char *buf) {
    char message[MAX_MESSAGE] = "";

    strcat(message, clients2[sfd].c_str());
    strcat(message, " : ");
    strcat(message, buf);
    strcat(message, "\n");
    for (auto pair : clients2) {
        if (pair.first != sfd)
            send(pair.first, message, strlen(message), 0);
    }
}

void welcome(string name, map<int, string> clients2) {
    char message[MAX_MESSAGE] = "";
    strcat(message, "系统提示 : ");
    strcat(message, name.c_str());
    strcat(message, "加入了聊天室\n");
    for (auto pair : clients2) {
        send(pair.first, message, strlen(message), 0);
    }
}

void quit(int sfd, map<string, int> &clients, map<int, string> &clients2) {
    int to_sfd;
    string name = clients2[sfd];
    char message[MAX_MESSAGE] = "";

    /* 从两个map中删除这个client */
    clients.erase(name);
    clients2.erase(sfd);

    /* 制作message */
    strcat(message, "系统提示 : ");
    strcat(message, name.c_str());
    strcat(message, "离开了聊天室\n");

    for (auto pair : clients2) {
        send(pair.first, message, strlen(message), 0);
    }
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
    server_addr.sin_port        = htons(8765);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

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

    events = (struct epoll_event*)calloc(100, sizeof(event));

    /* 准备工作做完了, 开始主循环 */
    int n;
    map<string, int> clients;
    map<int, string> clients2;
    string client_name;
    char buf[MAX_MESSAGE];
    int count;
    while (1) {
        n = epoll_wait(efd, events, maxsize, -1);
        /* 有n个事件响应了, 对这n个事件处理吧 */
        for (int i = 0; i < n; ++i) {
            /* 第一种情况, 这个事件挂掉了 */
            if ((events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!(events[i].events & EPOLLIN))) {
                cout << "name = " <<  clients2[events[i].data.fd] << endl;
                close(events[i].data.fd);
            } else if (events[i].data.fd == sfd) {
                /* 当event.data.fd=sfd时 */
                /* 我理解, 这里需要做2件事, 1, accept. 2, 注册新的事件 */
                int infd;
                infd = accept(sfd, (struct sockaddr *)NULL, NULL);

                /* 拿到client的名字 */
                count = recv(infd, buf, MAX_MESSAGE, 0);
                buf[count] = '\0';
                client_name = buf;

                /* 发送欢迎信息, 注意不能放到后面 */
                welcome(client_name, clients2);
                
                /* 将这个新的client放到clients中去 */
                clients[client_name] = infd;
                clients2[infd] = client_name;
                /* TODO : 重名问题后面解决 */

                /* 注册事件 */
                set_socket_nonblocking(infd);
                event.data.fd = infd;
                event.events = EPOLLIN | EPOLLET;
                epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
            } else {
                /* 收到消息, 打印消息就行了 */
                int recv_sfd = events[i].data.fd;
                count = read(recv_sfd, buf, MAX_MESSAGE);
                buf[count] = '\0';
                if (0 == count) {
                    quit(recv_sfd, clients, clients2);
                }
                if (is_blank(buf)) continue;
                pack_message_and_send(recv_sfd, clients2, buf);
            }
        }
    }
    free(events);
    close(sfd);
    return 0;
}
