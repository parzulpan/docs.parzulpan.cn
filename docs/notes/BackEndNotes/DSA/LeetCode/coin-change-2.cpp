// LeetCode518 零钱兑换 II coin-change-2

//给定不同面额的硬币和一个总金额。写出函数来计算可以凑成总金额的硬币组合数。假设每一种面额的硬币有无限个。 
//
// 
//
// 
// 
//
// 示例 1: 
//
// 输入: amount = 5, coins = [1, 2, 5]
//输出: 4
//解释: 有四种方式可以凑成总金额:
//5=5
//5=2+2+1
//5=2+1+1+1
//5=1+1+1+1+1
// 
//
// 示例 2: 
//
// 输入: amount = 3, coins = [2]
//输出: 0
//解释: 只用面额2的硬币不能凑成总金额3。
// 
//
// 示例 3: 
//
// 输入: amount = 10, coins = [10] 
//输出: 1
// 
//
// 
//
// 注意: 
//
// 你可以假设： 
//
// 
// 0 <= amount (总金额) <= 5000 
// 1 <= coin (硬币面额) <= 5000 
// 硬币种类不超过 500 种 
// 结果符合 32 位符号整数 
// 
// 👍 197 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)

// 解法1：动态规划。完全背包问题。dp[i][j] = x，若只使用前i个物品，当背包容量为j时，有x中方法可以装满背包。
class Solution {
public:
    int change(int amount, vector<int>& coins) {

        // dp vector
        int size = coins.size();
        vector<vector<int>> dp(size+1, vector<int>(amount+1, 0));

        // base case
        for(int i = 0; i <= size; ++i) dp[i][0] = 1;

        for(int i = 1; i <= size; ++i) {
            for(int j = 1; j <= amount; ++j) {
                if(j - coins[i-1] >= 0)
                    dp[i][j] = dp[i-1][j] + dp[i][j-coins[i-1]];
                else
                    dp[i][j] = dp[i-1][j];
            }
        }

        return dp[size][amount];
    }
};

// 解法2：带有状态压缩的动态规划。
class Solution2 {
public:
    int change(int amount, vector<int>& coins) {
        int size = coins.size();
        vector<int> dp(amount + 1, 0);

        // base case
        dp[0] = 1;

        for(int i = 0; i < size; ++i) {
            for(int j = 1; j <= amount; ++j) {
                if(j - coins[i] >= 0)
                    dp[j] = dp[j] + dp[j - coins[i]];
            }
        }

        return dp[amount];
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> v{1, 2, 5};

    Solution solution;
    int temp = solution.change(5, v);
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