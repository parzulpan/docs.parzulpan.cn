#include "base.h"


BaseTree::BaseTree() {
    ;
}

void BaseTree::levelOrderTraversal(TreeNode *root) {
    if (!root) return;

    queue<TreeNode*> q;
    q.push(root);
    TreeNode* temp;
    int size;

    while (!q.empty()) {
        size = q.size();
        for (int i = 0; i < size; ++i) {
            temp = q.front();
            q.pop();

            cout << temp->val << " ";
            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }
}

void BaseTree::preOrderTraversal(TreeNode *root) {
    if(!root) return;

    cout << root->val << " ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

void BaseTree::inOrderTraversal(TreeNode *root) {
    if(!root) return;

    inOrderTraversal(root->left);
    cout << root->val << " ";
    inOrderTraversal(root->right);
}

void BaseTree::postOrderTraversal(TreeNode *root) {
    if(!root) return;

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout << root->val << " ";
}

TreeNode *BaseTree::createTreeFromLevelOrderVector(vector<int> &v, int size, int start) {
    if (v.empty() || size < start) return nullptr;

    TreeNode* root = nullptr;

    // NullNode代表空节点
    if(start < size && v[start] != null) {
        root = new TreeNode(v[start]);

        root->left = createTreeFromLevelOrderVector(v, size, 2 * start + 1);
        root->right = createTreeFromLevelOrderVector(v, size, 2 * start + 2);
    }

    return root;


}

TreeNode *BaseTree::createTreeFromLevelOrderVector(vector<int> &v) {
    if(v.empty()) return nullptr;
    ;
}