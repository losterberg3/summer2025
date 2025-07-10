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
    void findSeq(TreeNode* root, std::vector<int>& seq)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            seq.push_back(root->val);
            return;
        }
        if (root->left)
        {findSeq(root->left, seq);}
        if (root->right)
        {findSeq(root->right, seq);}
    }

    bool leafSimilar(TreeNode* root1, TreeNode* root2) 
    {
        std::vector<int> seq1;
        std::vector<int> seq2;
        findSeq(root1, seq1);
        findSeq(root2, seq2);
        return seq1 == seq2;
    }
};