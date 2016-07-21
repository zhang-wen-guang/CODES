/*************************************************************************
    > File Name: 371.c
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: Wed 06 Jul 2016 02:47:39 PM CST
 ************************************************************************/

/* c 是 a b 共有的部分, 也就是需要进位的那些位 */
/* a 是a, b不同的部分, 这些位不需要考虑进位 */
/* b = c << 1 是在进位 */
#include <stdio.h>

int getSum(int a, int b) {
    if (0 == a) return b;
    if (0 == b) return a;

    int c;
    while (0 != b) {
        c = a & b;
        a = a ^ b;
        b = c << 1;
    }
    return a;
}
