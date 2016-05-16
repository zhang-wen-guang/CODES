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
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024

/* 自定义结构 */
typedef struct client{
    int status;
    int tcp_no;
    pthread_t thread_no;
}client;

/*--------------------- 全局变量 ----------------------*/
int server_socket_fd;
int max_client = 0;
int client_status[100];
int freed_clients = 0;
client *clients[100];

/*-------------------- 自定义函数 ---------------------*/
/* 没用到的函数, 用于设置socket为非阻塞模式 */
static int make_socket_non_blocking (int sfd)  
{  
  int flags, s;  
  
  //得到文件状态标志  
  flags = fcntl (sfd, F_GETFL, 0);  
  if (flags == -1)  
    {   
      perror ("fcntl");  
      return -1;  
    }   
  
  //设置文件状态标志  
  flags |= O_NONBLOCK;  
  s = fcntl (sfd, F_SETFL, flags);  
  if (s == -1)  
    {   
      perror ("fcntl");  
      return -1;  
    }   
  
  return 0;  
}  

/* 向所有其它client发送消息 */
void send_msg(int tcp_no, char *buf) {
    for (int i = 0; i < max_client; ++i) {
        if (clients[i]->status && clients[i]->tcp_no != tcp_no) {
            send(clients[i]->tcp_no, buf, strlen(buf), 0);
        }
    }
}

/* 建立一个新的线程,收发消息 */
void *handleThreads(void* cl) {
    char buf[MAXLINE];
    char final_msg[MAXLINE+100];
    client *this_client = (client *)cl;
    int msg_len;
    int tcp_no = this_client->tcp_no;
    char user_name[100];

    msg_len = recv(tcp_no, user_name, 100, 0);
    user_name[msg_len] = '\0';

    sprintf(buf, "欢迎%s加入聊天室", user_name);
    send_msg(tcp_no, buf);
    while ((msg_len = recv(tcp_no, buf, MAXLINE, 0)) != 0) {
        buf[msg_len] = '\0';
        sprintf(final_msg, "%s : %s", user_name, buf);
        send_msg(tcp_no, final_msg);
    }
    sprintf(final_msg, "%s离开了聊天室");
    send_msg(tcp_no, final_msg);
    this_client->status = 0;
}

/* 定时检查客户端连接情况 */
void *keep_alive() {
    int i = 0;
    while (1) {
        for (i = 0; i < max_client; ++i) {
        }
    }
    return NULL;
}

int main()
{
    int tcp_no;
    struct sockaddr_in server_addr;
    int msg_len;
    int bind_retval;

    /* 初始化全局变量 */
    for (int i = 0; i < 100; ++i) client_status[i] = 0;

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
    int pos;
    while (1) {
        tcp_no = accept(server_socket_fd, (struct sockaddr*)NULL, NULL);

        if (freed_clients) {  //前面有空余的位置
            for (int i = 0; i < max_client; ++i) {
                if (clients[i]->status = 0) {
                    pos = i;
                    break;
                }
            }
            freed_clients--;
        } else {
            pos = max_client++;
        }
        clients[pos] = (client *)malloc(sizeof(client));
        clients[pos]->status = 1;
        clients[pos]->tcp_no = tcp_no;
        pthread_create(&(clients[pos]->thread_no), NULL, &handleThreads, (void *)clients[pos]);
    }

    return 0;
}
