#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (auto &vc : dp)
            for (int &n : vc)
                n = 0;

        for (int i = 0; i < strs.size(); ++i) {
            int zeros = 0, ones = 0;
            for (char c : strs[i])
                if (c == '0')
                    zeros++;
                else
                    ones++;
            for (int j = m; j >= 0; --j)
                for (int k = n; k >= 0; --k)
                    if (j >= zeros && k >= ones)
                        dp[j][k] = max(dp[j][k], dp[j - zeros][k - ones] + 1);
        }
        return dp[m][n];
    }
};
