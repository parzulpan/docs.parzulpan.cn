// LeetCode107 二叉树的层次遍历 II

//给定一个二叉树，返回其节点值自底向上的层次遍历。 （即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历） 
//
// 例如： 
//给定二叉树 [3,9,20,null,null,15,7], 
//
//     3
//   / \
//  9  20
//    /  \
//   15   7
// 
//
// 返回其自底向上的层次遍历为： 
//
// [
//  [15,7],
//  [9,20],
//  [3]
//]
// 
// Related Topics 树 广度优先搜索


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

// 解法1：递归
class Solution {
public:
    vector<vector<int>> v;
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        helper(root, 0);
        reverse(v.begin(), v.end());
        return v;
    }

    void helper(TreeNode* root, int depth) {
        if(root) {
            // 同一层
            if(v.size() <= depth) {
                v.push_back(vector<int>());
            }

            // 将该层结果加入
            v[depth].push_back(root->val);
        } else {
            return;
        }

        helper(root->left, depth + 1 );
        helper(root->right, depth + 1);
    }
};

// 解法2：迭代。进行层序遍历，将每一层的节点值存入 temp vector ，将每一层的 temp vector 存入stack中，最后从stack取值到最终值中
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        // 结果向量
        vector<vector<int>> v;

        // 存放每层结果向量，也可以不用，直接reverse即可
        // stack<vector<int>> s;

        // 存在节点
        queue<TreeNode*> q;

        TreeNode* temp = root;
        if(!temp) return v;

        q.push(temp);

        while(!q.empty()) {
            int size = q.size();
            vector<int> temp;
            // 对每一层的节点进行操作
            for (int i = 0; i < size; ++i) {
                TreeNode* p = q.front();
                q.pop();
                temp.push_back(p->val);
                if(p->left) q.push(p->left);
                if(p->right) q.push(p->right);
            }
            v.push_back(temp);
        }

//        反转操作
//        while(!s.empty()) {
//            v.push_back(s.top());
//            s.pop();
//        }
        reverse(v.begin(), v.end());

        return v;
    }
};

//leetcode submit region end(Prohibit modification and deletion)


/**
 * KnowledgePoint:
 *
 * T(n) =
 *
 * O(n) =
 *
 * Summary:
 */