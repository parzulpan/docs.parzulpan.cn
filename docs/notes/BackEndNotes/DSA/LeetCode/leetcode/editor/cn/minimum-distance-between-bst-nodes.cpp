// LeetCode783 二叉搜索树节点最小距离 minimum-distance-between-bst-nodes

//给定一个二叉搜索树的根节点 root，返回树中任意两节点的差的最小值。 
//
// 
//
// 示例： 
//
// 输入: root = [4,2,6,1,3,null,null]
//输出: 1
//解释:
//注意，root是树节点对象(TreeNode object)，而不是数组。
//
//给定的树 [4,2,6,1,3,null,null] 可表示为下图:
//
//          4
//        /   \
//      2      6
//     / \    
//    1   3  
//
//最小的差值是 1, 它是节点1和节点2的差值, 也是节点3和节点2的差值。 
//
// 
//
// 注意： 
//
// 
// 二叉树的大小范围在 2 到 100。 
// 二叉树总是有效的，每个节点的值都是整数，且不重复。 
// 本题与 530：https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst/ 
//相同 
// 
// Related Topics 树 递归 
// 👍 65 👎 0


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

    int minDiffInBST(TreeNode* root) {
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
    int temp = solution.minDiffInBST(root);
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