/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:
    std::vector<int> sol;

    void amend(Node* root)
    {
        if (root == nullptr) return;
        sol.push_back(root->val);
        for (Node* i : root->children)
        {
            amend(i);
        }
    }

    vector<int> preorder(Node* root) {
    amend(root);
    return sol;
    }
};