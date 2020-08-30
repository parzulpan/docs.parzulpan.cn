// LeetCode559 N叉树的最大深度 maximum-depth-of-n-ary-tree

# 给定一个 N 叉树，找到其最大深度。 
# 
#  最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。 
# 
#  例如，给定一个 3叉树 : 
# 
#  
# 
#  
# 
#  
# 
#  我们应返回其最大深度，3。 
# 
#  说明: 
# 
#  
#  树的深度不会超过 1000。 
#  树的节点总不会超过 5000。 
#  Related Topics 树 深度优先搜索 广度优先搜索 
#  👍 97 👎 0


// pan: test header
//include "base-tree.h"

# leetcode submit region begin(Prohibit modification and deletion)
"""
# Definition for a Node.
class Node:
    def __init__(self, val=None, children=None):
        self.val = val
        self.children = children
"""

class Solution:
    def maxDepth(self, root: 'Node') -> int:
        
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