// LeetCode563 二叉树的坡度 binary-tree-tilt

//给定一个二叉树，计算整个树的坡度。 
//
// 一个树的节点的坡度定义即为，该节点左子树的结点之和和右子树结点之和的差的绝对值。空结点的的坡度是0。 
//
// 整个树的坡度就是其所有节点的坡度之和。 
//
// 
//
// 示例： 
//
// 输入：
//         1
//       /   \
//      2     3
//输出：1
//解释：
//结点 2 的坡度: 0
//结点 3 的坡度: 0
//结点 1 的坡度: |2-3| = 1
//树的坡度 : 0 + 0 + 1 = 1
// 
//
// 
//
// 提示： 
//
// 
// 任何子树的结点的和不会超过 32 位整数的范围。 
// 坡度的值不会超过 32 位整数的范围。 
// 
// Related Topics 树 
// 👍 75 👎 0


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

// 解法1：递归。先求出每个节点的坡度，然后遍历树求其和。
class Solution {
public:

    int sum=0;
    int allSum=0;

    int findTilt(TreeNode* root) {
        if(!root) return 0;

        helper(root);
        allSum += sum;
        findTilt(root->left);
        findTilt(root->right);

        return allSum;
    }

    // 求每个节点的坡度，保存其左子树值之和sumL和左右树值之和sumR
    int helper(TreeNode* root) {
        if(!root) return 0;

        int sumL = helper(root->left);
        int sumR = helper(root->right);
        sum = abs(sumL - sumR);

        return root->val + sumL + sumR;
    }
};

// 解法2：递归。先求出每个节点的坡度，然后遍历树求其和。直接用allSum保存结果，简化helper函数。
class Solution1 {
public:

    int allSum=0;

    int findTilt(TreeNode* root) {
        if(!root) return 0;

        helper(root);

        return allSum;
    }

    // 求每个节点的坡度，保存其左子树值之和sumL和左右树值之和sumR
    int helper(TreeNode* root) {
        if(!root) return 0;

        int sumL = helper(root->left);
        int sumR = helper(root->right);
        allSum += abs(sumL - sumR);

        return root->val + sumL + sumR;
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{1,2,3,4,5};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution1 solution;
    int temp = solution.findTilt(root);
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