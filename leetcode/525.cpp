#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> mp;
        int pre = 0, max = 0;

        mp[0] = -1;
        for (int i = 0; i < nums.size(); ++i) {
            pre += (nums[i] ? 1 : -1);

            if (mp.find(pre) != mp.end() && i - mp[pre] > max)
                max = i - mp[pre];
            if (mp.find(pre) == mp.end())
                mp[pre] = i;
        }
        return max;
    }
};