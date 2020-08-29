// LeetCode700 二叉搜索树中的搜索 search-in-a-binary-search-tree

# 给定二叉搜索树（BST）的根节点和一个值。 你需要在BST中找到节点值等于给定值的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 NULL。 
# 
#  例如， 
# 
#  
# 给定二叉搜索树:
# 
#         4
#        / \
#       2   7
#      / \
#     1   3
# 
# 和值: 2
#  
# 
#  你应该返回如下子树: 
# 
#  
#       2     
#      / \   
#     1   3
#  
# 
#  在上述示例中，如果要找的值是 5，但因为没有节点值为 5，我们应该返回 NULL。 
#  Related Topics 树 
#  👍 69 👎 0


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
    def searchBST(self, root: TreeNode, val: int) -> TreeNode:
        
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