// LeetCode606 根据二叉树创建字符串 construct-string-from-binary-tree

# 你需要采用前序遍历的方式，将一个二叉树转换成一个由括号和整数组成的字符串。 
# 
#  空节点则用一对空括号 "()" 表示。而且你需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对。 
# 
#  示例 1: 
# 
#  
# 输入: 二叉树: [1,2,3,4]
#        1
#      /   \
#     2     3
#    /    
#   4     
# 
# 输出: "1(2(4))(3)"
# 
# 解释: 原本将是“1(2(4)())(3())”，
# 在你省略所有不必要的空括号对之后，
# 它将是“1(2(4))(3)”。
#  
# 
#  示例 2: 
# 
#  
# 输入: 二叉树: [1,2,3,null,4]
#        1
#      /   \
#     2     3
#      \  
#       4 
# 
# 输出: "1(2()(4))(3)"
# 
# 解释: 和第一个示例相似，
# 除了我们不能省略第一个对括号来中断输入和输出之间的一对一映射关系。
#  
#  Related Topics 树 字符串 
#  👍 127 👎 0


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
    def tree2str(self, t: TreeNode) -> str:
        
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