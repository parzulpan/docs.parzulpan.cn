// LeetCode543 二叉树的直径 diameter-of-binary-tree

//给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。 
//
// 
//
// 示例 : 
//给定二叉树 
//
//           1
//         / \
//        2   3
//       / \     
//      4   5    
// 
//
// 返回 3, 它的长度是路径 [4,2,1,3] 或者 [5,2,1,3]。 
//
// 
//
// 注意：两结点之间的路径长度是以它们之间边的数目表示。 
// Related Topics 树 
// 👍 396 👎 0


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

// 解法1：递归。保存左右子深度之和的最大值。
class Solution {
public:
    int maxLength=0;
//    int curLength;
//    int size = 0;
//    TreeNode* temp;

    int diameterOfBinaryTree(TreeNode* root) {
        if(!root) return 0;

        helper(root);

        return maxLength;

    }

    int helper(TreeNode* root) {
        if(!root) return 0;

        int lengthL = helper(root->left);
        int lengthR = helper(root->right);
        maxLength = max(maxLength, lengthL + lengthR);

        return max(lengthL, lengthR) + 1;
    }

//    // 获得节点的左右子树的层数和
//    int getLevel(TreeNode* root) {
//        if(!root) return 0;
//        queue<TreeNode*> q;
//        q.push(root);
//        int levelL = 0;
//        int levelR = 0;
//
//        while(!q.empty()) {
//            size = q.size();
//
//            for (int i = 0; i < size; ++i) {
//                temp = q.front();
//                q.pop();
//
//                if(!temp->left && !temp->right) {
//                    ;
//                }
//
//                if(temp->left) {
//                    levelL++;
//                    q.push(temp->left);
//                }
//
//                if(temp->right) {
//                    levelR++;
//                    q.push(temp->right);
//                }
//            }
//        }
//
//        return levelL + levelR;
//    }
};


//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> levelOrderVector{1,2,3,4,5,null,null,7,null,null,6};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());

    Solution solution;
    int temp = solution.diameterOfBinaryTree(root);
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