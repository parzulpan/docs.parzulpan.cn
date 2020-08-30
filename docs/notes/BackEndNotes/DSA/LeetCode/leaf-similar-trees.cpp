// LeetCode872 叶子相似的树 leaf-similar-trees

//请考虑一颗二叉树上所有的叶子，这些叶子的值按从左到右的顺序排列形成一个 叶值序列 。 
//
// 
//
// 举个例子，如上图所示，给定一颗叶值序列为 (6, 7, 4, 9, 8) 的树。 
//
// 如果有两颗二叉树的叶值序列是相同，那么我们就认为它们是 叶相似 的。 
//
// 如果给定的两个头结点分别为 root1 和 root2 的树是叶相似的，则返回 true；否则返回 false 。 
//
// 
//
// 提示： 
//
// 
// 给定的两颗树可能会有 1 到 200 个结点。 
// 给定的两颗树上的值介于 0 到 200 之间。 
// 
// Related Topics 树 深度优先搜索 
// 👍 60 👎 0


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

// 解法1：迭代。先序遍历。
class Solution {
public:
    vector<int> res1;
    vector<int> res2;

    bool leafSimilar(TreeNode *root1, TreeNode *root2) {
        if(!root1 && !root2) return true;

        helper(root1, res1);
        helper(root2, res2);

        if(res1 == res2) return true;

        return false;
    }

    void helper(TreeNode *root, vector<int> &res) {
        if(!root) return;

        stack<TreeNode *> s;
        s.push(root);

        while (!s.empty()) {
            TreeNode *temp = s.top();
            s.pop();

            if(temp && !temp->left && !temp->right) res.push_back(temp->val);
            if(temp->right) s.push(temp->right);
            if(temp->left) s.push(temp->left);

        }
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{3,5,1,6,2,9,8,null,null,7,4};
    vector<int> levelOrderVector1{3,5,1,6,7,4,2,null,null,null,null,null,null,9,8};

    BaseTree baseTree;

    TreeNode *root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());
    TreeNode *root1 = baseTree.createTreeFromLevelOrderVector(levelOrderVector1, levelOrderVector1.size());

    Solution solution;
    bool temp = solution.leafSimilar(root, root1);
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