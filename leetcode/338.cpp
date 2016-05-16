/*************************************************************************
    > File Name: 338.cpp
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  4/ 2 21:05:18 2016
 ************************************************************************/

#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res(num + 1, 0);
        for (int i = 0; i <= num; ++i) {
            res[i] = res[i >> 1] + i % 2;
        }
        return res;
    }
};

int main()
{
    return 0;
}
