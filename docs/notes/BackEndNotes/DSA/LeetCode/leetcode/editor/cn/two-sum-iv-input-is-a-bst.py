// LeetCode653 两数之和 IV - 输入 BST two-sum-iv-input-is-a-bst

# 给定一个二叉搜索树和一个目标结果，如果 BST 中存在两个元素且它们的和等于给定的目标结果，则返回 true。 
# 
#  案例 1: 
# 
#  
# 输入: 
#     5
#    / \
#   3   6
#  / \   \
# 2   4   7
# 
# Target = 9
# 
# 输出: True
#  
# 
#  
# 
#  案例 2: 
# 
#  
# 输入: 
#     5
#    / \
#   3   6
#  / \   \
# 2   4   7
# 
# Target = 28
# 
# 输出: False
#  
# 
#  
#  Related Topics 树 
#  👍 153 👎 0


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
    def findTarget(self, root: TreeNode, k: int) -> bool:
        
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