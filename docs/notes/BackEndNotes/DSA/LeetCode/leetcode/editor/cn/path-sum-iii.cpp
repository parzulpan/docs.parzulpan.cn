// LeetCode437 路径总和 III

//给定一个二叉树，它的每个结点都存放着一个整数值。 
//
// 找出路径和等于给定数值的路径总数。 
//
// 路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。 
//
// 二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。 
//
// 示例： 
//
// root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
//
//      10
//     /  \
//    5   -3
//   / \    \
//  3   2   11
// / \   \
//3  -2   1
//
//返回 3。和等于 8 的路径有:
//
//1.  5 -> 3
//2.  5 -> 2 -> 1
//3.  -3 -> 11
// 
// Related Topics 树 
// 👍 473 👎 0

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

// 解法1：递归。LeetCode112 路径总和的基础上，分析易知，这里不在要求必须从根节点开始到叶子节点结尾。
// 所以将每个节点执行一遍递归，且递归终止条件只有当节点为空时。
class Solution {
public:

    int cnt = 0;

    int pathSum(TreeNode *root, int sum) {
        if(!root) return 0;

        // 前序遍历
        pathSumFromNode(root, sum, 0);
        pathSum(root->left, sum);
        pathSum(root->right, sum);

        return cnt;
    }

    void pathSumFromNode(TreeNode *root, int sum, int curVal) {
        if(!root) return;

        // 前序遍历
        curVal += root->val;
        if(curVal == sum) cnt++;
        pathSumFromNode(root->left, sum, curVal);
        pathSumFromNode(root->right, sum, curVal);
    }
};



//// 解法2：迭代。
//class Solution {
//public:
//    int pathSum(TreeNode* root, int sum) {
//        if(!root) return 0;
//
//        if(!root->left && !root->right) return 0;
//
//        int cnt = 0;
//        int size;
//        TreeNode* temp;
//        int tempVal;
//        vector<int> possibleVal{root->val};    // 可能值，包括当前节点值和之前节点值之和
//        queue<TreeNode*> q1;    // 保存节点
//        queue<vector<int>>q2;   // 保存可能值
//
//        q1.push(root);
//        q2.push(possibleVal);
//
//        while (!q1.empty()) {
//            size = q1.size();
//            for (int i = 0; i < size; ++i) {
//                temp = q1.front();
//                q1.pop();
//                possibleVal = q2.front();
//                q2.pop();
//
//                if(!temp->left && !temp->right) {
//                    if(temp->val == sum) cnt++;
//
//                    for(auto val: possibleVal) {
//                        if(val + temp->val == sum) cnt++;
//                    }
//                }
//
//                if(temp->left) {
//                    q1.push(temp->left);
//
//                    if(temp->left->val == sum) cnt++;
//                    vector<int> tempPossibleVal(possibleVal);
//                    tempPossibleVal.push_back(temp->left->val);
//                    for(auto val: possibleVal) {
//                        if(val + temp->left->val == sum) cnt++;
//
//                        tempPossibleVal.push_back(temp->left->val);
//                    }
//
//                    q2.push(tempPossibleVal);
//                }
//
//                if(temp->right) {
//                    ;
//                }
//            }
//        }
//
//        return cnt;
//
//    }
//};

//leetcode submit region end(Prohibit modification and deletion)

// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{10,5,-3,3,2,null,11,3,-2,null,1};
    int sum = 8;

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    int temp = solution.pathSum(root, sum);

    cout << temp;

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