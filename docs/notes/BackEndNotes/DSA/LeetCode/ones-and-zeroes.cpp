// LeetCode474 一和零 ones-and-zeroes

//在计算机界中，我们总是追求用有限的资源获取最大的收益。 
//
// 现在，假设你分别支配着 m 个 0 和 n 个 1。另外，还有一个仅包含 0 和 1 字符串的数组。 
//
// 你的任务是使用给定的 m 个 0 和 n 个 1 ，找到能拼出存在于数组中的字符串的最大数量。每个 0 和 1 至多被使用一次。 
//
// 注意: 
//
// 
// 给定 0 和 1 的数量都不会超过 100。 
// 给定字符串数组的长度不会超过 600。 
// 
//
// 示例 1: 
//
// 
//输入: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
//输出: 4
//
//解释: 总共 4 个字符串可以通过 5 个 0 和 3 个 1 拼出，即 "10","0001","1","0" 。
// 
//
// 示例 2: 
//
// 
//输入: Array = {"10", "0", "1"}, m = 1, n = 1
//输出: 2
//
//解释: 你可以拼出 "10"，但之后就没有剩余数字了。更好的选择是拼出 "0" 和 "1" 。
// 
// Related Topics 动态规划 
// 👍 178 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)

// 解法1：动态规划。
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        if(strs.empty()) return 0;

        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(const auto& str: strs) {
            int ones = 0, zeros = 0;
            for(const auto& c: str) {
                (c - '0') == 1 ? ones++ : zeros++;
            }
            for(int i = m; i >= zeros; --i) {
                for(int j = n; j >= ones; --j) {
                    dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones] + 1);
                }
            }
        }

        return dp[m][n];
    }
};

//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<string> v{"10", "0001", "111001", "1", "0"};

    Solution solution;
    int temp = solution.findMaxForm(v, 5, 3);
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