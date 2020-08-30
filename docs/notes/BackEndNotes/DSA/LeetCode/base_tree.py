# -*- coding: utf-8 -*-
"""
@Author    : parzulpan

@Email     : parzulpan@gmail.com

@Summary   : 该文件所实现的功能描述

@Attention : 
"""

from collections import deque


class TreeNode:
    """
    Definition for a binary tree node.
    """
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class BaseTree:
    """

    """
    def __init__(self):
        pass

    @staticmethod
    def create_tree_from_level_order_list(root: TreeNode, level_order_list: list, start: int) -> TreeNode or None:
        """ 用层次遍历递归创建二叉树

        :param root:
        :param level_order_list:
        :param start:
        :return:
        """
        if start < len(level_order_list):
            if level_order_list[start] is None:
                return None
            else:
                root = TreeNode(level_order_list[start])
                root.left = BaseTree.create_tree_from_level_order_list(root.left, level_order_list, 2 * start + 1)
                root.right = BaseTree.create_tree_from_level_order_list(root.right, level_order_list, 2 * start + 2)
                return root

        return root

    @staticmethod
    def level_order_traversal(root: TreeNode) -> None:
        """ 迭代法 层序遍历

        :param root:
        :return:
        """
        if root is None:
            return

        queue = [root]
        while queue:
            root = queue.pop(0)
            print(root.val + " ")
            if root.left is not None:
                queue.append(root.left)
            if root.right is not None:
                queue.append(root.right)

    @staticmethod
    def pre_order_traversal(root: TreeNode) -> None:
        """ 递归法 前序遍历

        :param root:
        :return:
        """
        if root is None:
            return

        print(root.val + " ")
        BaseTree.pre_order_traversal(root.left)
        BaseTree.pre_order_traversal(root.right)

    @staticmethod
    def pre_order_traversal_iterative_method(root: TreeNode) -> None:
        """ 迭代法 前序遍历

        :param root:
        :return:
        """
        if root is None:
            return

        stack = []
        while root or stack:
            while root:
                print(root.val + " ")
                stack.append(root)
                root = root.left
            root = stack.pop()
            root = root.right

    @staticmethod
    def in_order_traversal(root: TreeNode) -> None:
        """ 递归法 中序遍历

        :param root:
        :return:
        """
        if root is None:
            return

        BaseTree.pre_order_traversal(root.left)
        print(root.val + " ")
        BaseTree.pre_order_traversal(root.right)

    @staticmethod
    def in_order_traversal_iterative_method(root: TreeNode) -> None:
        """ 迭代法 中序遍历

        :param root:
        :return:
        """
        if root is None:
            return

        stack = []
        while root or stack:
            while root:
                stack.append(root)
                root = root.left

            root = stack.pop()
            print(root.val + " ")
            root = root.right

    @staticmethod
    def post_order_traversal(root: TreeNode) -> None:
        """ 递归法 后序遍历

        :param root:
        :return:
        """
        if root is None:
            return

        BaseTree.pre_order_traversal(root.left)
        BaseTree.pre_order_traversal(root.right)
        print(root.val + " ")

    @staticmethod
    def post_order_traversal_iterative_method(root: TreeNode) -> None:
        """ 迭代法 后序遍历

        :param root:
        :return:
        """
        if root is None:
            return

        stack = []
        while stack:
            root = stack.pop()
            if root.left:
                stack.append(root.left)
            if root.right:
                stack.append(root.right)
            stack.append(root)

        while stack:
            print(stack.pop() + " ")
