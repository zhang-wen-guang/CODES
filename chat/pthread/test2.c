/*************************************************************************
    > File Name: test2.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年05月09日 星期一 18时42分30秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int a;

int main()
{
    pid_t fpid;
    a = 0;

    fpid = fork();

    if (fpid < 0) {
        printf("error\n");
        exit(-1);
    }
    if (fpid == 0) {
        a++;
        printf("I am child, a = %d\n", a);
    } else {
        sleep(2);
        a++;
        printf("I am father, a = %d\n", a);
    }
    return 0;
}
