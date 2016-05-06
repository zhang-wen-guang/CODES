/*************************************************************************
    > File Name: 337.cpp
    > Author: ZWG
    > Mail: zhangwg1990@gmail.com 
    > Created Time: 六  4/ 2 23:31:07 2016
 ************************************************************************/

#include <iostream>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    int rob(TreeNode* root) {
        int* res = robSub(root);
        return max(res[0], res[1]);
    }
private:
    int* robSub(TreeNode* root) {
        int* res = new int[2];
        res[0] = res[1] = 0;

        if (NULL == root) return res;

        int* left = robSub(root->left);
        int* right = robSub(root->right);
        res[0] = root->val + left[1] + right[1];
        res[1] = max(left[0], left[1]) + max(right[0], right[1]);
        return res;
    }
};

int main()
{
    return 0;
}
