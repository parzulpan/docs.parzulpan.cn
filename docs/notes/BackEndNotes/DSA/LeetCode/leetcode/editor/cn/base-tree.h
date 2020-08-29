#ifndef LEETCODE_BASE_TREE_H
#define LEETCODE_BASE_TREE_H

#endif //LEETCODE_BASE_TREE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <map>
#include <set>
#include <memory>
#include <cmath>

using namespace  std;

// 空节点
const int null = -9999;

// definition for a binary tree node.
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


// definition for a n tree node.
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


class BaseTree {
public:
    BaseTree();
    // create
    TreeNode* createTreeFromLevelOrderVector(vector<int>& v, int size, int start=0);
    TreeNode* createTreeFromLevelOrderVector(vector<int> & v);

    // traversal
    void levelOrderTraversal(TreeNode* root);
    void preOrderTraversal(TreeNode* root);
    void inOrderTraversal(TreeNode* root);
    void postOrderTraversal(TreeNode* root);

};


