// LeetCode617 合并二叉树 merge-two-binary-trees

//给定两个二叉树，想象当你将它们中的一个覆盖到另一个上时，两个二叉树的一些节点便会重叠。 
//
// 你需要将他们合并为一个新的二叉树。合并的规则是如果两个节点重叠，那么将他们的值相加作为节点合并后的新值，否则不为 NULL 的节点将直接作为新二叉树的节点
//。 
//
// 示例 1: 
//
// 
//输入: 
//	Tree 1                     Tree 2                  
//          1                         2                             
//         / \                       / \                            
//        3   2                     1   3                        
//       /                           \   \                      
//      5                             4   7                  
//输出: 
//合并后的树:
//	     3
//	    / \
//	   4   5
//	  / \   \ 
//	 5   4   7
// 
//
// 注意: 合并必须从两个树的根节点开始。 
// Related Topics 树 
// 👍 406 👎 0


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

// 解法1：递归。对两棵树同时进行前序遍历，并将对应的节点进行合并。遍历时，分为三种情况：
// 1. 如果两个树的当前节点均不为空，则将它们的节点值相加。
// 2. 如果其中一棵树的当前节点为空，则返回另一棵树的节点作为结果节点。
// 3. 如果两个树的当前节点均为空，则返回空

class Solution {
public:

    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        // 情况3
        if(!t1 && !t2) return nullptr;

        // 情况2
        if(!t1) return t2;
        if(!t2) return t1;

        // 情况1
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);

        return t1;

    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector1{1,3,2,5};
    vector<int> levelOrderVector2{2,1,3,null,4,null,7};

    BaseTree baseTree;

    TreeNode* root1 = baseTree.createTreeFromLevelOrderVector(levelOrderVector1, levelOrderVector1.size());
    TreeNode* root2 = baseTree.createTreeFromLevelOrderVector(levelOrderVector2, levelOrderVector2.size());
    Solution solution;
    TreeNode* temp = solution.mergeTrees(root1, root2);

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