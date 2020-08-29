// LeetCode671 二叉树中第二小的节点 second-minimum-node-in-a-binary-tree

# 给定一个非空特殊的二叉树，每个节点都是正数，并且每个节点的子节点数量只能为 2 或 0。如果一个节点有两个子节点的话，那么该节点的值等于两个子节点中较小的一
# 个。 
# 
#  给出这样的一个二叉树，你需要输出所有节点中的第二小的值。如果第二小的值不存在的话，输出 -1 。 
# 
#  示例 1: 
# 
#  输入: 
#     2
#    / \
#   2   5
#      / \
#     5   7
# 
# 输出: 5
# 说明: 最小的值是 2 ，第二小的值是 5 。
#  
# 
#  示例 2: 
# 
#  输入: 
#     2
#    / \
#   2   2
# 
# 输出: -1
# 说明: 最小的值是 2, 但是不存在第二小的值。
#  
#  Related Topics 树 
#  👍 87 👎 0


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
    def findSecondMinimumValue(self, root: TreeNode) -> int:
        
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