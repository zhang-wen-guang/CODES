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
#include <stdint.h>

#define MAXLINE 1024
#define CLIENT_COUNT 256

/* 自定义结构 */
/* client结构 */
typedef struct client{
    int tcp_no;
    char *name;
    int pos;
    pthread_t thread_no;
    struct client *pre;
    struct client *next;
    struct client *hash_pre;
    struct client *hash_next;
}client;

/*--------------------- 全局变量 ----------------------*/
int server_socket_fd;
struct client *clients[CLIENT_COUNT];
struct client *head = NULL;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/*-------------------- 自定义函数 ---------------------*/

/* hash函数, 抄自redis */
unsigned int dictGenHashFunction(const void *key, int len) {
    /* 'm' and 'r' are mixing constants generated offline.
     They're not really 'magic', they just happen to work well.  */
    uint32_t seed = 5381;
    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    /* Initialize the hash to a 'random' value */
    uint32_t h = seed ^ len;

    /* Mix 4 bytes at a time into the hash */
    const unsigned char *data = (const unsigned char *)key;

    while(len >= 4) {
        uint32_t k = *(uint32_t*)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    /* Handle the last few bytes of the input array  */
    switch(len) {
    case 3: h ^= data[2] << 16;
    case 2: h ^= data[1] << 8;
    case 1: h ^= data[0]; h *= m;
    };

    /* Do a few final mixes of the hash to ensure the last few
     * bytes are well-incorporated. */
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return (unsigned int)h;
}

/* 向所有其它client发送消息 */
void send_msg(int tcp_no, char *buf) {
    struct client* cur = head;
    while (cur) {
        if (cur->tcp_no != tcp_no) {
            pthread_mutex_lock(&lock);
            send(cur->tcp_no, buf, strlen(buf), 0);
            pthread_mutex_unlock(&lock);
        }
        cur = cur->next;
    }
}

/* 删除一个client */
void deleClient(struct client *client) {
    if (client->pre != NULL)
        client->pre->next = client->next;
    else
        head = client->next;

    if (client->next != NULL){
        client->next->pre = client->pre;
    } else {
        if (client->pre != NULL)
            client->pre->next = NULL;
        else
            head = NULL;
    }

    if (client->hash_pre != NULL) {
        client->hash_pre->hash_next = client->hash_next;
    } else {
        clients[client->pos] = client->next;
    }
    if (client->hash_next != NULL) {
        client->hash_next->hash_pre = client->hash_pre;
    } else {
        if (client->hash_pre != NULL) {
            client->hash_pre->next = NULL;
        } else {
            clients[client->pos] = NULL;
        }
    }

    close(client->tcp_no);
    free(client->name);
    free(client);
}

/* @功能实现 */
void sendSingle(char *buf, struct client* from) {
    char name[100];
    char msg[MAXLINE];
    char final_msg[MAXLINE + 100];
    int pos;
    struct client *p;

    sscanf(buf, "@%s %s", name, msg);
    sprintf(final_msg, "%s : %s\n", name, msg);
    pos = dictGenHashFunction(name, strlen(name)) % CLIENT_COUNT;
    p = clients[pos];
    while (p) {
        if (0 == strcmp(name, p->name)) {
            pthread_mutex_lock(&lock);
            send(p->tcp_no, final_msg, strlen(final_msg), 0);
            pthread_mutex_unlock(&lock);
            return;
        }
        p = p->hash_next;
    }
    char unfind[] = "没有这个用户\n";
    pthread_mutex_lock(&lock);
    send(from->tcp_no, unfind, strlen(unfind), 0);
    pthread_mutex_unlock(&lock);
}

/* 建立一个新的线程,收发消息 */
void *handleThreads(void* cl) {
    char buf[MAXLINE];
    char final_msg[MAXLINE+100];
    struct client *this_client = (client *)cl;
    int msg_len;
    int tcp_no = this_client->tcp_no;

    sprintf(buf, "欢迎%s加入聊天室\n", this_client->name);
    send_msg(tcp_no, buf);
    while ((msg_len = recv(tcp_no, buf, MAXLINE, 0)) != 0) {
        buf[msg_len] = '\0';
        if (buf[0] == '@') {
            sendSingle(buf, this_client);
            continue;
        }
        sprintf(final_msg, "%s : %s", this_client->name, buf);
        send_msg(tcp_no, final_msg);
    }
    sprintf(final_msg, "%s离开了聊天室\n", this_client->name);
    send_msg(tcp_no, final_msg);
    deleClient(this_client);
}

/* 定时检查客户端连接情况 */
void *keep_alive() {
    return NULL;
}

int main()
{
    int tcp_no;
    struct sockaddr_in server_addr;
    int msg_len;
    int bind_retval;
    struct client *cur_client;

    /* 初始化全局变量 */
    for (int i = 0; i < CLIENT_COUNT; ++i) clients[i] = NULL;

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
    unsigned int hash_value;
    char *user_name;
    while (1) {
        tcp_no = accept(server_socket_fd, (struct sockaddr*)NULL, NULL);

        /* 创建一个client结构体 */
        cur_client = (client *)malloc(sizeof(client));
        cur_client->tcp_no = tcp_no;

        /* 设置client用户名 */
        user_name = (char *)malloc(100 * sizeof(char));
        msg_len = recv(tcp_no, user_name, 100, 0);
        user_name[msg_len] = '\0';
        cur_client->name = user_name;

        /* 放入head链表 */
        cur_client->pre = NULL;
        cur_client->next = head;
        if (head != NULL) head->pre = cur_client;
        head = cur_client;

        /* 放入hash表 */
        hash_value = dictGenHashFunction(user_name, strlen(user_name));
        pos = hash_value % CLIENT_COUNT;
        cur_client->pos = pos;
        cur_client->hash_next = clients[pos];
        if (clients[pos] != NULL)
            clients[pos]->hash_pre = cur_client;
        clients[pos] = cur_client;

        pthread_create(&(cur_client->thread_no), NULL, &handleThreads, (void *)cur_client);
    }
    return 0;
}
