#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& cost, int target) {
        vector<string> dp(target + 1);

        for (int i = 1; i <= target; ++i) {
            for (int j = cost.size() - 1; j >= 0; --j) {
                char ad = '1' + j;
                dp[i] = max(dp[i], dp[i - cost[j]] + ad);
            }
        }
        return dp[target];
    }
};