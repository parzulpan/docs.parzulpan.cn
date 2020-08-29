// LeetCode653 两数之和 IV - 输入 BST two-sum-iv-input-is-a-bst

//给定一个二叉搜索树和一个目标结果，如果 BST 中存在两个元素且它们的和等于给定的目标结果，则返回 true。 
//
// 案例 1: 
//
// 
//输入: 
//    5
//   / \
//  3   6
// / \   \
//2   4   7
//
//Target = 9
//
//输出: True
// 
//
// 
//
// 案例 2: 
//
// 
//输入: 
//    5
//   / \
//  3   6
// / \   \
//2   4   7
//
//Target = 28
//
//输出: False
// 
//
// 
// Related Topics 树 
// 👍 151 👎 0


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

// 解法1：递归。中序遍历得到递增序列，然后求和即可。
class Solution {
public:
    vector<int> preOrderVector;

    bool findTarget(TreeNode* root, int k) {
        if(!root) return false;

        postOrderTraversal(root);
        int size = preOrderVector.size();
        for(int i = 0, j = size - 1; i < j ;) {
            if(preOrderVector[i] + preOrderVector[j] > k)
                --j;
            else if (preOrderVector[i] + preOrderVector[j] < k)
                ++i;
            else
                return true;
        }

        return false;
    }

    void postOrderTraversal(TreeNode * root) {
        if(!root) return;

        postOrderTraversal(root->left);
        preOrderVector.push_back(root->val);
        postOrderTraversal(root->right);
    }
};

// 解法2：迭代。层序遍历，将值加入set。
class Solution1 {
public:

    bool findTarget(TreeNode* root, int k) {
        if(!root) return false;

        queue<TreeNode*> q;
        q.push(root);
        set<int> s;

        while(!q.empty()) {
            TreeNode* temp = q.front();
            q.pop();

            // 函数：count
            // 作用：判断元素是否在集合set中
            // 返回值：存在返回1个，不存在返回0个。
            if(s.count(k - temp->val))
                return true;

            s.insert(temp->val);

            if(temp->left) q.push(temp->left);
            if(temp->right) q.push(temp->right);
        }


        return false;
    }
};



//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{2,1,3};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    bool temp = solution.findTarget(root, 4);
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