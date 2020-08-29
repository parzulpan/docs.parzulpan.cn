// LeetCode559 N叉树的最大深度 maximum-depth-of-n-ary-tree

//给定一个 N 叉树，找到其最大深度。 
//
// 最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。 
//
// 例如，给定一个 3叉树 : 
//
// 
//
// 
//
// 
//
// 我们应返回其最大深度，3。 
//
// 说明: 
//
// 
// 树的深度不会超过 1000。 
// 树的节点总不会超过 5000。 
// Related Topics 树 深度优先搜索 广度优先搜索 
// 👍 97 👎 0


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

// 解法1：递归。类似于二叉树的最大深度。
class Solution {
public:
    int maxDepth(Node* root) {
        if(!root) return 0;

        if(root->children.empty()) return 1;

        // 用向量保存结果
        vector<int> tempMaxVector;
        for(auto t: root->children) {
            tempMaxVector.push_back(maxDepth(t));
        }

        // 求向量中的最大值
        return *max_element(tempMaxVector.begin(), tempMaxVector.end()) + 1;
    }
};

// 解法2：迭代。类似于二叉树的最大深度。
class Solution2 {
public:
    int maxDepth(Node* root) {
        if(!root) return 0;

        queue<Node*> q;
        q.push(root);
        Node* temp;
        int maxD = 0;

        while(!q.empty()) {
            maxD++;
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                temp = q.front();
                q.pop();

                for(auto t:temp->children) {
                    if(t) q.push(t);
                }
            }
        }

        return maxD;
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
    int temp = solution.maxDepth(root);
    cout << temp << " ";

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