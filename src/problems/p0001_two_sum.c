/**
 * 1. 两数之和
 * https://leetcode.cn/problems/two-sum
 *
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值
 * target  的那两个整数，并返回它们的数组下标。
 *
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
 *
 * 你可以按任意顺序返回答案。
 * 
 * 2 <= nums.length <= 10^4
 * -10^9 <= nums[i] <= 10^9
 * -10^9 <= target <= 10^9
 */

#include <stdio.h>
#include <stdlib.h>

// 内联宏 实现内存管理
#define MALLOC(type, n) ((type *)malloc(sizeof(type) * (n)))
#define FREE(ptr)                                                              \
  do {                                                                         \
    free(ptr);                                                                 \
    (ptr) = NULL;                                                              \
  } while (0)

// 暴力递归破解法
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {

  for (int i = 0; i < numsSize; i++) {
      for (int j = i + 1; j < numsSize; j++) {
        if (nums[i] + nums[j] == target) {
          int *res = (int *)malloc(sizeof(int) * 2);
          res[0] = i;
          res[1] = j;
          *returnSize = 2;
          return res;
        }
    }
  }

  *returnSize = 0;
  return NULL;
}

int main(void) {
  int nums1[] = {2, 7, 11, 15};
  int target1 = 9;
  int nums2[] = {3, 2, 4};
  int target2 = 6;
  int nums3[] = {3, 3};
  int target3 = 6;
  int res = 0;

  int *res1 = twoSum(nums1, sizeof(nums1) / sizeof(nums1[0]), target1, &res);
  printf("%d = %d + %d\n", target1, nums1[res1[0]], nums1[res1[1]]);
  do {
    free(res1);
    res1 = NULL;
  } while (res1 != NULL);

  int *res2 = twoSum(nums2, sizeof(nums2) / sizeof(nums2[0]), target2, &res);
  printf("%d = %d + %d\n", target2, nums2[res2[0]], nums2[res2[1]]);
  do {
    free(res2);
    res2 = NULL;
  } while (res2 != NULL);
  int *res3 = twoSum(nums3, sizeof(nums3) / sizeof(nums3[0]), target3, &res);
  printf("%d = %d + %d\n", target3, nums3[res3[0]], nums3[res3[1]]);
  do {
    free(res3);
    res3 = NULL;
  } while (res3 != NULL);

  return 0;
}
