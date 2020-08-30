// LeetCode572 另一个树的子树 subtree-of-another-tree

# 给定两个非空二叉树 s 和 t，检验 s 中是否包含和 t 具有相同结构和节点值的子树。s 的一个子树包括 s 的一个节点和这个节点的所有子孙。s 也可以看
# 做它自身的一棵子树。 
# 
#  示例 1: 
# 给定的树 s: 
# 
#  
#      3
#     / \
#    4   5
#   / \
#  1   2
#  
# 
#  给定的树 t： 
# 
#  
#    4 
#   / \
#  1   2
#  
# 
#  返回 true，因为 t 与 s 的一个子树拥有相同的结构和节点值。 
# 
#  示例 2: 
# 给定的树 s： 
# 
#  
#      3
#     / \
#    4   5
#   / \
#  1   2
#     /
#    0
#  
# 
#  给定的树 t： 
# 
#  
#    4
#   / \
#  1   2
#  
# 
#  返回 false。 
#  Related Topics 树 
#  👍 313 👎 0


// pan: test header
//include "base-tree.h"

# leetcode submit region begin(Prohibit modification and deletion)
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def isSubtree(self, s: TreeNode, t: TreeNode) -> bool:
        
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