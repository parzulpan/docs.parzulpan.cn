// LeetCode53 最大子序和 maximum-subarray

//给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。 
//
// 示例: 
//
// 输入: [-2,1,-3,4,-1,2,1,-5,4],
//输出: 6
//解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
// 
//
// 进阶: 
//
// 如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的分治法求解。 
// Related Topics 数组 分治算法 动态规划 
// 👍 2186 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)

// 这是一个动态规划问题，因为它具有最优子结构。
// base case：
// 状态，即原问题和子问题中会变化的量：最大和
// 选择，即导致状态发生变化的行为：数组值
// dp函数/向量的定义：以 nums[i] 为结尾的 最大子数组和 为 dp[i]。
// 状态转移方程：
// f(i) = max{f(i-1) + Ai , Ai}

// 解法1：暴力递归。
// T(n)：指数级别。
class Solution {
public:
    int maxSubArray(vector<int>& nums) {

        int maxValue = 0;
        int size = nums.size();
        for(int i = 0; i < size; ++i) {
            int temp = 0;
            for(int j = i; j < size; ++j) {
                temp += nums[j];
                maxValue = max(maxValue, temp);
            }
        }
        return maxValue;
    }
};

// 解法2：dp向量的迭代解法。
// T(n)：O(n)
class Solution2 {
public:
    int maxSubArray(vector<int>& nums) {
        int size = nums.size();
        if(size == 0) return 0;
        if(size == 1) return nums[0];
        vector<int> dp(size, 0);

        // base case
        dp[0] = nums[0];

        // 状态转移方程
        for (int i = 1; i < size; ++i) {
            // 当前值 与 当前值加上之前的值 选最大
           dp[i] = max(nums[i], nums[i] + dp[i - 1]);
        }

//        int maxValue = INT32_MIN;
//        for (int i = 0; i < size; ++i) {
//            maxValue = max(maxValue, dp[i]);
//        }
        sort(dp.begin(), dp.end());
        int maxValue = dp[size - 1];

        return maxValue;
    }
};

// 解法3：dp向量状态压缩的迭代解法。注意到 dp[i] 仅仅和 dp[i-1] 的状态有关。
// T(n)：O(n)
class Solution3 {
public:
    int maxSubArray(vector<int>& nums) {
        if(nums.empty()) return 0;

        int preMaxVal = 0, maxValue = nums[0];
        for(const auto&x: nums) {
            // 保存上一次的结果
            preMaxVal = max(x, preMaxVal + x);
            maxValue = max(preMaxVal, maxValue);
        }

        return maxValue;
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> v{-2,1,-3,4,-1,2,1,-5,4};

    Solution3 solution;
    int temp = solution.maxSubArray(v);
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