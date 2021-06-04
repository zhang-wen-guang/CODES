#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int pre = 0;
        unordered_map<int, int> mp;

        mp[0] = -1;
        for (int i = 0; i < nums.size(); ++i) {
            pre += nums[i];
            int tail = pre % k;

            if (mp.find(tail) != mp.end() && i - mp[tail] > 1)
                return true;
            if (mp.find(tail) == mp.end())
                mp[tail] = i;
        }
        return false;
    }
};
