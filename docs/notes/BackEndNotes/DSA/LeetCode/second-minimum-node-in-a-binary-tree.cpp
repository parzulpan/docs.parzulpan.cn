// LeetCode671 二叉树中第二小的节点 second-minimum-node-in-a-binary-tree

//给定一个非空特殊的二叉树，每个节点都是正数，并且每个节点的子节点数量只能为 2 或 0。如果一个节点有两个子节点的话，那么该节点的值等于两个子节点中较小的一
//个。 
//
// 给出这样的一个二叉树，你需要输出所有节点中的第二小的值。如果第二小的值不存在的话，输出 -1 。 
//
// 示例 1: 
//
// 输入: 
//    2
//   / \
//  2   5
//     / \
//    5   7
//
//输出: 5
//说明: 最小的值是 2 ，第二小的值是 5 。
// 
//
// 示例 2: 
//
// 输入: 
//    2
//   / \
//  2   2
//
//输出: -1
//说明: 最小的值是 2, 但是不存在第二小的值。
// 
// Related Topics 树 
// 👍 85 👎 0


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

// 解法1：直接遍历，得到每个节点的值，用集合保存节点值。
// 查看第二小的值，如果它存在且第一小的值等于根节点的值，说明成功，输出第二小的值。否则输出-1。
class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        if(!root) return -1;

        queue<TreeNode*> q;
        q.push(root);
        set<int> s;
        int root_val = root->val;
        TreeNode* temp;

        while(!q.empty()) {
            temp = q.front();
            q.pop();

            if(temp) s.insert(temp->val);
            if(temp->left) q.push(temp->left);
            if(temp->right) q.push(temp->right);
        }

        if(s.size() < 2 || *(s.begin()) != root_val) return -1;

        return *(++s.begin());

    }
};


//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{2,2,5,null,null,5,7};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    int temp = solution.findSecondMinimumValue(root);
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