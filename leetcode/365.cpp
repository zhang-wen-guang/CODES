/*************************************************************************
    > File Name: 365.cpp
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  6/25 21:03:26 2016
 ************************************************************************/

#include <iostream>
using namespace std;

class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        if (0 == z) return true;
        return (z <= x + y && 0 == z % gcd(x, y));
    }
private:
    int  gcd(int a, int b) {
        if (0 == b) return a;
        return gcd(b, a % b);
    }
};

int main()
{
    return 0;
}
