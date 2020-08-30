// LeetCode404 左叶子之和

//计算给定二叉树的所有左叶子之和。 
//
// 示例： 
//
// 
//    3
//   / \
//  9  20
//    /  \
//   15   7
//
//在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24 
//
// 
// Related Topics 树 
// 👍 162 👎 0

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

// 解法1：迭代。
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(!root) return 0;

        int sum = 0;
        int size;
        int flag;
        TreeNode* temp;
        queue<TreeNode*> q1;    // 保存节点
        queue<int> q2;  // 保存当前节点是否为父节点的左子树
        q1.push(root);
        q2.push(0);

        while (!q1.empty()) {
            size = q1.size();
            for (int i = 0; i < size; ++i) {
                temp = q1.front();
                q1.pop();
                flag = q2.front();
                q2.pop();

                // 当根节点为左子树时将节点值累加
                if(!temp->left && !temp->right) {
                    if(flag) {
                        sum += temp->val;
                    }
                }

                // 左子树存入队列，并将为左子树的标志存入队列
                if(temp->left) {
                    q1.push(temp->left);
                    q2.push(1);
                }

                // 右子树存入队列，并将不为左子树的标志存入队列
                if(temp->right) {
                    q1.push(temp->right);
                    q2.push(0);
                }

            }
        }

        return sum;

    }
};


//leetcode submit region end(Prohibit modification and deletion)

// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{3, 9, 20, null, null, 15, 7};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    int temp = solution.sumOfLeftLeaves(root);

    cout << temp;

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