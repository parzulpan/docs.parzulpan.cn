// LeetCode112 路径总和

//给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。 
//
// 说明: 叶子节点是指没有子节点的节点。 
//
// 示例: 
//给定如下二叉树，以及目标和 sum = 22， 
//
//               5
//             / \
//            4   8
//           /   / \
//          11  13  4
//         /  \      \
//        7    2      1
// 
//
// 返回 true, 因为存在目标和为 22 的根节点到叶子节点的路径 5->4->11->2。 
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

// 解法1：递归。前序遍历。
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        if(!root->left && !root->right && sum == root->val) return true;

        return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
    }
};

// 解法2：迭代。利用层序遍历，使用两个队列，一个队列保存节点，一个队列保存遍历过节点的总和。
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;

        queue<TreeNode*> q1;
        queue<int> q2;
        q1.push(root);
        q2.push(root->val);

        while(!q1.empty()) {
            int size = q1.size();
            for(int i = 0; i < size; ++i) {
                TreeNode* temp = q1.front();
                q1.pop();
                int val = q2.front();
                q2.pop();

                if(!temp->left && !temp->right && sum == val) return true;

                if(temp->left) {
                    q1.push(temp->left);
                    q2.push(val + temp->left->val);
                }

                if(temp->right) {
                    q1.push(temp->right);
                    q2.push(val + temp->right->val);
                }
            }
        }
        return false;
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