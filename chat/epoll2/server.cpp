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
#include <arpa/inet.h>
#include <string.h>

using namespace std;

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

    int tcp_no = accept(sfd, (struct sockaddr *)NULL, NULL);
    cout << "tcp_no = " << tcp_no << endl;
    char s1[1024];
    while (recv(tcp_no, s1, 1000, 0)) {
        cout << s1 << endl;
    }

    cout<<"Hello, I am server"<<endl;
    return 0;
}
