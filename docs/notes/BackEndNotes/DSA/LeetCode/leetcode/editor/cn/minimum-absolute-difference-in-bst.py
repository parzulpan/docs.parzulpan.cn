// LeetCode530 二叉搜索树的最小绝对差 minimum-absolute-difference-in-bst

# 给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两节点的差的绝对值的最小值。 
# 
#  
# 
#  示例： 
# 
#  输入：
# 
#    1
#     \
#      3
#     /
#    2
# 
# 输出：
# 1
# 
# 解释：
# 最小绝对差为 1，其中 2 和 1 的差的绝对值为 1（或者 2 和 3）。
#  
# 
#  
# 
#  提示： 
# 
#  
#  树中至少有 2 个节点。 
#  本题与 783 https://leetcode-cn.com/problems/minimum-distance-between-bst-nodes/ 
# 相同 
#  
#  Related Topics 树 
#  👍 121 👎 0


// pan: test header
//include "base-tree.h"

# leetcode submit region begin(Prohibit modification and deletion)
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def getMinimumDifference(self, root: TreeNode) -> int:
# leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{1,2,3,4,5};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution1 solution;
    int temp = solution.findTilt(root);
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