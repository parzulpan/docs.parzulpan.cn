// LeetCode501 二叉搜索树中的众数

//给定一个有相同值的二叉搜索树（BST），找出 BST 中的所有众数（出现频率最高的元素）。 
//
// 假定 BST 有如下定义： 
//
// 
// 结点左子树中所含结点的值小于等于当前结点的值 
// 结点右子树中所含结点的值大于等于当前结点的值 
// 左子树和右子树都是二叉搜索树 
// 
//
// 例如： 
//给定 BST [1,null,2,2], 
//
//    1
//    \
//     2
//    /
//   2
// 
//
// 返回[2]. 
//
// 提示：如果众数超过1个，不需考虑输出顺序 
//
// 进阶：你可以不使用额外的空间吗？（假设由递归产生的隐式调用栈的开销不被计算在内） 
// Related Topics 树 
// 👍 118 👎 0

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

// 解法1：递归。先得到中序遍历重复个数序列，然后对该序列处理。
class Solution {
public:
    map<int, int> inOrderMap;
    vector<int> res;

    vector<int> findMode(TreeNode* root) {
        if(!root) return vector<int>{};
        helper(root);
        int repeatMaxCnt = 0;
        for(auto val: inOrderMap) {
            // 重复个数等于当前重复最大值，则当前值加入结果向量
            //  重复个数小于当前重复最大值，则更新当前重复最大值，再清空结果向量后加入当前值
            if(val.second == repeatMaxCnt) {
                res.push_back(val.first);
            } else if(val.second > repeatMaxCnt) {
                repeatMaxCnt = val.second;
                res.clear();
                res.push_back(val.first);
            }
        }

        return res;

    }

    // 获得中序遍历重复个数序列
    void helper(TreeNode* root) {
        if(!root) return;
        helper(root->left);
        inOrderMap[root->val]++;
        helper(root->right);
    }

};

//leetcode submit region end(Prohibit modification and deletion)

// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{10,5,-3,3,2,null,11,3,-3,null,11,11};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    vector<int> temp = solution.findMode(root);
    for(auto t: temp)
        cout << t << " ";

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