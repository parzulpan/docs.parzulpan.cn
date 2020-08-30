// LeetCode72 编辑距离 edit-distance

//给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。 
//
// 你可以对一个单词进行如下三种操作： 
//
// 
// 插入一个字符 
// 删除一个字符 
// 替换一个字符 
// 
//
// 
//
// 示例 1： 
//
// 输入：word1 = "horse", word2 = "ros"
//输出：3
//解释：
//horse -> rorse (将 'h' 替换为 'r')
//rorse -> rose (删除 'r')
//rose -> ros (删除 'e')
// 
//
// 示例 2： 
//
// 输入：word1 = "intention", word2 = "execution"
//输出：5
//解释：
//intention -> inention (删除 't')
//inention -> enention (将 'i' 替换为 'e')
//enention -> exention (将 'n' 替换为 'x')
//exention -> exection (将 'n' 替换为 'c')
//exection -> execution (插入 'u')
// 
// Related Topics 字符串 动态规划 
// 👍 978 👎 0


// pan: test header
#include "base-dp.h"

//leetcode submit region begin(Prohibit modification and deletion)
// 解法1：带备忘录的递归。解决两个字符串的动态规划问题，一般都是用两个指针 i,j 分别指向两个字符串的最后，然后一步步往前走，缩小问题的规模。
class Solution {
public:
    string s1, s2;
    int minDistance(string word1, string word2) {
        s1 = word1;
        s2 = word2;
        return dp(word1.size() - 1, word2.size() - 1);
    }

    int dp(int i, int j) {
        // base case
        if(i == -1 || j == -1) return 0;
        if(i == 0 || j == 0) return 1;

        if(s1[i] == s2[j]) {
            // 跳过操作，匹配上，什么都不做，s1和s2指针前移，操作数不变
            return dp(i - 1, j - 1);
        } else {
            // 插入操作，s1插入一个字符匹配上s2，s2指针前移，操作数加1
            int a = dp(i, j - 1) + 1;

            // 删除操作，s1删除一个字符匹配上s2，s1指针前移，操作数加1
            int b = dp(i - 1, j) + 1;

            // 替换操作，s1替换一个字符匹配上s2，s1和s2指针前移，操作数加1
            int c = dp(i - 1, j - 1) + 1;

            // 得到这三种操作所需最小操作数
            return min(a, min(b, c));
        }
    }
};
//leetcode submit region end(Prohibit modification and deletion)


// pan: test main
int main() {

    // test case

    Solution solution;
    int temp = solution.minDistance("intention", "execution");
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