// LeetCode140 单词拆分 II word-break-ii

//给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，在字符串中增加空格来构建一个句子，使得句子中所有的单词都在词典中。返回所有这些可能的
//句子。 
//
// 说明： 
//
// 
// 分隔时可以重复使用字典中的单词。 
// 你可以假设字典中没有重复的单词。 
// 
//
// 示例 1： 
//
// 输入:
//s = "catsanddog"
//wordDict = ["cat", "cats", "and", "sand", "dog"]
//输出:
//[
//  "cats and dog",
//  "cat sand dog"
//]
// 
//
// 示例 2： 
//
// 输入:
//s = "pineapplepenapple"
//wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
//输出:
//[
//  "pine apple pen apple",
//  "pineapple pen apple",
//  "pine applepen apple"
//]
//解释: 注意你可以重复使用字典中的单词。
// 
//
// 示例 3： 
//
// 输入:
//s = "catsandog"
//wordDict = ["cats", "dog", "sand", "and", "cat"]
//输出:
//[]
// 
// Related Topics 动态规划 回溯算法 
// 👍 203 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)

// 解法1：动态规划。

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {

        int sSize = s.size();
        vector<string> res;
        map<string, vector<string>> m;
        string subStr;

        // dp vector
        vector<vector<string>> dp(sSize+1, vector<string>());

        // base case
        dp[0] = vector<string>{""};

        for(int i = 1; i <= sSize; ++i) {
            m.clear();
            for (int j = 0; j <= i; ++j) {
                subStr = s.substr(j, i - j);
                if (wordDict.cend() != find(wordDict.cbegin(), wordDict.cend(), subStr)) {
                    // 防止个别变态的测试用例爆栈，做一下优化
                    // s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
                    // wordDict = ["a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"]

                    for(const auto &it: dp[j]) {
                        if(it.empty()) {
                            dp[i].push_back(it + subStr);
                        }
                        else {
                            dp[i].push_back(it + " " + subStr);
                        }
                    }
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
//    vector<string> v{"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    vector<string> v{"aaaa","aaa"};
    Solution solution;
//    vector<string> temp = solution.wordBreak("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", v);
    vector<string> temp = solution.wordBreak("aaaaaaa", v);
    for(const auto& t: temp) {
        cout << t << endl;
    }


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