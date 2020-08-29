// LeetCode104 二叉树的最大深度

//给定一个二叉树，找出其最大深度。 
//
// 二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。 
//
// 说明: 叶子节点是指没有子节点的节点。 
//
// 示例： 
//给定二叉树 [3,9,20,null,null,15,7]， 
//
//     3
//   / \
//  9  20
//    /  \
//   15   7 
//
// 返回它的最大深度 3 。 
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
    int maxDepth(TreeNode* root) {
        TreeNode* p = root;
        if(!p) return 0;

        return max(maxDepth(p->left)+1, maxDepth(p->right)+1);
    }
};


// 解法2：迭代。层序遍历二叉树，总层数即为最大深度
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        int res = 0;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            // 遍历一层值加1
            res++;
            int size = q.size();
            // 遍历每一层
            for(int i = 0; i < size; ++i) {
                TreeNode* p = q.front();
                q.pop();
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
        }
        return res;
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