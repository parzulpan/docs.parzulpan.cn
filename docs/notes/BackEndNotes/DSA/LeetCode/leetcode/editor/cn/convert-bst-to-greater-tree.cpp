// LeetCode538 把二叉搜索树转换为累加树 convert-bst-to-greater-tree

//给定一个二叉搜索树（Binary Search Tree），把它转换成为累加树（Greater Tree)，使得每个节点的值是原来的节点值加上所有大于它的节
//点值之和。 
//
// 
//
// 例如： 
//
// 输入: 原始二叉搜索树:
//              5
//            /   \
//           2     13
//
//输出: 转换为累加树:
//             18
//            /   \
//          20     13
// 
//
// 
//
// 注意：本题和 1038: https://leetcode-cn.com/problems/binary-search-tree-to-greater-s
//um-tree/ 相同 
// Related Topics 树 
// 👍 275 👎 0


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

// 解法1：递归。注意到中序遍历为递增序列，那么将中序遍历变型即能得到递减序列，那么除第一个值(此时为最大值)，其余值累加即可。
class Solution {
public:

    int val = 0;

    TreeNode* convertBST(TreeNode* root) {
        if(!root) return root;

        // 中序遍历变型版
        convertBST(root->right);
        val = root->val + val;
        root->val = val;
        convertBST(root->left);

        return root;
    }

};


//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{5,2,13};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    TreeNode* temp = solution.convertBST(root);
    baseTree.levelOrderTraversal(temp);

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