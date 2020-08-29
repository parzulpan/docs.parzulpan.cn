// LeetCode530 二叉搜索树的最小绝对差 minimum-absolute-difference-in-bst

//给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两节点的差的绝对值的最小值。 
//
// 
//
// 示例： 
//
// 输入：
//
//   1
//    \
//     3
//    /
//   2
//
//输出：
//1
//
//解释：
//最小绝对差为 1，其中 2 和 1 的差的绝对值为 1（或者 2 和 3）。
// 
//
// 
//
// 提示： 
//
// 
// 树中至少有 2 个节点。 
// 本题与 783 https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes/ 
//相同 
// 
// Related Topics 树 
// 👍 116 👎 0

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

// 解法1：递归。常规题。
class Solution {
public:
    vector<int> inOrderVector;
    int size;
    int absMinVal = INT_MAX;
    int absCurVal;

    int getMinimumDifference(TreeNode* root) {
        if(!root) return 0;

        helper(root);

        size = inOrderVector.size();
        for(int i = 0; i < size - 1; ++i) {
            absCurVal = abs(inOrderVector[i] - inOrderVector[i+1]);
            if(absCurVal < absMinVal)
                absMinVal = absCurVal;
        }

        return absMinVal;
    }

    void helper(TreeNode* root) {
        if(!root) return;

        helper(root->left);
        inOrderVector.push_back(root->val);
        helper(root->right);

    }

};


//leetcode submit region end(Prohibit modification and deletion)

// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{1,null,3,null,null,2};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    int temp = solution.getMinimumDifference(root);
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