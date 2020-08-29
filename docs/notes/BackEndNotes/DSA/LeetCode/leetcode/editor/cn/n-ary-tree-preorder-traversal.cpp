// LeetCode589 N叉树的前序遍历 n-ary-tree-preorder-traversal

//给定一个 N 叉树，返回其节点值的前序遍历。 
//
// 例如，给定一个 3叉树 : 
//
// 
//
// 
//
// 
//
// 返回其前序遍历: [1,3,5,6,2,4]。 
//
// 
//
// 说明: 递归法很简单，你可以使用迭代法完成此题吗? Related Topics 树 
// 👍 86 👎 0


// pan: test header
#include "base-tree.h"

//leetcode submit region begin(Prohibit modification and deletion)
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

// 解法1：递归。类似于二叉树的前序遍历。
class Solution {
public:
    vector<int> res;
    vector<int> preorder(Node* root) {
        if(!root) return vector<int>();

        res.push_back(root->val);
        for(auto t:root->children) {
            preorder(t);
        }

        return res;
    }
};

// 解法2：迭代。用栈保存。
class Solution2 {
public:
    vector<int> res;
    vector<int> preorder(Node* root) {
        if(!root) return res;

        stack<Node*> s;
        s.push(root);
        Node* temp;
        while(!s.empty()) {
            temp = s.top();
            s.pop();
            res.push_back(temp->val);
            int size = temp->children.size();
            // 这里需注意顺序，栈的特性，所以要倒着入栈，才能顺着出栈
            for(int i = size - 1; i >= 0; --i) {
                if(temp->children[i]) s.push(temp->children[i]);
            }
        }

        return res;
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{1,2,3,4,5};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    vector<int> temp = solution.preorder(root);
    for(auto t: temp)
        cout << t << " ";

    return 0;
}

/** 
 * KnowledgePoint:
 * 
 * T(n) = 
 * 
 * O(n) = 
 * 
 * Summary: 
 */ 