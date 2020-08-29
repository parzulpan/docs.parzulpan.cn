// LeetCode235 二叉搜索树的最近公共祖先

//给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。 
//
// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（
//一个节点也可以是它自己的祖先）。” 
//
// 例如，给定如下二叉搜索树: root = [6,2,8,0,4,7,9,null,null,3,5] 
//
// 
//
// 
//
// 示例 1: 
//
// 输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 8
//输出: 6 
//解释: 节点 2 和节点 8 的最近公共祖先是 6。
// 
//
// 示例 2: 
//
// 输入: root = [6,2,8,0,4,7,9,null,null,3,5], p = 2, q = 4
//输出: 2
//解释: 节点 2 和节点 4 的最近公共祖先是 2, 因为根据定义最近公共祖先节点可以为节点本身。 
//
// 
//
// 说明: 
//
// 
// 所有节点的值都是唯一的。 
// p、q 为不同节点且均存在于给定的二叉搜索树中。 
// 
// Related Topics 树 
// 👍 324 👎 0

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

// 解法1：递归。利用二叉搜索树的特性：左节点的值<根节点的值<右节点的值。
// 如果根节点的值大于这两个节点的最大值，说明其最近公共祖先节点在根节点的左子树。
// 如果根节点的值小于这两个节点的最小值，说明其最近公共祖先节点在根节点的右子树。
// 以此递归，当根节点的值为这两个节点的中间值，则其为最近公共祖先节点。
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;

        if(root->val > max(p->val, q->val)) {
            return lowestCommonAncestor(root->left, p, q);
        } else if (root->val < min(p->val, q->val)) {
            return lowestCommonAncestor(root->right, p, q);
        } else {
            return root;
        }

    }
};

// 解法2：迭代。由于一定会有最近公共祖先节点，所以可以一直循环寻找，找到则返回值即可。
class SolutionA {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return NULL;

        while(true) {
            if(root->val > max(p->val, q->val)) {
                root = root->left;
            } else if (root->val < min(p->val, q->val)) {
                root = root->right;
            } else {
                return root;
            }
        }

    }
};

//leetcode submit region end(Prohibit modification and deletion)

// pan: test main
int main() {
    // test case
    vector<int> levelOrderVector{6,2,8,0,4,7,9,null,null,3,5};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    TreeNode* temp = solution.lowestCommonAncestor(root, root->right, root->right->right);

    cout << temp->val <<endl;

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
 * 要充分利用题目的已知条件，二叉搜索树的特性：左节点的值<根节点的值<右节点的值
 */ 