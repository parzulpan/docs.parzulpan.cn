// LeetCode377 组合总和 Ⅳ combination-sum-iv

//给定一个由正整数组成且不存在重复数字的数组，找出和为给定目标正整数的组合的个数。 
//
// 示例: 
//
// 
//nums = [1, 2, 3]
//target = 4
//
//所有可能的组合为：
//(1, 1, 1, 1)
//(1, 1, 2)
//(1, 2, 1)
//(1, 3)
//(2, 1, 1)
//(2, 2)
//(3, 1)
//
//请注意，顺序不同的序列被视作不同的组合。
//
//因此输出为 7。
// 
//
// 进阶： 
//如果给定的数组中含有负数会怎么样？ 
//问题会产生什么变化？ 
//我们需要在题目中添加什么限制来允许负数的出现？ 
//
// 致谢： 
//特别感谢 @pbrother 添加此问题并创建所有测试用例。 
// Related Topics 动态规划 
// 👍 176 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)

// 解法1：动态规划。完全背包问题。

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        // 处理测试用例: []
        if(nums.empty()) return 0;

        // 用数学知识排除恶心的测试用例，防止爆栈。如果nums中所有数的最大公约数g不能整除target，那么答案肯定为0
        // 测试用例: nums = [3,33,333], target = 10000
        int g = nums[0];
        for(auto num : nums)
            g = __gcd(g, num);
        if(target % g != 0) return 0;

        // dp vector
        vector<unsigned long long> dp(target + 1, 0);

        // base case
        dp[0] = 1;

        // 注意这里的状态转移
        int size = nums.size();
        for(int j = 1; j <= target; ++j) {
            for(int i = 0; i < size; ++i) {
                if(j >= nums[i])
                    dp[j] = dp[j] + dp[j - nums[i]];
            }
        }

        return dp[target];
    }
};
//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> v{1, 2, 3};

    Solution solution;
    int temp = solution.combinationSum4(v, 4);
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