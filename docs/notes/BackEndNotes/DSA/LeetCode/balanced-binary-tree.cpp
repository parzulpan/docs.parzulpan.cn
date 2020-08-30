// LeetCode110 平衡二叉树 balanced-binary-tree

//给定一个二叉树，判断它是否是高度平衡的二叉树。 
//
// 本题中，一棵高度平衡二叉树定义为： 
//
// 
// 一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过1。 
// 
//
// 示例 1: 
//
// 给定二叉树 [3,9,20,null,null,15,7] 
//
//     3
//   / \
//  9  20
//    /  \
//   15   7 
//
// 返回 true 。 
// 
//示例 2: 
//
// 给定二叉树 [1,2,2,3,3,null,null,4,4] 
//
//        1
//      / \
//     2   2
//    / \
//   3   3
//  / \
// 4   4
// 
//
// 返回 false 。 
//
// 
// Related Topics 树 深度优先搜索


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

// 解法1：递归。
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root)  //若为空树，平衡
            return true;
        if(abs(height(root->left) - height(root->right)) > 1)  //高度大于1，不平衡
            return false;
        return (isBalanced(root->left) && isBalanced(root->right));  //递归判断左右子树是否平衡
    }

    int height(TreeNode* root){  //递归求左右子树的最大高度
        if(!root)
            return 0;
        int left = height(root->left);
        int right = height(root->right);
        return max(left + 1,right + 1);
    }
};

//// 解法2：迭代。先得到树最小的高度，即层序遍历第一个为 左/右子树为空 或 左右子树为空 的节点所在的层数。之后将当前的高度和最小的高度比较即可。
//// 注意：这种迭代的做法是错误的！！！二叉树每个节点的左右两个子树的高度差的绝对值不超过1。注意题意！！！
//class Solution {
//public:
//    bool isBalanced(TreeNode* root) {
//        if(!root || (!root->left && !root->right)) return true;
//
//        int minHeight = 0;  // 最小的高度
//        int curHeight = 0;
//        bool findMinHeight = false; // 是否找到
//        queue<TreeNode*> q;
//        q.push(root);
//
//        while(!q.empty()) {
//            curHeight++;
//            if(minHeight < curHeight - 1) return false;
//            int size = q.size();
//            for(int i = 0; i < size; ++i) {
//                TreeNode* temp = q.front();
//                q.pop();
//
//                if(temp->left)
//                    q.push(temp->left);
//
//                if(temp->right)
//                    q.push(temp->right);
//
//                if(!findMinHeight) {
//                    if(!temp->left || !temp->right) findMinHeight = true;
//                    minHeight = curHeight;
//                }
//            }
//        }
//        return true;
//
//    }
//};

//leetcode submit region end(Prohibit modification and deletion)

// pan: test main
int main() {

    // test case: 3,9,20,null,null,15,7  1,2,2,3,3,null,null,4,4  1,2,2,3,3,3,3,4,4,4,4,4,4,null,null,5,5
    vector<int> levelOrderVector{1,2,2,3,3,3,3,4,4,4,4,4,4,null,null,5,5};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    bool temp = solution.isBalanced(root);
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