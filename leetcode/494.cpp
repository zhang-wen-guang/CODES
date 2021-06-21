#include <vector>


using namespace std;

class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int n : nums) sum += n;
        if (1 == (sum - target) % 2 || sum < target) return 0;

        int reg = (sum - target) / 2;
        std::vector<int> dp(reg + 1);

        for (int &n : dp) n = 0;
        dp[0] = 1;

        for (int i = 0; i < nums.size(); ++i) {
            for (int j = reg; j >=0; --j) {
                if (nums[i] <= j) dp[j] = dp[j] + dp[j - nums[i]];
            }
        }
        return dp[reg];
    }
};
