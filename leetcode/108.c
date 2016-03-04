#include <stdio.h>
#include <stdlib.h>

//Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
struct TreeNode* constructTree(int* nums, int start, int end) {
    int mid;
    struct TreeNode *root;

    if (NULL == nums) return NULL;
    mid = (start + end) / 2;
    root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = nums[mid];

    if (mid == end)
        root->right = NULL;
    else
        root->right = constructTree(nums, mid + 1, end);

    if (mid == start)
        root->left = NULL;
    else
        root->left = constructTree(nums, start, mid - 1);
   
    return root;
}
struct TreeNode* sortedArrayToBST(int* nums, int numsSize) {
    return constructTree(nums, 0, numsSize - 1);
}
int main()
{
    return 0;
}
