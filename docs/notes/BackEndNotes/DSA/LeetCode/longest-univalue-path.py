// LeetCode687 最长同值路径 longest-univalue-path

# 给定一个二叉树，找到最长的路径，这个路径中的每个节点具有相同值。 这条路径可以经过也可以不经过根节点。 
# 
#  注意：两个节点之间的路径长度由它们之间的边数表示。 
# 
#  示例 1: 
# 
#  输入: 
# 
#  
#               5
#              / \
#             4   5
#            / \   \
#           1   1   5
#  
# 
#  输出: 
# 
#  
# 2
#  
# 
#  示例 2: 
# 
#  输入: 
# 
#  
#               1
#              / \
#             4   5
#            / \   \
#           4   4   5
#  
# 
#  输出: 
# 
#  
# 2
#  
# 
#  注意: 给定的二叉树不超过10000个结点。 树的高度不超过1000。 
#  Related Topics 树 递归 
#  👍 301 👎 0


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
    def longestUnivaluePath(self, root: TreeNode) -> int:
        
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