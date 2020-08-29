// LeetCode938 二叉搜索树的范围和 range-sum-of-bst

//给定二叉搜索树的根结点 root，返回 L 和 R（含）之间的所有结点的值的和。 
//
// 二叉搜索树保证具有唯一的值。 
//
// 
//
// 示例 1： 
//
// 输入：root = [10,5,15,3,7,null,18], L = 7, R = 15
//输出：32
// 
//
// 示例 2： 
//
// 输入：root = [10,5,15,3,7,13,18,1,null,6], L = 6, R = 10
//输出：23
// 
//
// 
//
// 提示： 
//
// 
// 树中的结点数量最多为 10000 个。 
// 最终的答案保证小于 2^31。 
// 
// Related Topics 树 递归 
// 👍 120 👎 0


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

// 解法1：递归。利用二叉搜索树的特性即可。
class Solution {
public:
    int ans = 0;
    int rangeSumBST(TreeNode* root, int L, int R) {

        dfs(root, L, R);
        return ans;
    }

    void dfs(TreeNode* root, int L, int R) {
        if(!root) return;

        if(root->val <= R && root->val >= L) {
            ans += root->val;
        }

        // 右子树不考虑
        if(root->val > L) {
            dfs(root->left, L, R);
        }

        // 左子树不考虑
        if(root->val < R) {
            dfs(root->right, L, R);
        }
    }
};

// 解法2：迭代。利用二叉搜索树的特性即可。
class Solution2 {
public:

    int rangeSumBST(TreeNode* root, int L, int R) {
        if(!root) return 0;

        stack<TreeNode*> s;
        s.push(root);
        TreeNode* temp;
        int ans = 0;

        while(!s.empty()) {
            temp = s.top();
            s.pop();

            if(temp->val <= R && temp->val >= L) {
                ans += temp->val;
            }

            // 右子树不考虑
            if(temp->left && temp->val > L) {
                s.push(temp->left);
            }

            // 左子树不考虑
            if(temp->right && temp->val < R) {
                s.push(temp->right);
            }

        }

        return ans;
    }

};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{10,5,15,3,7,13,18,1,null,6};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    int temp = solution.rangeSumBST(root, 6, 10);
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