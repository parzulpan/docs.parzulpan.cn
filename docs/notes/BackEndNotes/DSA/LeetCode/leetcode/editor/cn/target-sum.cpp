// LeetCode494 目标和 target-sum

//给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。对于数组中的任意一个整数，你都可以从 + 或 -中选
//择一个符号添加在前面。 
//
// 返回可以使最终数组和为目标数 S 的所有添加符号的方法数。 
//
// 
//
// 示例： 
//
// 输入：nums: [1, 1, 1, 1, 1], S: 3
//输出：5
//解释：
//
//-1+1+1+1+1 = 3
//+1-1+1+1+1 = 3
//+1+1-1+1+1 = 3
//+1+1+1-1+1 = 3
//+1+1+1+1-1 = 3
//
//一共有5种方法让最终目标和为3。
// 
//
// 
//
// 提示： 
//
// 
// 数组非空，且长度不会超过 20 。 
// 初始的数组的和不会超过 1000 。 
// 保证返回的最终结果能被 32 位整数存下。 
// 
// Related Topics 深度优先搜索 动态规划 
// 👍 321 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)

// 解法1：动态规划。
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int len = nums.size();
        unsigned long long sum = accumulate(nums.begin(), nums.end(), 0);
        unsigned long long dpVal = (S + sum) / 2;
        if(nums.empty() || abs(S) > sum || (S + sum) % 2 != 0) return 0;

        // dp table
        vector<unsigned long long> dp(dpVal+1, 0);
        // base case
        dp[0] = 1;

        for(int i = 1; i <= len; ++i) {
            for(unsigned long long j = dpVal; j >= 0; --j) {
                if(j >= nums[i-1]) {
                    dp[j] = dp[j] + dp[j-nums[i-1]];
                }
            }
        }

        return dp[dpVal];
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> v{1, 1, 1, 1, 1};

    Solution solution;
    int temp = solution.findTargetSumWays(v, 3);
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