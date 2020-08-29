// LeetCode226 翻转二叉树

//翻转一棵二叉树。 
//
// 示例： 
//
// 输入： 
//
//      4
//   /   \
//  2     7
// / \   / \
//1   3 6   9 
//
// 输出： 
//
//      4
//   /   \
//  7     2
// / \   / \
//9   6 3   1 
//
// 备注: 
//这个问题是受到 Max Howell 的 原问题 启发的 ： 
//
// 谷歌：我们90％的工程师使用您编写的软件(Homebrew)，但是您却无法在面试时在白板上写出翻转二叉树这道题，这太糟糕了。 
// Related Topics 树

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

// 解法1：递归。
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root)
            return NULL;
        TreeNode *tmp = root->left;
        root->left = invertTree(root->right);
        root->right = invertTree(tmp);
        return root;
    }
};

//// 解法2：迭代。这是一个不太好的解法，请直接看解法3。
//class Solution {
//public:
//    TreeNode* invertTree(TreeNode* root) {
//        if(!root) return root;
//
//        queue<TreeNode*> q;
//        vector<TreeNode*> v1;
////        vector<int> v2;
//        q.push(root);
//        v1.push_back(root)
////        v2.push_back(root->val)
//
//        while(!q.empty()) {
//            int size = q.size();
//            for(int i = 0; i < size; ++i) {
//                TreeNode* temp = q.front();
//                q.pop();
//
//                if(temp->left) {
//                    q.push(temp->left);
//                    v1.push_back(temp->left)
//                    v2.push_back(0)
//                } else {
//                    v1.push_back(temp)
//                    v2.push_back(0)
//                }
//                if(temp->right) {
//                    q.push(temp->right);
//                    v1.push_back(temp->right)
//                    v2.push_back(1)
//                } else {
//                    v1.push_back(temp)
//                    v2.push_back(1)
//                }
//            }
//
//            int begin = 0;
//            int end = v1.size() - 1;
//            for(int i = begin, int j = end; i < j; ++i, --j;) {
//                if(v1[i] && v1[j]) {
//                    int temp = v1[i]->val;
//                    v1[i]->val = v1[j]->val;
//                    v1[j]->val = temp;
//                }
//
//                if(v1[i] && !v1[j]) {
//                    int temp = v1[i]->val;
//                    if(!v2[i]) {
//                        v1[j]->right = v1[i];
//                        v1[j]->right->val = temp;
//                    } else {
//                        v1[j]->left = v1[i];
//                        v1[j]->left->val = temp;
//                    }
//                    v1[i] = NULL;
//                }
//
//                if(!v1[i] && v1[j]) {
//                    int temp = v1[j]->val;
//                    if(!v2[j]) {
//                        v1[i]->right = v1[j];
//                        v1[i]->right->val = temp;
//                    } else {
//                        v1[i]->left = v1[j];
//                        v1[i]->left->val = temp;
//                    }
//                    v1[j] = NULL;
//                }
//            }
//        }
//
//        return root;
//    }
//};

// 解法3：迭代。使用层序遍历，直接交换左右子树即可。
class SolutionA {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root)
            return NULL;

        queue<TreeNode*> q;
        TreeNode* node = root;
        int size = 0;
        q.push(root);

        while (!q.empty()) {
            size = q.size();
            for(int i = 0; i < size; ++i) {
                node = q.front();
                q.pop();

                // 左右子树交换
                TreeNode* tmp = node->left;
                node->left = node->right;
                node->right = tmp;

                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }
        return root;
    }
};

//leetcode submit region end(Prohibit modification and deletion)

// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{4,2,7,1,3,6,9};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    TreeNode* temp = solution.invertTree(root);

    baseTree.levelOrderTraversal(temp);

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