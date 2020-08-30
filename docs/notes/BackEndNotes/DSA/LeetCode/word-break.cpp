// LeetCode139 单词拆分 word-break

//给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。 
//
// 说明： 
//
// 
// 拆分时可以重复使用字典中的单词。 
// 你可以假设字典中没有重复的单词。 
// 
//
// 示例 1： 
//
// 输入: s = "leetcode", wordDict = ["leet", "code"]
//输出: true
//解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。
// 
//
// 示例 2： 
//
// 输入: s = "applepenapple", wordDict = ["apple", "pen"]
//输出: true
//解释: 返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"。
//     注意你可以重复使用字典中的单词。
// 
//
// 示例 3： 
//
// 输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
//输出: false
// 
// Related Topics 动态规划 
// 👍 589 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)

// 解法1：动态规划。
// 1. 状态：非空字符串s的子串和可选字典wordDict
// 2. 选择：子串在字典wordDict中能否找到
// 3. dp向量：dp[i]= x，从下标0到下标i的非空字符串s的子串，能否在可选字典wordDict中找到。base case为dp[0] = true.
// 4. 状态转移：

class Solution {
public:

    bool wordBreak(string s, vector<string>& wordDict) {
        int sSize = s.size();

        // dp vector
        vector<bool> dp(sSize+1, false);

        // base case
        dp[0] = true;

        //
        for(int i = 1; i <= sSize; ++i) {
            for (int j = 0; j <= i; ++j) {
                if(dp[j] && wordDict.cend() != find(wordDict.cbegin(), wordDict.cend(), s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[sSize];
    }
};
//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case
    vector<string> v{"leet", "code"};

    Solution solution;
    bool temp = solution.wordBreak("leetcode", v);
    cout << temp;

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