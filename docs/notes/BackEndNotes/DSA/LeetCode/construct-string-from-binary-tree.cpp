// LeetCode606 根据二叉树创建字符串 construct-string-from-binary-tree

//你需要采用前序遍历的方式，将一个二叉树转换成一个由括号和整数组成的字符串。 
//
// 空节点则用一对空括号 "()" 表示。而且你需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对。 
//
// 示例 1: 
//
// 
//输入: 二叉树: [1,2,3,4]
//       1
//     /   \
//    2     3
//   /    
//  4     
//
//输出: "1(2(4))(3)"
//
//解释: 原本将是“1(2(4)())(3())”，
//在你省略所有不必要的空括号对之后，
//它将是“1(2(4))(3)”。
// 
//
// 示例 2: 
//
// 
//输入: 二叉树: [1,2,3,null,4]
//       1
//     /   \
//    2     3
//     \  
//      4 
//
//输出: "1(2()(4))(3)"
//
//解释: 和第一个示例相似，
//除了我们不能省略第一个对括号来中断输入和输出之间的一对一映射关系。
// 
// Related Topics 树 字符串 
// 👍 126 👎 0


// pan: test header
#include "base-tree.h"

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

// 解法1：递归。进行前序遍历时，按照不同情况添加额外的括号。分为四种情况：
// 1. 当前节点有左右子树，则递归时需要在左右子树的结果都添加一层括号。
// 2. 当前节点没有左右子树，则递归时不需要添加任何括号。
// 3. 当前节点只有左子树，则递归时只给左子树的结果添加一层括号。
// 4. 当前节点只有右子树，则先给添加一层空括号，表示左子树为空，然后递归时给右子树的结果添加一层括号
class Solution {
public:

    string tree2str(TreeNode* t) {
        if(!t) return "";

        // 情况2
        if(!t->left && !t->right) return to_string(t->val) + "";

        // 情况3
        if(!t->right) return to_string(t->val) + "(" + tree2str(t->left) + ")";

        // 情况4
        if(!t->left) return to_string(t->val) + "()" + "(" + tree2str(t->right) + ")";

        // 情况1
        return to_string(t->val) + "(" + tree2str(t->left) + ")" + "(" + tree2str(t->right) + ")";
    }


};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{1,2,3,4};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    string temp = solution.tree2str(root);
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