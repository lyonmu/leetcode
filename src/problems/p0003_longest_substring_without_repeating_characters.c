/**
 * 3. 无重复字符的最长子串
 * https://leetcode.cn/problems/longest-substring-without-repeating-characters
 *
 * 给定一个字符串 s ，请你找出其中不含有重复字符的 最长 子串 的长度。
 *
 * 0 <= s.length <= 5 * 10^4
 * s 由英文字母、数字、符号和空格组成
 *
 * 输入：s = "abcabcbb"
 * 输出：3
 * 解释：因为无重复字符的最长子串是 "abc"，所以其长度为 3。
 *
 * 输入：s = "bbbbb"
 * 输出：1
 * 解释：因为无重复字符的最长子串是 "b"，所以其长度为 1。
 *
 * 输入：s = "pwwkew"
 * 输出：3
 * 解释：因为无重复字符的最长子串是 "wke"，所以其长度为 3。
 *
 */

#include <stdio.h>
#include <stdlib.h>

int lengthOfLongestSubstring(char *s) {

  if (s == NULL || *s == '\0') {
    return 0;
  }

  // 记录每个 ASCII 字符最后出现的位置，初始化为 -1
  int last[256];
  for (int i = 0; i < 256; i++) {
    last[i] = -1;
  }

  int max = 0;      // 最大长度
  int left = 0;     // 窗口左边界

  for (int right = 0; s[right] != '\0'; right++) {
    unsigned char c = (unsigned char)s[right];

    // 如果字符在当前窗口内已存在，移动左边界
    if (last[c] >= left) {
      left = last[c] + 1;
    }

    // 更新字符最后出现的位置
    last[c] = right;

    // 更新最大长度
    int current = right - left + 1;
    if (current > max) {
      max = current;
    }
  }

  return max;
}

int main(void) {

  char *test = (char *)malloc(sizeof(char) * 9);

  test[0] = 'a';
  test[1] = 'b';
  test[2] = 'c';
  test[3] = 'a';
  test[4] = 'b';
  test[5] = 'c';
  test[6] = 'b';
  test[7] = 'b';
  test[8] = '\0';

  int len = lengthOfLongestSubstring(test);

  printf("len: %d\n", len);

  free(test);

  char *test1 = (char *)malloc(sizeof(char) * 7);

  test1[0] = 'p';
  test1[1] = 'w';
  test1[2] = 'w';
  test1[3] = 'k';
  test1[4] = 'e';
  test1[5] = 'w';
  test1[6] = '\0';

  int len1 = lengthOfLongestSubstring(test1);

  printf("len: %d\n", len1);

  free(test1);

  char *test2 = (char *)malloc(sizeof(char) * 7);

  test2[0] = 'b';
  test2[1] = 'b';
  test2[2] = 'b';
  test2[3] = 'b';
  test2[4] = 'b';
  test2[5] = 'b';
  test2[6] = '\0';

  int len2 = lengthOfLongestSubstring(test2);

  printf("len: %d\n", len2);

  free(test2);

  return 0;
}
