/*************************************************************************
    > File Name: 216.cpp
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 2016年03月08日 星期二 17时31分08秒
 ************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        vector<int> path;
        backtrack(k, n, 1, path, ans);
        return ans;
    }
private:
    void backtrack(int k, int n, int start, vector<int> &path, vector<vector<int>> &ans) {
        if (0 == k && 0 == n) {
            ans.push_back(path);
            return;
        }
        for (int i = start; i < 11 - k && i <= n ; ++i) {
            path.push_back(i);
            backtrack(k - 1, n - i, i + 1, path, ans);
            path.pop_back();
        }
    }
};

int main() {
    return 0;
}
