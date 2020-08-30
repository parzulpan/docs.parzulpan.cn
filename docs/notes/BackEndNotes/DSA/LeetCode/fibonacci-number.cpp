// LeetCode509 斐波那契数 fibonacci-number

//斐波那契数，通常用 F(n) 表示，形成的序列称为斐波那契数列。该数列由 0 和 1 开始，后面的每一项数字都是前面两项数字的和。也就是： 
//
// F(0) = 0,   F(1) = 1
//F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
// 
//
// 给定 N，计算 F(N)。 
//
// 
//
// 示例 1： 
//
// 输入：2
//输出：1
//解释：F(2) = F(1) + F(0) = 1 + 0 = 1.
// 
//
// 示例 2： 
//
// 输入：3
//输出：2
//解释：F(3) = F(2) + F(1) = 1 + 1 = 2.
// 
//
// 示例 3： 
//
// 输入：4
//输出：3
//解释：F(4) = F(3) + F(2) = 2 + 1 = 3.
// 
//
// 
//
// 提示： 
//
// 
// 0 ≤ N ≤ 30 
// 
// Related Topics 数组 
// 👍 140 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)

// 注意：严格来说这一道题不是动态规划问题，因为它没有求最值。但是可以学习明白什么是重叠子问题。
// 要计算原问题 f(20)，就得先计算出子问题 f(19) 和 f(18)，然后要计算 f(19)，就要先算出子问题 f(18) 和 f(17)，以此类推。可以发现，存在大量的重叠子问题。

// 解法1：暴力递归。
class Solution {
public:
    int fib(int N) {
        if(N == 1 || N == 2) return 1;

        return fib(N - 1) + fib(N - 2);
    }
};

// 解法2：带备忘录的递归解法。
// 每次算出某个子问题的答案后别着急返回，先记录到备忘录里再返回。当每次遇到一个子问题时先去备忘录查查，如果发现备忘录里面有，直接拿出来用。
class Solution1 {
public:
    int fib(int N) {
       if(N < 1) return 0;

       // 备忘录全初始化为0
       vector<int> memo(N + 1, 0);

       return helper(memo, N);
    }

    int helper(vector<int>& memo, int N) {
        // base case
        if(N == 1 || N == 2) return 1;

        // 已经计算过
        if(memo[N] != 0) return memo[N];

        memo[N] = helper(memo, N - 1) + helper(memo, N - 2);

        return memo[N];
    }
};

// 解法3：dp向量的迭代解法。将备忘录独立出来为一张DP表，利用这张表自底向上求解。
class Solution3 {
public:
    int fib(int N) {
        if(N < 1) return 0;
        if(N == 1 || N == 2) return 1;

        // DP表
        vector<int> dp(N + 1, 0);

        // base case
        dp[1] = dp[2] = 1;
        for(int i = 3; i <= N; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }

        return dp[N];
    }

};

// 解法4：dp向量状态压缩的迭代解法。可以发现，当前状态只和之前的两个状态有关，其实并不需要那么长的一个DP表来存储所有的状态，只要想办法存储之前的两个状态就行了。

class Solution4 {
public:
    int fib(int N) {
        if(N < 1) return 0;
        if(N == 1 || N == 2) return 1;

        int pre = 1, cur = 1;
        for(int i = 3; i <= N; ++i) {
            int sum = pre + cur;
            pre = cur;
            cur = sum;
        }

        return cur;
    }

};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case

    Solution4 solution;
    int temp = solution.fib(20);
    cout << temp << " ";

    return 0;
}

/** 
 * KnowledgePoint: 解法2：实际上，带「备忘录」的递归算法，把一棵存在巨量冗余的递归树通过「剪枝」，
 * 改造成了一幅不存在冗余的递归图，极大减少了子问题（即递归图中节点）的个数。
 * 
 * T(n) =  O(n)
 * 
 * O(n) = 
 * 
 * Summary: 
 */ 