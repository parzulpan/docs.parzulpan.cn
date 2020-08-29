// LeetCode416 分割等和子集 partition-equal-subset-sum

//给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。 
//
// 注意: 
//
// 
// 每个数组中的元素不会超过 100 
// 数组的大小不会超过 200 
// 
//
// 示例 1: 
//
// 输入: [1, 5, 11, 5]
//
//输出: true
//
//解释: 数组可以分割成 [1, 5, 5] 和 [11].
// 
//
// 
//
// 示例 2: 
//
// 输入: [1, 2, 3, 5]
//
//输出: false
//
//解释: 数组不能分割成两个元素和相等的子集.
// 
//
// 
// Related Topics 动态规划 
// 👍 329 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)

// 解法1：动态规划。子集背包问题。
// T(n)：O(n)

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // 求和
        int sum = 0;
        for(auto num: nums) {
            sum += num;
        }

        // 和为奇数时，肯定不满足条件
        if(sum % 2 != 0) return false;

        // dp向量，dp[i][j] = x
        // 表示对于前 i 个物品，当前背包的容量为 j 时，若 x 为 true，则说明可以恰好将背包装满，若 x 为 false，则说明不能恰好将背包装满。
        int size = nums.size();
        sum = sum / 2;
        vector<vector<bool>> dp(size+1, vector<bool>(sum+1, false));

        // base case
        for(int i = 0; i < size; ++i) dp[i][0] = true;

        for(int i = 1; i <= size; ++i) {
            for(int j = 1; j <= sum; ++j) {
                if(j - nums[i-1] < 0) dp[i][j] = dp[i-1][j];
                else dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
            }
        }

        return dp[size][sum];
    }
};

// 解法2：带有状态压缩的动态规划。子集背包问题。注意到 dp[i][j] 都是通过上一行 dp[i-1][..] 转移过来的。
// T(n)：O(n)

class Solution2 {
public:
    bool canPartition(vector<int>& nums) {
        // 求和
        int sum = 0;
        int size = nums.size();
        for(auto num: nums) {
            sum += num;
        }

        // 和为奇数或size只有1时，肯定不满足条件
        if(sum % 2 != 0 || size == 1) return false;

        // dp向量
        sum = sum / 2;
        vector<bool> dp(sum+1, false);

        // base case
        dp[0] = true;

        for(int i = 1; i < size; ++i) {
            for(int j = sum; j >= 0; --j) {
                if(j-nums[i] >= 0) dp[j] = dp[j] || dp[j-nums[i]];
            }
        }

        return dp[sum];
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<int>v{1, 5, 5, 6, 5};

    Solution solution;
    bool temp = solution.canPartition(v);
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