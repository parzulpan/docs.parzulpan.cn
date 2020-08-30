// LeetCode669 修剪二叉搜索树 trim-a-binary-search-tree

# 给定一个二叉搜索树，同时给定最小边界L 和最大边界 R。通过修剪二叉搜索树，使得所有节点的值在[L, R]中 (R>=L) 。你可能需要改变树的根节点，所以
# 结果应当返回修剪好的二叉搜索树的新的根节点。 
# 
#  示例 1: 
# 
#  
# 输入: 
#     1
#    / \
#   0   2
# 
#   L = 1
#   R = 2
# 
# 输出: 
#     1
#       \
#        2
#  
# 
#  示例 2: 
# 
#  
# 输入: 
#     3
#    / \
#   0   4
#    \
#     2
#    /
#   1
# 
#   L = 1
#   R = 3
# 
# 输出: 
#       3
#      / 
#    2   
#   /
#  1
#  
#  Related Topics 树 
#  👍 240 👎 0


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
    def trimBST(self, root: TreeNode, L: int, R: int) -> TreeNode:
        
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