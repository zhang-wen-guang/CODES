/*************************************************************************
    > File Name: test1.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年05月09日 星期一 15时36分26秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>

void *func1()
{
    printf("In thread %lu\n", pthread_self());
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, &func1, NULL);
    pthread_create(&t2, NULL, &func1, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
