// LeetCode783 二叉搜索树节点最小距离 minimum-distance-between-bst-nodes

# 给定一个二叉搜索树的根节点 root，返回树中任意两节点的差的最小值。 
# 
#  
# 
#  示例： 
# 
#  输入: root = [4,2,6,1,3,null,null]
# 输出: 1
# 解释:
# 注意，root是树节点对象(TreeNode object)，而不是数组。
# 
# 给定的树 [4,2,6,1,3,null,null] 可表示为下图:
# 
#           4
#         /   \
#       2      6
#      / \    
#     1   3  
# 
# 最小的差值是 1, 它是节点1和节点2的差值, 也是节点3和节点2的差值。 
# 
#  
# 
#  注意： 
# 
#  
#  二叉树的大小范围在 2 到 100。 
#  二叉树总是有效的，每个节点的值都是整数，且不重复。 
#  本题与 530：https://leetcode-cn.com/problems/minimum-absolute-difference-in-bst/ 
# 相同 
#  
#  Related Topics 树 递归 
#  👍 65 👎 0


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
    def minDiffInBST(self, root: TreeNode) -> int:
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