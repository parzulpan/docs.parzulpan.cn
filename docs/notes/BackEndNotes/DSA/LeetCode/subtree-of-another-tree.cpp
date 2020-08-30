// LeetCode572 另一个树的子树 subtree-of-another-tree

//给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看
//做它自身的一棵子树。 
//
// 示例 1: 
//给定的树 s: 
//
// 
//     3
//    / \
//   4   5
//  / \
// 1   2
// 
//
// 给定的树 t： 
//
// 
//   4 
//  / \
// 1   2
// 
//
// 返回 true，因为 t 与 s 的一个子树拥有相同的结构和节点值。 
//
// 示例 2: 
//给定的树 s： 
//
// 
//     3
//    / \
//   4   5
//  / \
// 1   2
//    /
//   0
// 
//
// 给定的树 t： 
//
// 
//   4
//  / \
// 1   2
// 
//
// 返回 false。 
// Related Topics 树 
// 👍 308 👎 0


// pan: test header
#include "base-tree.h"

//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// 解法1：递归，DFS暴力匹配。DFS枚举s中的每一个节点，判断这个点的子树是否和t相等。
// 判断这个点的子树是否和t相等：让两个指针一开始先指向该节点和t的根，然后进行"同步移动"两个指针来"同步遍历"这两棵树，判断对应位置是否相同。
class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        return dfs(s, t);
    }

    bool dfs(TreeNode* c, TreeNode* t) {
        if(!c) return false;
        return check(c, t) || dfs(c->left, t) || dfs(c->right, t);
    }

    bool check(TreeNode* c, TreeNode* t) {
        if(!c && !t) return true;

        // 节点均不为空，但是节点值不等
        if(!(c && t && (c->val == t->val))) return false;

        return check(c->left, t->left) && check(c->right, t->right);

    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector1{3,4,5,1,2,null,null,null,null,0};
    vector<int> levelOrderVector2{4,1,2,null,null,null,null};

    BaseTree baseTree;

    TreeNode* root1 = baseTree.createTreeFromLevelOrderVector(levelOrderVector1, levelOrderVector1.size());
    TreeNode* root2 = baseTree.createTreeFromLevelOrderVector(levelOrderVector2, levelOrderVector1.size());

    Solution solution;
    bool temp = solution.isSubtree(root1, root2);
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