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
class Solution {
public:
    int sum = 0;
    void add(TreeNode* root) {
        if (root->left && root->left->left == nullptr && root->left->right == nullptr)
        {
            sum+=root->left->val;
        } 
        if (root->right && root->right->left == nullptr && root->right->right == nullptr)
        {
        }
        if (root->right)
        {
            add(root->right);
        }
        if (root->left)
        {
            add(root->left);
        }
    }

    int sumOfLeftLeaves(TreeNode* root)
    {
        add(root);
        return sum;
    }
};