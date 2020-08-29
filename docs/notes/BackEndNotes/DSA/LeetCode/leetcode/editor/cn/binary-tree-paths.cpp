// LeetCode257 二叉树的所有路径

//给定一个二叉树，返回所有从根节点到叶子节点的路径。 
//
// 说明: 叶子节点是指没有子节点的节点。 
//
// 示例: 
//
// 输入:
//
//   1
// /   \
//2     3
// \
//  5
//
//输出: ["1->2->5", "1->3"]
//
//解释: 所有根节点到叶子节点的路径为: 1->2->5, 1->3 
// Related Topics 树 深度优先搜索 
// 👍 285 👎 0

// pan: test header
#include "base-tree.h"

//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//// 解法1：递归。
//class Solution {
//public:
//    vector<string> binaryTreePaths(TreeNode* root) {
//
//        if(!root) return vector<string>{""};
//        if(!root->left && !root->right) return vector<string>{to_string(root->val)};
//
//
//    }
//};

// 解法2：迭代。
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if(!root) return vector<string>{};

        vector<string> res; // 结果向量
        queue<TreeNode* >q1;    // 保存节点
        queue<string> q2;   // 保存路径
        q1.push(root);
        q2.push(to_string(root->val));

        int size;
        TreeNode* temp;
        string s;

        while(!q1.empty()) {
            size = q1.size();
            for(int i = 0; i < size; ++i) {
                temp = q1.front();
                q1.pop();
                s = q2.front();
                q2.pop();

                // 根节点，则将路径值加入结果向量中
                if(!temp->left && !temp->right) {
                    res.push_back(s);
                }

                // 若左/右子树不为空，则节点入队列，并将路径拼接后入队列
                if(temp->left) {
                    q1.push(temp->left);
                    q2.push(s + "->" + to_string(temp->left->val));
                }

                if(temp->right) {
                    q1.push(temp->right);
                    q2.push(s + "->" + to_string(temp->right->val));
                }
            }
        }

        return res;


    }
};


//leetcode submit region end(Prohibit modification and deletion)

// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{1,2,3,null,5};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    vector<string> temp = solution.binaryTreePaths(root);

    for(auto t: temp) {
        cout << t << " ";
    }

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