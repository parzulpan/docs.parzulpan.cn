# LeetCode100 相同的树 same-tree

# 给定两个二叉树，编写一个函数来检验它们是否相同。 
# 
#  如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。 
# 
#  示例 1: 
# 
#  输入:       1         1
#           / \       / \
#          2   3     2   3
# 
#         [1,2,3],   [1,2,3]
# 
# 输出: true 
# 
#  示例 2: 
# 
#  输入:      1          1
#           /           \
#          2             2
# 
#         [1,2],     [1,null,2]
# 
# 输出: false
#  
# 
#  示例 3: 
# 
#  输入:       1         1
#           / \       / \
#          2   1     1   2
# 
#         [1,2,1],   [1,1,2]
# 
# 输出: false
#  
#  Related Topics 树 深度优先搜索 
#  👍 394 👎 0


# pan: test import
from LeetCode.leetcode.editor.cn.base_tree import TreeNode, BaseTree, deque

# leetcode submit region begin(Prohibit modification and deletion)
# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:
    """
    解法1：递归。
    """
    def isSameTree(self, p: TreeNode, q: TreeNode) -> bool:

        if not p and not q:
            return True

        if not q or not p or p.val != q.val:
            return False

        return self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)


class Solution2:
    """
    解法2：迭代。利用双向队列deque。
    """

    def isSameTree(self, p: TreeNode, q: TreeNode) -> bool:

        def check(_p, _q):
            if not _p and not _q:
                return True
            if not _q or not _p:
                return False
            if _p.val != _q.val:
                return False
            return True

        deq = deque()
        deq.append([p, q])
        while deq:
            p, q = deq.popleft()
            if not check(p, q):
                return False
            if p:
                deq.append([p.left, q.left])
                deq.append([p.right, q.right])

        return True

# leetcode submit region end(Prohibit modification and deletion)


# pan: test main
if __name__ == '__main__':
    root = BaseTree.create_tree_from_level_order_list(TreeNode(None), [1, 2, 3], 0)
    root1 = BaseTree.create_tree_from_level_order_list(TreeNode(None), [1, 2, 3], 0)
    solution = Solution()
    temp = solution.isSameTree(root, root1)
    print(temp)


"""
KnowledgePoint:

T(n) = 

O(n) = 

Summary:
"""