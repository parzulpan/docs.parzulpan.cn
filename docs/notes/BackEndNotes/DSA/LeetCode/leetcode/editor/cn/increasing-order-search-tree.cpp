// LeetCode897 递增顺序查找树 increasing-order-search-tree

//给你一个树，请你 按中序遍历 重新排列树，使树中最左边的结点现在是树的根，并且每个结点没有左子结点，只有一个右子结点。 
//
// 
//
// 示例 ： 
//
// 输入：[5,3,6,2,4,null,8,1,null,null,null,7,9]
//
//       5
//      / \
//    3    6
//   / \    \
//  2   4    8
// /        / \ 
//1        7   9
//
//输出：[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
//
// 1
//  \
//   2
//    \
//     3
//      \
//       4
//        \
//         5
//          \
//           6
//            \
//             7
//              \
//               8
//                \
//                 9  
//
// 
//
// 提示： 
//
// 
// 给定树中的结点数介于 1 和 100 之间。 
// 每个结点都有一个从 0 到 1000 范围内的唯一整数值。 
// 
// Related Topics 树 深度优先搜索 
// 👍 81 👎 0


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

// 解法1：递归。中序遍历，然后构造新的树。
class Solution {
public:
    vector<int> inOrderVector;

    TreeNode* increasingBST(TreeNode* root) {

        inOrderTraversal(root);

        auto ans = new TreeNode(0);
        TreeNode* cur = ans;

        for(auto v: inOrderVector) {
            cur->right = new TreeNode(v);
            cur = cur->right;
        }

        return ans->right;
    }

    void inOrderTraversal(TreeNode * root) {
        if(!root) return;

        inOrderTraversal(root->left);
        inOrderVector.push_back(root->val);
        inOrderTraversal(root->right);
    }
};

// 解法2：递归。中序遍历，并更改树的连接方式。
class Solution2 {
public:
    TreeNode* cur;

    TreeNode* increasingBST(TreeNode* root) {

        auto ans = new TreeNode(0);
        cur = ans;
        inOrderTraversal(root);

        return ans->right;
    }

    void inOrderTraversal(TreeNode * root) {
        if(!root) return;

        inOrderTraversal(root->left);
        root->left = nullptr;
        cur->right = root;
        cur = root;
        inOrderTraversal(root->right);
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{5,3,6,2,4,null,8,1,null,null,null,7,9};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    TreeNode* temp = solution.increasingBST(root);
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