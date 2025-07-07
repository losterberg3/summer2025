/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

 #include <cstdlib>

class Solution {
public:
    int sum = 0;

    int total(TreeNode* root)
    {
        int rsum = root->right ? total(root->right) : 0;
        int lsum = root->left ? total(root->left) : 0;
        
        sum += abs(lsum - rsum);

        return lsum + rsum + root->val;
    }

    int findTilt(TreeNode* root) 
    {
        if (root)
        {
            total(root);
        }
        return sum;
    }
};