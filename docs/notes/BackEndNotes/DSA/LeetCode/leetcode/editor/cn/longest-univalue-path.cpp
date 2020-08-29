// LeetCode687 最长同值路径 longest-univalue-path

//给定一个二叉树，找到最长的路径，这个路径中的每个节点具有相同值。 这条路径可以经过也可以不经过根节点。 
//
// 注意：两个节点之间的路径长度由它们之间的边数表示。 
//
// 示例 1: 
//
// 输入: 
//
// 
//              5
//             / \
//            4   5
//           / \   \
//          1   1   5
// 
//
// 输出: 
//
// 
//2
// 
//
// 示例 2: 
//
// 输入: 
//
// 
//              1
//             / \
//            4   5
//           / \   \
//          4   4   5
// 
//
// 输出: 
//
// 
//2
// 
//
// 注意: 给定的二叉树不超过10000个结点。 树的高度不超过1000。 
// Related Topics 树 递归 
// 👍 301 👎 0


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

//// 解法1：迭代。直接层次遍历得到节点值，然后排序，记录最大的重复值个数repeatMaxCnt。这里一个错误做法！！因为没考虑节点的关联性。
//class Solution {
//public:
//    int longestUnivaluePath(TreeNode* root) {
//        if(!root) return 0;
//
//        queue<TreeNode*> q;
//        q.push(root);
//        TreeNode* temp;
//        int repeatCnt = 0;
//        int repeatMaxCnt = 0;
//        vector<int> v;
//
//        while(!q.empty()) {
//            temp = q.front();
//            q.pop();
//            if(temp) v.push_back(temp->val);
//            if(temp->left) q.push(temp->left);
//            if(temp->right) q.push(temp->right);
//        }
//
//        sort(v.begin(), v.end());
//        int size = v.size();
//        for(int i = 0; i < size-1; ++i) {
//            if(v[i] == v[i+1]) {
//                ++repeatCnt;
//            } else {
//                repeatCnt = 0;
//            }
//
//            if(repeatCnt > repeatMaxCnt) {
//                repeatMaxCnt = repeatCnt;
//            }
//        }
//
//        return repeatMaxCnt;
//    }
//};

// 解法2：递归。
class Solution {
public:
    int max_path = 0;

    int longestUnivaluePath(TreeNode* root) {
        if(!root) return 0;

        helper(root);
        return max_path;
    }

    int helper(TreeNode* root) {
        if(!root) return 0;

        int left = helper(root->left);
        int right = helper(root->right);

        int left_path = 0, right_path = 0;
        if(root->left && root->val == root->left->val) left_path = left_path + left;
        if(root->right && root->val == root->right->val) right_path = right_path + right;

        max_path = max(max_path, left_path + right_path);

        return max(left_path, right_path) + 1;


    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case: 5,4,5,1,1,null,5、
    vector<int> levelOrderVector{1,2,2,2,2};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    int temp = solution.longestUnivaluePath(root);
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