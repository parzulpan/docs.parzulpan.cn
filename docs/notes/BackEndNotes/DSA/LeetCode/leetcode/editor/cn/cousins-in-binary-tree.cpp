// LeetCode993 二叉树的堂兄弟节点 cousins-in-binary-tree

//在二叉树中，根节点位于深度 0 处，每个深度为 k 的节点的子节点位于深度 k+1 处。 
//
// 如果二叉树的两个节点深度相同，但父节点不同，则它们是一对堂兄弟节点。 
//
// 我们给出了具有唯一值的二叉树的根节点 root，以及树中两个不同节点的值 x 和 y。 
//
// 只有与值 x 和 y 对应的节点是堂兄弟节点时，才返回 true。否则，返回 false。 
//
// 
//
// 示例 1： 
// 
//
// 输入：root = [1,2,3,4], x = 4, y = 3
//输出：false
// 
//
// 示例 2： 
// 
//
// 输入：root = [1,2,3,null,4,null,5], x = 5, y = 4
//输出：true
// 
//
// 示例 3： 
//
// 
//
// 输入：root = [1,2,3,null,4], x = 2, y = 3
//输出：false 
//
// 
//
// 提示： 
//
// 
// 二叉树的节点数介于 2 到 100 之间。 
// 每个节点的值都是唯一的、范围为 1 到 100 的整数。 
// 
//
// 
// Related Topics 树 广度优先搜索 
// 👍 76 👎 0


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

// 解法1：由题意，如果二叉树的两个节点深度相同，但父节点不同，则它们是一对堂兄弟节点。层序遍历，每一层的节点且其父节点不同即满足题意。
class Solution {
public:
    bool isCousins(TreeNode* root, int x, int y) {
        if(!root) return false;

        queue<TreeNode*> q;    // 保存节点
        q.push(root);
        vector<TreeNode*> v; // 保存父节点
        TreeNode* temp;
        int size = 0;

        while(!q.empty()) {
            size = q.size();

            for (int i = 0; i < size; ++i) {
                temp = q.front();
                q.pop();

                if(temp->left) {
                    q.push(temp->left);
                    if (temp->left->val == x or temp->left->val == y)
                        v.push_back(temp);
                }
                if(temp->right) {
                    q.push(temp->right);
                    if (temp->right->val == x or temp->right->val == y)
                        v.push_back(temp);
                }
            }

            if(v.size() == 2 && v[0] != v[1])
                return true;
            else
                v.clear();
        }

        return false;
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{1,2,3,null,4,null,5};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    bool temp = solution.isCousins(root, 5, 4);
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