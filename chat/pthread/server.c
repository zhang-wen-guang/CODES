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

#define MAXLINE 1024

char buf[MAXLINE];
int server_socket_fd;
pthread_t ths[100];
int clients[100];
int count_of_clients = 0;

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

/* 建立一个新的线程 */
void *handleThreads(void* no) {
    int msg_len;
    int tcp_no = *(int *)no;

    while ((msg_len = recv(tcp_no, buf, MAXLINE, 0)) != 0) {
        buf[msg_len] = '\0';
        for (int i = 0; i < count_of_clients; ++i) {
            if (clients[i] != tcp_no) {
                send(clients[i], buf, strlen(buf), 0);
            }
        }
    }
}

int main()
{
    int tcp_no;
    struct sockaddr_in server_addr;
    int msg_len;
    int bind_retval;
    pid_t fpid;

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

    /* 将socket设置成非阻塞模式,不太行 */
    //make_socket_non_blocking(server_socket_fd);

    /* step 3: listen */
    listen(server_socket_fd, 10);


#if 0
    /* step 4: accept */

    int count_of_clients = 0;
    while (-1 != (tcp_no = accept(server_socket_fd, (struct sockaddr*)NULL, NULL))) {
        fpid = fork();
        if (fpid > 0) {
            continue;  //father
        } else {
            clients[count_of_clients++] = tcp_no;
            break;     //child
        }
    }
#endif
    
    /* step 4: accept */
    while (1) {
        printf("line 119\n");
        tcp_no = accept(server_socket_fd, (struct sockaddr*)NULL, NULL);
        printf("tcp_no = %d\n", tcp_no);
        if (tcp_no > 0) { //有来自client的连接
            clients[count_of_clients++] = tcp_no;
            pthread_create(&(ths[count_of_clients - 1]), NULL, &handleThreads, (void *)&tcp_no);
        }
    }

    return 0;
}
