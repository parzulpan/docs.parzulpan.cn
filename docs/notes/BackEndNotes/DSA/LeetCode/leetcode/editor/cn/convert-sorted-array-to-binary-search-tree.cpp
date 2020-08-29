// LeetCode108 将有序数组转换为二叉搜索树

//将一个按照升序排列的有序数组，转换为一棵高度平衡二叉搜索树。 
//
// 本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。 
//
// 示例: 
//
// 给定有序数组: [-10,-3,0,5,9],
//
//一个可能的答案是：[0,-3,9,-10,null,5]，它可以表示下面这个高度平衡二叉搜索树：
//
//      0
//     / \
//   -3   9
//   /   /
// -10  5
// 
// Related Topics 树 深度优先搜索


//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 解法1：递归。分析知，根节点应该是有序数组的中间点，从中间点分开为左右两个有序数组，在分别找出其中间点作为原中间点的左右两个子节点，即二分查找的核心思想
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }

    TreeNode* helper(vector<int>nums, int left, int right) {
        if(left > right) return NULL;

        int mid = (right - left) / 2 + left;
        TreeNode* cur = new TreeNode(nums[mid]);
        cur->left = helper(nums, left, mid - 1);
        cur->right = helper(nums, mid + 1, right);
        return cur;
    }
};

//leetcode submit region end(Prohibit modification and deletion)

/**
 * KnowledgePoint:
 * 二叉查找树（Binary Search Tree），（又：二叉搜索树，二叉排序树）它或者是一棵空树，或者是具有下列性质的二叉树：
 * 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
 * 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
 * 它的左、右子树也分别为二叉排序树。
 * 二叉搜索树作为一种经典的数据结构，它既有链表的快速插入与删除操作的特点，又有数组快速查找的优势；
 * 所以应用十分广泛，例如在文件系统和数据库系统一般会采用这种数据结构进行高效率的排序与检索操作。
 *
 * T(n) =
 *
 * O(n) =
 *
 * Summary:
 * 遍历树的方法大致分为两类：
 * 1. DFS: 先序遍历、中序遍历、后序遍历
 * 2. BFS: 层序遍历
 * 众所周知，二叉搜索树的中序遍历结果输出的是升序序列，那么，反之，将有序序列作为输入，可以将该问题看作根据中序遍历序列创建二叉搜索树。
 * 易知，只有中序序列 或者 有先序和后序序列不能确定一棵二叉搜索树，但是有先序/后序序列和中序序列能确定一棵二叉搜索树，所有这里可能有多个二叉搜索树。
 * 但是，加上了树平衡的要求能唯一确定吗？
 * 答案是不能，因为选择中点进行构造，但是需要分奇数和偶数的情况。
 */