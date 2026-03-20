/**
 * 5. 最长回文子串
 * https://leetcode.cn/problems/longest-palindromic-substring
 *
 * 给你一个字符串 s，找到 s 中最长的回文子串。
 *
 * 如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。
 *
 * 约束条件：
 * 1 <= s.length <= 1000
 * s 仅由数字和英文字母组成
 *
 * 示例 1：
 * 输入：s = "babad"
 * 输出："bab"
 * 解释："aba" 同样是符合题意的答案。
 *
 * 示例 2：
 * 输入：s = "cbbd"
 * 输出："bb"
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 内联宏实现内存管理
#define MALLOC(type, n) ((type *)malloc(sizeof(type) * (n)))
#define FREE(ptr)                                                              \
  do {                                                                         \
    free(ptr);                                                                 \
    (ptr) = NULL;                                                              \
  } while (0)

// 中心扩展法：从每个位置向两边扩展，找到以该位置为中心的最大回文串
// 返回回文串的起始位置
static int expandAroundCenter(char *s, int left, int right, int len) {
  while (left >= 0 && right < len && s[left] == s[right]) {
    left--;
    right++;
  }
  // 返回回文串长度（left 和 right 指向的是扩展后第一次不匹配的位置）
  return right - left - 1;
}

// 使用中心扩展法找最长回文子串
char *longestPalindrome(char *s) {
  if (s == NULL || *s == '\0') {
    char *result = MALLOC(char, 1);
    result[0] = '\0';
    return result;
  }

  int len = strlen(s);
  int start = 0;   // 最长回文子串的起始位置
  int maxLen = 1;  // 最长回文子串的长度

  for (int i = 0; i < len; i++) {
    // 以单字符为中心（奇数长度回文）
    int len1 = expandAroundCenter(s, i, i, len);
    // 以双字符间隙为中心（偶数长度回文）
    int len2 = expandAroundCenter(s, i, i + 1, len);
    // 取较长的回文串
    int currentLen = (len1 > len2) ? len1 : len2;

    if (currentLen > maxLen) {
      maxLen = currentLen;
      // 计算起始位置
      // 对于奇数长度：start = i - maxLen / 2
      // 对于偶数长度：start = i - maxLen / 2 + 1
      // 统一公式：start = i - (maxLen - 1) / 2
      start = i - (maxLen - 1) / 2;
    }
  }

  // 分配结果字符串并复制
  char *result = MALLOC(char, maxLen + 1);
  strncpy(result, s + start, maxLen);
  result[maxLen] = '\0';

  return result;
}

// 判断字符串是否是回文
static int isPalindrome(const char *s, int start, int end) {
  while (start < end) {
    if (s[start] != s[end]) {
      return 0;
    }
    start++;
    end--;
  }
  return 1;
}

// 验证结果是否正确（检查是否为回文且长度正确）
static int verifyResult(const char *input, const char *result) {
  int resultLen = strlen(result);
  // 结果应该是回文
  if (!isPalindrome(result, 0, resultLen - 1)) {
    return 0;
  }
  // 在输入字符串中查找该结果
  int inputLen = strlen(input);
  for (int i = 0; i <= inputLen - resultLen; i++) {
    if (strncmp(input + i, result, resultLen) == 0) {
      return 1;
    }
  }
  return 0;
}

int main(void) {
  int totalTests = 0;
  int passedTests = 0;

  printf("============================================================\n");
  printf("       最长回文子串 - 测试套件 (Longest Palindromic Substring)\n");
  printf("============================================================\n\n");

  // ============================================================
  // 类别 1: LeetCode 问题示例 (Problem Examples)
  // ============================================================
  printf("【类别 1】LeetCode 问题示例 (Problem Examples)\n");
  printf("------------------------------------------------------------\n");

  // 测试 1: "babad" -> "bab" 或 "aba"
  {
    totalTests++;
    char s[] = "babad";
    char *result = longestPalindrome(s);
    // 验证结果是否为 "bab" 或 "aba"
    int isCorrect = (strcmp(result, "bab") == 0 || strcmp(result, "aba") == 0);
    const char *expected = "\"bab\" or \"aba\"";
    printf("测试 %d: [问题示例] %s\n", totalTests, s);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    %s\n", expected);
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // 测试 2: "cbbd" -> "bb"
  {
    totalTests++;
    char s[] = "cbbd";
    char *result = longestPalindrome(s);
    int isCorrect = (strcmp(result, "bb") == 0);
    printf("测试 %d: [问题示例] %s\n", totalTests, s);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"bb\"\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // ============================================================
  // 类别 2: 边界情况 (Edge Cases)
  // ============================================================
  printf("\n【类别 2】边界情况 (Edge Cases)\n");
  printf("------------------------------------------------------------\n");

  // 测试 3: 单个字符 "a"
  {
    totalTests++;
    char s[] = "a";
    char *result = longestPalindrome(s);
    int isCorrect = verifyResult(s, result);
    printf("测试 %d: [边界] 单个字符\n", totalTests);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"a\"\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // 测试 4: 长度为2 "ac"
  {
    totalTests++;
    char s[] = "ac";
    char *result = longestPalindrome(s);
    int isCorrect = verifyResult(s, result);
    printf("测试 %d: [边界] 长度为2\n", totalTests);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"a\" or \"c\"\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // 测试 5: 全部相同字符 "aaa"
  {
    totalTests++;
    char s[] = "aaa";
    char *result = longestPalindrome(s);
    int isCorrect = verifyResult(s, result);
    printf("测试 %d: [边界] 全部相同字符\n", totalTests);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"aaa\"\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // 测试 6: 空结果的2字符不同 "ab"
  {
    totalTests++;
    char s[] = "ab";
    char *result = longestPalindrome(s);
    int isCorrect = verifyResult(s, result);
    printf("测试 %d: [边界] 两字符不同\n", totalTests);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"a\" or \"b\"\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // 测试 7: 长字符串全是相同字符
  {
    totalTests++;
    char s[] = "aaaaaaaaaa"; // 10个a
    char *result = longestPalindrome(s);
    int isCorrect = verifyResult(s, result);
    printf("测试 %d: [边界] 长字符串全相同字符\n", totalTests);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"aaaaaaaaaa\"\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // ============================================================
  // 类别 3: 特殊场景 (Special Scenarios)
  // ============================================================
  printf("\n【类别 3】特殊场景 (Special Scenarios)\n");
  printf("------------------------------------------------------------\n");

  // 测试 8: 回文在开头 "babadada"
  {
    totalTests++;
    char s[] = "babadada";
    char *result = longestPalindrome(s);
    int isCorrect = verifyResult(s, result);
    printf("测试 %d: [特殊] 回文在开头\n", totalTests);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"bab\" (回文在开头)\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // 测试 9: 回文在中间 "abacdba"
  {
    totalTests++;
    char s[] = "abacdba";
    char *result = longestPalindrome(s);
    int isCorrect = verifyResult(s, result);
    printf("测试 %d: [特殊] 回文在中间\n", totalTests);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"aba\" (回文在开头)\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // 测试 10: 回文在结尾 "abacdcaba"
  {
    totalTests++;
    char s[] = "abacdcaba";
    char *result = longestPalindrome(s);
    int isCorrect = verifyResult(s, result);
    printf("测试 %d: [特殊] 回文在结尾\n", totalTests);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"abacdcaba\" (整个字符串是回文)\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // 测试 11: 偶数长度回文 "cbbd"
  {
    totalTests++;
    char s[] = "cbbd";
    char *result = longestPalindrome(s);
    int isCorrect = verifyResult(s, result);
    printf("测试 %d: [特殊] 偶数长度回文\n", totalTests);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"bb\"\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // 测试 12: 奇数长度回文 "racecar"
  {
    totalTests++;
    char s[] = "racecar";
    char *result = longestPalindrome(s);
    int isCorrect = verifyResult(s, result);
    printf("测试 %d: [特殊] 奇数长度回文\n", totalTests);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"racecar\"\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // 测试 13: 多个相同长度回文，取第一个 "abcdeedcba"
  {
    totalTests++;
    char s[] = "abcdeedcba";
    char *result = longestPalindrome(s);
    int isCorrect = verifyResult(s, result);
    printf("测试 %d: [特殊] 多个候选回文\n", totalTests);
    printf("  输入:    \"%s\"\n", s);
    printf("  期望:    \"abcdeedcba\"\n");
    printf("  实际:    \"%s\"\n", result);
    printf("  结果:    %s\n", isCorrect ? "✓ PASS" : "✗ FAIL");
    printf("------------------------------------------------------------\n");
    if (isCorrect) passedTests++;
    FREE(result);
  }

  // ============================================================
  // 测试总结
  // ============================================================
  printf("\n============================================================\n");
  printf("                      测试总结\n");
  printf("============================================================\n");
  printf("总测试数: %d\n", totalTests);
  printf("通过:     %d\n", passedTests);
  printf("失败:     %d\n", totalTests - passedTests);
  printf("通过率:   %.1f%%\n", (double)passedTests / totalTests * 100);
  printf("============================================================\n");

  return (passedTests == totalTests) ? 0 : 1;
}
