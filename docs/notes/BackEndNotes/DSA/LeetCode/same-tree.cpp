// LeetCode100 相同的树

//给定两个二叉树，编写一个函数来检验它们是否相同。 
//
// 如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。 
//
// 示例 1: 
//
// 输入:       1         1
//          / \       / \
//         2   3     2   3
//
//        [1,2,3],   [1,2,3]
//
//输出: true 
//
// 示例 2: 
//
// 输入:      1          1
//          /           \
//         2             2
//
//        [1,2],     [1,null,2]
//
//输出: false
// 
//
// 示例 3: 
//
// 输入:       1         1
//          / \       / \
//         2   1     1   2
//
//        [1,2,1],   [1,1,2]
//
//输出: false
// 
// Related Topics 树 深度优先搜索


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

// 解法1：递归
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // 都为null
        if(p == NULL && q == NULL) return true;
        // 只有一个为null
        if(p == NULL || q == NULL) return false;
        if(p->val != q->val) return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};


// 解法2：迭代
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // 将节点存在栈中
        stack<TreeNode*> s1, s2;
        if(p) s1.push(p);
        if(q) s2.push(q);

        while(!s1.empty() && !s2.empty()) {
            // 取出节点
            TreeNode *t1 = s1.top();
            s1.pop();
            TreeNode *t2 = s2.top();
            s2.pop();

            // 节点值不等
            if(t1->val != t2->val) return false;

            // 左子树节点个数不等
            if(t1->left) s1.push(t1->left);
            if(t2->left) s2.push(t2->left);
            if(s1.size() != s2.size()) return false;

            // 右子树节点个数不等
            if(t1->right) s1.push(t1->right);
            if(t2->right) s2.push(t2->right);
            if(s1.size() != s2.size()) return false;
        }

        // 处理一开始就有节点为空的情况
        return s1.size() == s2.size();

    }
};

//leetcode submit region end(Prohibit modification and deletion)


/**
 * KnowledgePoint:
 *
 * T(n) =
 *
 * O(n) =
 *
 * Summary:
 */