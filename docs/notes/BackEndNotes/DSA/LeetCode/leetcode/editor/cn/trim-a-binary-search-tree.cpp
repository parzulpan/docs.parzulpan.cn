// LeetCode669 修剪二叉搜索树 trim-a-binary-search-tree

//给定一个二叉搜索树，同时给定最小边界L 和最大边界 R。通过修剪二叉搜索树，使得所有节点的值在[L, R]中 (R>=L) 。你可能需要改变树的根节点，所以
//结果应当返回修剪好的二叉搜索树的新的根节点。 
//
// 示例 1: 
//
// 
//输入: 
//    1
//   / \
//  0   2
//
//  L = 1
//  R = 2
//
//输出: 
//    1
//      \
//       2
// 
//
// 示例 2: 
//
// 
//输入: 
//    3
//   / \
//  0   4
//   \
//    2
//   /
//  1
//
//  L = 1
//  R = 3
//
//输出: 
//      3
//     / 
//   2   
//  /
// 1
// 
// Related Topics 树 
// 👍 236 👎 0


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

// 解法1：递归。前序遍历，分为以下情况：
// 1. 当前节点值小于等于L，则说明其左子树不满足条件，将其左子树置为空。
// 2. 当前节点值大于等于R，则说明其右子树不满足条件，将其右子树置为空。
// 3. 当前节点左子树不为空且左子树的节点值小于L，则说明当前节点左子树不满足条件，将当前节点左子树置为当前节点左子树的右子树。
// 4. 当前节点右子树不为空且右子树的节点值大于R，则说明当前节点右子树不满足条件，将当前节点右子树置为当前节点右子树的左子树。
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if(!root) return nullptr;

        // 情况1和2
        if(root && root->val == L) root->left = nullptr;
        if(root && root->val == R) root->right = nullptr;
        while(root) {
            // 更换根节点
            if (root->val < L) {
                root->left = nullptr;
                root = root->right;

            } else if(root->val > R) {
                root->right = nullptr;
                root = root -> left;
            } else {
                break;
            }

        }

        // 情况3
        while(root->left && root->left->val < L) {
            root->left = root->left->right;
        }

        // 情况4
        while(root->right && root->right->val > R) {
            root->right = root->right->left;
        }

        trimBST(root->left, L, R);
        trimBST(root->right,L, R);

        return root;
    }
};

//解法2：递归。更好理解，但是内存消耗比解法1高。
class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if (!root) return root;

        if(root->val > R) return trimBST(root->left, L, R);

        if(root->val < L) return trimBST(root->right, L, R);

        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);

        return root;
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{3,0,4,null,2,null,null,null,null,1};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    TreeNode* temp = solution.trimBST(root, 1, 3);
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