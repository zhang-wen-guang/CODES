#include <string>
#include <stack>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int pre = 0, res = 0;
        unordered_map<int, int> mp;
        mp[0] = 1;
        for (int num : nums) {
            pre += num;
            if (mp.find(pre - k) != mp.end()) {
                res += mp[pre - k];
            }
            mp[pre]++;
        }
        return res;
    }
};