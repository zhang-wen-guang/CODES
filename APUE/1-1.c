/*************************************************************************
    > File Name: 1-1.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年03月03日 星期四 17时25分55秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR           *dp;
    struct dirent *dirp;

    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; ++i)
        printf("no[%d] argv is %s\n", i, argv[i]);

    if ((dp = opendir(argv[1])) == NULL)
        printf("can not open %s\n", argv[1]);

    while ((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);

    closedir(dp);
    exit(0);
}
