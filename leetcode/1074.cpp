#include <string>
#include <stack>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
private:
    int calOneLine(vector<int>& sum, int target) {
        unordered_map<int, int> mp;
        mp[0] = 1;
        int pre = 0, count = 0;
        for (int i = 0; i < sum.size(); ++i) {
            pre += sum[i];
            if (mp.find(pre - target) != mp.end()) {
                count += mp[pre - target];
            }
            mp[pre]++;
        }
        return count;
    }
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int res = 0;

        for (int i = 0; i < m; ++i) {
            vector<int> sum(n);
            for (int j = i; j < m; ++j) {
                for (int k = 0; k < n; ++k) {
                    sum[k] += matrix[j][k];
                }
                res += calOneLine(sum, target);
            }
        }
        return res;
    }
};
