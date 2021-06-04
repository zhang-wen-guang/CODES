#include <vector>

using namespace std;

class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        vector<long long> preSum;
        long long pre = 0;
        for (int num : candiesCount) {
            preSum.push_back(pre);
            pre += num;
        }
        preSum.push_back(pre);

        vector<bool> res;

        for (vector<int>& query : queries) {
            int candyMin = query[1] + 1;
            long long candyMax = (long long)candyMin * query[2];

            if (candyMax <= preSum[query[0]] || candyMin > preSum[query[0] + 1])
                res.push_back(false);
            else
                res.push_back(true);
        }
        return res;
    }
};