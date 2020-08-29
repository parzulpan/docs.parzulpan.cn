// LeetCode111 二叉树的最小深度

//给定一个二叉树，找出其最小深度。 
//
// 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。 
//
// 说明: 叶子节点是指没有子节点的节点。 
//
// 示例: 
//
// 给定二叉树 [3,9,20,null,null,15,7], 
//
//     3
//   / \
//  9  20
//    /  \
//   15   7 
//
// 返回它的最小深度 2. 
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

// 解法1：递归。最小深度问题就是就最短路径的节点个数，直接DFS即可。
class Solution {
public:
    int minDepth(TreeNode *root) {
        if (!root)
            return 0;
        if (!root->left && !root->right)
            return 1;

        if (!root->left) //若左子树为空，则返回右子树的深度，反之返回左子树的深度
            return minDepth(root->right) + 1;
        else if (!root->right)
            return minDepth(root->left) + 1;
        else    //如果都不为空，则返回左子树和右子树深度的最小值
            return 1 + min(minDepth(root->left), minDepth(root->right));
    }
};

// 解法2：迭代。层序遍历，遇到叶子节点时则返回当前层数。
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;

        queue<TreeNode*> q;
        int minHeight = 0;
        q.push(root);
        while(!q.empty()) {
            minHeight++;
            int size = q.size();
            for(int i = 0; i < size; ++i) {
                TreeNode* temp = q.front();
                q.pop();

                if(!temp->left && !temp->right) return minHeight;
                if(temp->left) q.push(temp->left);
                if(temp->right) q.push(temp->right);
            }
        }
        return minHeight;
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