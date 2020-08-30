// LeetCode300 最长上升子序列 longest-increasing-subsequence

//给定一个无序的整数数组，找到其中最长上升子序列的长度。 
//
// 示例: 
//
// 输入: [10,9,2,5,3,7,101,18]
//输出: 4 
//解释: 最长的上升子序列是 [2,3,7,101]，它的长度是 4。 
//
// 说明: 
//
// 
// 可能会有多种最长上升子序列的组合，你只需要输出对应的长度即可。 
// 你算法的时间复杂度应该为 O(n2) 。 
// 
//
// 进阶: 你能将算法的时间复杂度降低到 O(n log n) 吗? 
// Related Topics 二分查找 动态规划 
// 👍 833 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)

// 解法1：暴力递归/动态规划。
// T(n)：O(n^2)

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int size = nums.size();
        if(!size) return 0;

        vector<int> dp(size, 0);

        dp[0] = 1;

        for(int i = 1; i < size; ++i) {
            int minIndex = helper(nums,dp, i);
            if(minIndex != -1) {
                dp[i] = max(1, 1 + dp[minIndex]);
            }
            else {
                dp[i] = 1;
            }
        }

//        sort(dp.begin(), dp.end());
//        int maxLIS = dp[size - 1];
        int maxLIS = *max_element(dp.begin(), dp.end());

        return maxLIS;
    }

    // 在当前index之前的序列中，找到最后一个比当前值小且dp值最大的index
    int helper(vector<int>& nums, vector<int>&dp, int index) {

        int minIndex = -1;
        int maxLIS = 0;

        for (int i = 0; i < index; ++i) {
            if(nums[i] < nums[index] && dp[i] > maxLIS) {
                minIndex = i;
                maxLIS = dp[i];
            }
        }

        return minIndex;
    }

};

// 解法2：贪心算法+二分查找。
// T(n)：O(nlogn)


//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> v{10,9,2,5,3,7,101,18};

    Solution solution;
    int temp = solution.lengthOfLIS(v);
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