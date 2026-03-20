/**
 * 4. 寻找两个正序数组的中位数
 * https://leetcode.cn/problems/median-of-two-sorted-arrays
 *
 * 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
 *
 * 算法的时间复杂度应该为 O(log (m+n)) 。
 *
 * 示例 1：
 * 输入：nums1 = [1,3], nums2 = [2]
 * 输出：2.00000
 * 解释：合并数组 = [1,2,3] ，中位数 2
 *
 * 示例 2：
 * 输入：nums1 = [1,2], nums2 = [3,4]
 * 输出：2.50000
 * 解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
 *
 * 提示：
 * - nums1.length == m
 * - nums2.length == n
 * - 0 <= m <= 1000
 * - 0 <= n <= 1000
 * - 1 <= m + n <= 2000
 * - -10^6 <= nums1[i], nums2[i] <= 10^6
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Memory management macros
#define MALLOC(type, n) ((type *)malloc(sizeof(type) * (n)))
#define FREE(ptr)                                                              \
  do {                                                                         \
    free(ptr);                                                                 \
    (ptr) = NULL;                                                              \
  } while (0)

// Function prototypes

/**
 * @brief Find the median of two sorted arrays
 * @param nums1 Pointer to the first sorted array
 * @param nums1Size Size of the first array
 * @param nums2 Pointer to the second sorted array
 * @param nums2Size Size of the second array
 * @return The median value as a double
 */
double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2,
                              int nums2Size);

/**
 * @brief Find partition index in the shorter array using binary search
 * @param nums1 Pointer to the first sorted array (shorter)
 * @param nums1Size Size of the first array
 * @param nums2 Pointer to the second sorted array
 * @param nums2Size Size of the second array
 * @return The partition index in nums1
 *
 * This helper function implements binary search to find the partition point
 * where all elements on the left side are <= all elements on the right side.
 *
 * Algorithm:
 * 1. Binary search on the shorter array to find partition point
 * 2. Use sentinel values (INT_MIN/INT_MAX) for boundary conditions
 * 3. Ensure: max(left1, left2) <= min(right1, right2)
 * 4. Use safe midpoint calculation to avoid integer overflow
 *
 * Time complexity: O(log(min(m, n)))
 * Space complexity: O(1)
 */
static int findPartitionIndex(int *nums1, int nums1Size, int *nums2,
                              int nums2Size) {
  int left = 0;
  int right = nums1Size;

  while (left <= right) {
    // Partition index in nums1
    int partition1 = left + (right - left) / 2;

    // Partition index in nums2 (total left elements = (total + 1) / 2)
    int totalLeft =
        (nums1Size + nums2Size + 1) / 2; // +1 handles odd total length
    int partition2 = totalLeft - partition1;

    // Get boundary values using sentinel values for edge cases
    int left1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
    int right1 = (partition1 == nums1Size) ? INT_MAX : nums1[partition1];

    int left2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
    int right2 = (partition2 == nums2Size) ? INT_MAX : nums2[partition2];

    // Check if partition is valid: max(left) <= min(right)
    if (left1 <= right2 && left2 <= right1) {
      // Found valid partition
      // The partition is correct, return partition1
      return partition1;
    } else if (left1 > right2) {
      // Too far right in nums1, need to move left
      right = partition1 - 1;
    } else {
      // Too far left in nums1, need to move right
      left = partition1 + 1;
    }
  }

  // This should never happen with valid input
  return 0;
}

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2,
                              int nums2Size) {
  // Ensure nums1 is the shorter array for optimal binary search
  if (nums1Size > nums2Size) {
    // Swap pointers and sizes
    int *tempNums = nums1;
    int tempSize = nums1Size;
    nums1 = nums2;
    nums1Size = nums2Size;
    nums2 = tempNums;
    nums2Size = tempSize;
  }

  // Handle edge cases
  if (nums1Size == 0) {
    // Only nums2 has elements
    if (nums2Size % 2 == 1) {
      return (double)nums2[nums2Size / 2];
    } else {
      return ((double)nums2[nums2Size / 2 - 1] + (double)nums2[nums2Size / 2]) /
             2.0;
    }
  }

  // Find partition using binary search on shorter array
  int partition1 = findPartitionIndex(nums1, nums1Size, nums2, nums2Size);
  int partition2 = (nums1Size + nums2Size + 1) / 2 - partition1;

  // Get boundary values using sentinel values for edge cases
  int left1 = (partition1 == 0) ? INT_MIN : nums1[partition1 - 1];
  int right1 =
      (partition1 == nums1Size) ? INT_MAX : nums1[partition1];

  int left2 = (partition2 == 0) ? INT_MIN : nums2[partition2 - 1];
  int right2 =
      (partition2 == nums2Size) ? INT_MAX : nums2[partition2];

  // Calculate median based on total length (odd or even)
  if ((nums1Size + nums2Size) % 2 == 1) {
    // Odd total length: median is max of left values
    return (double)(left1 > left2 ? left1 : left2);
  } else {
    // Even total length: median is average of max left and min right
    double maxLeft = (left1 > left2) ? (double)left1 : (double)left2;
    double minRight = (right1 < right2) ? (double)right1 : (double)right2;
    return (maxLeft + minRight) / 2.0;
  }
}

// Helper function to print array
static void printArray(int *arr, int size) {
  printf("[");
  for (int i = 0; i < size; i++) {
    printf("%d%s", arr[i], (i < size - 1) ? ", " : "");
  }
  printf("]");
}

// Helper function to run a single test case
static int runTest(int *nums1, int nums1Size, int *nums2, int nums2Size,
                   double expected, int testNum, const char *description) {
  double result = findMedianSortedArrays(nums1, nums1Size, nums2, nums2Size);
  int passed = (result == expected);

  printf("Test %d: %s\n", testNum, description);
  printf("  nums1 = ");
  if (nums1Size == 0)
    printf("[]");
  else
    printArray(nums1, nums1Size);
  printf(", nums2 = ");
  if (nums2Size == 0)
    printf("[]");
  else
    printArray(nums2, nums2Size);
  printf("\n");
  printf("  Result: %.5f, Expected: %.5f -> %s\n", result, expected,
         passed ? "PASS" : "FAIL");

  return passed;
}

int main(void) {
  int passed = 0;
  int total = 0;

  printf("========================================\n");
  printf("   Median of Two Sorted Arrays Tests\n");
  printf("========================================\n\n");

  // ===== Example 1: nums1 = [1,3], nums2 = [2] -> median = 2.0 =====
  {
    int *nums1 = MALLOC(int, 2);
    int *nums2 = MALLOC(int, 1);
    nums1[0] = 1;
    nums1[1] = 3;
    nums2[0] = 2;
    printf("Example 1: Basic case (odd total length)\n");
    printf("  Expected: 2.0\n");
    if (runTest(nums1, 2, nums2, 1, 2.0, ++total,
                "nums1=[1,3], nums2=[2]"))
      passed++;
    FREE(nums1);
    FREE(nums2);
  }
  printf("\n");

  // ===== Example 2: nums1 = [1,2], nums2 = [3,4] -> median = 2.5 =====
  {
    int *nums1 = MALLOC(int, 2);
    int *nums2 = MALLOC(int, 2);
    nums1[0] = 1;
    nums1[1] = 2;
    nums2[0] = 3;
    nums2[1] = 4;
    printf("Example 2: Basic case (even total length)\n");
    printf("  Expected: 2.5\n");
    if (runTest(nums1, 2, nums2, 2, 2.5, ++total,
                "nums1=[1,2], nums2=[3,4]"))
      passed++;
    FREE(nums1);
    FREE(nums2);
  }
  printf("\n");

  // ===== Edge case: One array empty =====
  {
    int *nums2 = MALLOC(int, 1);
    nums2[0] = 1;
    printf("Edge Case: Empty first array\n");
    printf("  Expected: 1.0\n");
    if (runTest(NULL, 0, nums2, 1, 1.0, ++total, "nums1=[], nums2=[1]"))
      passed++;
    FREE(nums2);
  }
  printf("\n");

  {
    int *nums1 = MALLOC(int, 1);
    nums1[0] = 2;
    printf("Edge Case: Empty second array\n");
    printf("  Expected: 2.0\n");
    if (runTest(nums1, 1, NULL, 0, 2.0, ++total, "nums1=[2], nums2=[]"))
      passed++;
    FREE(nums1);
  }
  printf("\n");

  // ===== Edge case: Arrays with negative numbers =====
  {
    int *nums1 = MALLOC(int, 3);
    int *nums2 = MALLOC(int, 2);
    nums1[0] = -5;
    nums1[1] = -3;
    nums1[2] = -1;
    nums2[0] = -2;
    nums2[1] = 0;
    printf("Edge Case: Negative numbers (odd total)\n");
    printf("  Merged: [-5,-3,-2,-1,0], median=-2.0\n");
    printf("  Expected: -2.0\n");
    if (runTest(nums1, 3, nums2, 2, -2.0, ++total,
                "nums1=[-5,-3,-1], nums2=[-2,0]"))
      passed++;
    FREE(nums1);
    FREE(nums2);
  }
  printf("\n");

  {
    int *nums1 = MALLOC(int, 2);
    int *nums2 = MALLOC(int, 2);
    nums1[0] = -10;
    nums1[1] = -5;
    nums2[0] = -3;
    nums2[1] = 0;
    printf("Edge Case: Negative numbers (even total)\n");
    printf("  Merged: [-10,-5,-3,0], median=-4.0\n");
    printf("  Expected: -4.0\n");
    if (runTest(nums1, 2, nums2, 2, -4.0, ++total,
                "nums1=[-10,-5], nums2=[-3,0]"))
      passed++;
    FREE(nums1);
    FREE(nums2);
  }
  printf("\n");

  {
    int *nums1 = MALLOC(int, 2);
    int *nums2 = MALLOC(int, 1);
    nums1[0] = -1000000;
    nums1[1] = 1000000;
    nums2[0] = -500000;
    printf("Edge Case: Extreme negative and positive values\n");
    printf("  Merged: [-1000000,-500000,1000000], median=-500000.0\n");
    printf("  Expected: -500000.0\n");
    if (runTest(nums1, 2, nums2, 1, -500000.0, ++total,
                "nums1=[-1000000,1000000], nums2=[-500000]"))
      passed++;
    FREE(nums1);
    FREE(nums2);
  }
  printf("\n");

  // ===== Edge case: Arrays with duplicate values =====
  {
    int *nums1 = MALLOC(int, 2);
    int *nums2 = MALLOC(int, 2);
    nums1[0] = 0;
    nums1[1] = 0;
    nums2[0] = 0;
    nums2[1] = 0;
    printf("Edge Case: All duplicates\n");
    printf("  Merged: [0,0,0,0], median=0.0\n");
    printf("  Expected: 0.0\n");
    if (runTest(nums1, 2, nums2, 2, 0.0, ++total,
                "nums1=[0,0], nums2=[0,0]"))
      passed++;
    FREE(nums1);
    FREE(nums2);
  }
  printf("\n");

  {
    int *nums1 = MALLOC(int, 3);
    int *nums2 = MALLOC(int, 3);
    nums1[0] = 1;
    nums1[1] = 1;
    nums1[2] = 2;
    nums2[0] = 1;
    nums2[1] = 1;
    nums2[2] = 3;
    printf("Edge Case: Many duplicates (odd total)\n");
    printf("  Merged: [1,1,1,1,2,3], median=1.0\n");
    printf("  Expected: 1.0\n");
    if (runTest(nums1, 3, nums2, 3, 1.0, ++total,
                "nums1=[1,1,2], nums2=[1,1,3]"))
      passed++;
    FREE(nums1);
    FREE(nums2);
  }
  printf("\n");

  {
    int *nums1 = MALLOC(int, 3);
    int *nums2 = MALLOC(int, 3);
    nums1[0] = 1;
    nums1[1] = 2;
    nums1[2] = 3;
    nums2[0] = 3;
    nums2[1] = 3;
    nums2[2] = 4;
    printf("Edge Case: Duplicates across arrays (even total)\n");
    printf("  Merged: [1,2,3,3,3,4], median=3.0\n");
    printf("  Expected: 3.0\n");
    if (runTest(nums1, 3, nums2, 3, 3.0, ++total,
                "nums1=[1,2,3], nums2=[3,3,4]"))
      passed++;
    FREE(nums1);
    FREE(nums2);
  }
  printf("\n");

  // ===== Additional edge cases =====
  {
    int *nums1 = MALLOC(int, 1);
    int *nums2 = MALLOC(int, 1);
    nums1[0] = 2;
    nums2[0] = 1;
    printf("Additional: Two single elements\n");
    printf("  Merged: [1,2], median=1.5\n");
    printf("  Expected: 1.5\n");
    if (runTest(nums1, 1, nums2, 1, 1.5, ++total, "nums1=[2], nums2=[1]"))
      passed++;
    FREE(nums1);
    FREE(nums2);
  }
  printf("\n");

  {
    int *nums1 = MALLOC(int, 5);
    int *nums2 = MALLOC(int, 5);
    for (int i = 0; i < 5; i++) {
      nums1[i] = 2 * i + 1;
      nums2[i] = 2 * i + 2;
    }
    printf("Additional: Same length arrays\n");
    printf("  nums1=[1,3,5,7,9], nums2=[2,4,6,8,10]\n");
    printf("  Merged: [1,2,3,4,5,6,7,8,9,10], median=5.5\n");
    printf("  Expected: 5.5\n");
    if (runTest(nums1, 5, nums2, 5, 5.5, ++total,
                "nums1=[1,3,5,7,9], nums2=[2,4,6,8,10]"))
      passed++;
    FREE(nums1);
    FREE(nums2);
  }
  printf("\n");

  // ===== Summary =====
  printf("========================================\n");
  printf("           Test Summary\n");
  printf("========================================\n");
  printf("Passed: %d/%d\n", passed, total);
  printf("Status: %s\n", (passed == total) ? "ALL TESTS PASSED!" : "SOME TESTS FAILED");
  printf("========================================\n");

  return (passed == total) ? 0 : 1;
}
