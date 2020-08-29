// LeetCode322 零钱兑换 coin-change

//给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回
// -1。 
//
// 
//
// 示例 1: 
//
// 输入: coins = [1, 2, 5], amount = 11
//输出: 3 
//解释: 11 = 5 + 5 + 1 
//
// 示例 2: 
//
// 输入: coins = [2], amount = 3
//输出: -1 
//
// 
//
// 说明: 
//你可以认为每种硬币的数量是无限的。 
// Related Topics 动态规划 
// 👍 705 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)

// 这是一个动态规划问题，因为它具有最优子结构。
// 比如：想求 amount = 11 时的最少硬币数（原问题），如果知道凑出 amount = 10 的最少硬币数（子问题），
// 只需要把子问题的答案加一（再选一枚面值为 1 的硬币）就是原问题的答案。因为硬币的数量是没有限制的，所以子问题之间没有相互制，是互相独立的。

// base case：目标金额 amount 为 0 时算法返回 0
// 状态，即原问题和子问题中会变化的量：唯一的状态就是目标金额 amount
// 选择，即导致状态发生变化的行为：硬币的面值
// dp函数/向量的定义：输入一个目标金额 n，返回凑出目标金额 n 的最少硬币数量
// 状态转移方程：
// dp(n): 0, n = 0; -1, n < 0; min{dp(n - coin} + 1 | coin in coins }, n > 0;

// 解法1：暴力递归。
// T(n)：指数级别。
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // base case
        if(amount == 0) return 0;
        if(amount < 0) return -1;

        // 求最小值，结果默认初始化为最大整型值
        int res = INT32_MAX;

        for(auto& coin : coins) {
            int subProblem = coinChange(coins, amount - coin);

            // 子问题无解，跳过
            if(subProblem == -1)
                continue;

            res = min(res, subProblem + 1);
        }

        return (res != INT32_MAX) ? res : -1;
    }
};

// 解法2：带备忘录的递归。
// T(n)：O(n)
class Solution2 {
public:
    map<int, int> memo;
    int coinChange(vector<int>& coins, int amount) {
        if(memo.cend() != memo.find(amount)) return memo[amount];

        // base case
        if(amount == 0) return 0;
        if(amount < 0) return -1;

        // 求最小值，结果默认初始化为最大整型值
        int res = INT32_MAX;

        for(auto& coin : coins) {
            int subProblem = coinChange(coins, amount - coin);

            // 子问题无解，跳过
            if(subProblem == -1)
                continue;

            res = min(res, subProblem + 1);
        }

        // 添加到备忘录
        memo.insert({amount, (res != INT32_MAX) ? res : -1});

        return memo[amount];
    }
};

// 解法3：dp向量的迭代解法。
// T(n)：O(n)
class Solution3 {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 数组值代表最少硬币数，大小为amount + 1，并将数组值设为不可能出现的面值
        vector<int> dp(amount + 1, amount + 1);

        // base case
        dp[0] = 0;

        // 遍历所有状态的所有取值
        int len = dp.size();
        for(int i = 0; i < len; ++i) {
            // 求所有子问题+1的最小值
            for(int coin: coins) {
                // 子问题无解则跳过，当目标金额为 i 时，至少需要 dp[i] 枚硬币凑出。
                if(i - coin >= 0) {
                    dp[i] = min(dp[i], 1 + dp[i - coin]);
                }
            }
        }
        return (dp[amount] == amount + 1) ? -1 : dp[amount];
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int> v{1, 2, 5};

    Solution solution;
    int temp = solution.coinChange(v, 11);
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
 * Summary: 计算机解决问题其实没有任何奇技淫巧，它唯一的解决办法就是穷举，穷举所有可能性。算法设计无非就是先思考“如何穷举”，然后再追求“如何聪明地穷举”。
 */ 