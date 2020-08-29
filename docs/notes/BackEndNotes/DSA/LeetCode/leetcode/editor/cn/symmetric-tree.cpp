// LeetCode101 对称二叉树

//给定一个二叉树，检查它是否是镜像对称的。 
//
// 
//
// 例如，二叉树 [1,2,2,3,4,4,3] 是对称的。 
//
//     1
//   / \
//  2   2
// / \ / \
//3  4 4  3
// 
//
// 
//
// 但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的: 
//
//     1
//   / \
//  2   2
//   \   \
//   3    3
// 
//
// 
//
// 进阶： 
//
// 你可以运用递归和迭代两种方法解决这个问题吗？ 
// Related Topics 树 深度优先搜索 广度优先搜索


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
    bool isSymmetric(TreeNode* root) {
        return isMirror(root, root);
    }

    bool isMirror(TreeNode* p, TreeNode* q) {
        // 均为空
        if(!p && !q) return true;

        // 其中有一个不为空，或者节点的值不等
        if((!p || !q) || (p->val != q->val)) return false;

        // 联想镜像对称，左对应右
        return isMirror(p->left, q->right) && isMirror(p->right, q->left);
    }
};


// 解法2：迭代
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;

        // 将节点的左右子节点存入队列中
        queue<TreeNode*> q1, q2;
        q1.push(root->left);
        q2.push(root->right);

        while(!q1.empty() && !q2.empty()) {
            // 取出节点
            TreeNode* n1 = q1.front();
            q1.pop();
            TreeNode* n2 = q2.front();
            q2.pop();

            // 均为空则不处理
            if(!n1 && !n2) continue;

            // 其中有一个不为空，或者均不为空但节点的值不等
            if((!n1 || !n2) || (n1->val != n2->val)) return false;

            // 联想镜像对称，左对应右，加入队列
            q1.push(n1->left);
            q1.push(n1->right);
            q2.push(n2->right);
            q2.push(n2->left);
        }

        // 处理完返回true
        return true;
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