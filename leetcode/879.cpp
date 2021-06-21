#include <vector>

using namespace std;

class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1));

        for (int i = 0; i <= n; ++i) dp[i][0] = 1;

        int MOD = (int)1e9 + 7;
        for (int i = 0; i < profit.size(); ++i) {
            int members = group[i], earn = profit[i];
            for (int j = n; j >= members; --j) {
                for (int k = minProfit; k >= 0; --k) {
                    dp[j][k] = (dp[j][k] + dp[j - members][max(0, k - earn)]) % MOD;
                }
            }
        }
        return dp[n][minProfit];
    }
};