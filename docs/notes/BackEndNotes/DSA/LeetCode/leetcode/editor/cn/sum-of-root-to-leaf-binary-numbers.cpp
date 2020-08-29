// LeetCode1022 从根到叶的二进制数之和 sum-of-root-to-leaf-binary-numbers

//给出一棵二叉树，其上每个结点的值都是 0 或 1 。每一条从根到叶的路径都代表一个从最高有效位开始的二进制数。例如，如果路径为 0 -> 1 -> 1 ->
// 0 -> 1，那么它表示二进制数 01101，也就是 13 。 
//
// 对树上的每一片叶子，我们都要找出从根到该叶子的路径所表示的数字。 
//
// 以 10^9 + 7 为模，返回这些数字之和。 
//
// 
//
// 示例： 
//
// 
//
// 输入：[1,0,1,0,1,0,1]
//输出：22
//解释：(100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
// 
//
// 
//
// 提示： 
//
// 
// 树中的结点数介于 1 和 1000 之间。 
// node.val 为 0 或 1 。 
// 
// Related Topics 树 
// 👍 58 👎 0


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

// 解法1：递归。
class Solution {
public:
    int sum = 0;
    int sumRootToLeaf(TreeNode* root) {
        if (!root) return 0;

        helper(root, "");

        return sum;
    }

    void helper(TreeNode* root, string bString) {
        if(!root) return;

        bString += to_string(root->val);
        if(!root->left && !root->right)
            sum += bStringToDInt(bString);

        helper(root->left, bString);
        helper(root->right, bString);
    }

    // 二进制字符串转换成十进制整数
    static int bStringToDInt(const string &s) {
        int size = s.size();
        int res = 0;
        for (int i = 0; i < size; ++i) {
            res += (s.at(i) - '0') * pow(2, size - i - 1);
        }

        return res;
    }

};
//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{1,0,1,0,1,0,1};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    int temp = solution.sumRootToLeaf(root);
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