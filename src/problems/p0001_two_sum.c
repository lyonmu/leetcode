/**
 * 1. 两数之和
 * https://leetcode.cn/problems/two-sum/
 *
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那
 * 两个整数，并返回它们的数组下标。
 *
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。
 *
 * 你可以按任意顺序返回答案。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 内联宏替代 common.h
#define MALLOC(type, n) ((type*)malloc(sizeof(type) * (n)))
#define FREE(ptr) do { free(ptr); (ptr) = NULL; } while(0)

// 内联 swap 函数
static inline void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * 哈希表解法 - O(n) 时间复杂度
 * 使用哈希表存储已经遍历过的数字及其索引
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    // 使用简单的数组作为哈希表（因为题目范围较小）
    // 键：数值，值：索引
    int hash[20000] = {0};  // 假设数值范围在 -10000 到 9999
    int offset = 10000;

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int idx = complement + offset;

        // 检查补数是否在哈希表中
        if (idx >= 0 && idx < 20000 && hash[idx] != 0) {
            int* result = MALLOC(int, 2);
            result[0] = hash[idx] - 1;  // 减1因为初始化为0
            result[1] = i;
            *returnSize = 2;
            return result;
        }

        // 将当前数字存入哈希表
        hash[nums[i] + offset] = i + 1;
    }

    // 没有找到答案
    *returnSize = 0;
    return NULL;
}

/**
 * 双指针解法（需要先排序）- O(nlogn) 时间复杂度
 * 注意：排序会改变原始数组，所以需要返回原始索引
 */
int* twoSumTwoPointers(int* nums, int numsSize, int target, int* returnSize) {
    int* indices = MALLOC(int, numsSize);
    for (int i = 0; i < numsSize; i++) {
        indices[i] = i;
    }

    // 使用临时数组进行排序
    int* temp_nums = MALLOC(int, numsSize);
    memcpy(temp_nums, nums, sizeof(int) * numsSize);

    // 冒泡排序（保持索引同步）
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (temp_nums[j] > temp_nums[j + 1]) {
                swap(&temp_nums[j], &temp_nums[j + 1]);
                swap(&indices[j], &indices[j + 1]);
            }
        }
    }

    int left = 0;
    int right = numsSize - 1;

    while (left < right) {
        int sum = temp_nums[left] + temp_nums[right];
        if (sum == target) {
            int* result = MALLOC(int, 2);
            result[0] = indices[left];
            result[1] = indices[right];
            *returnSize = 2;
            FREE(indices);
            FREE(temp_nums);
            return result;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    FREE(indices);
    FREE(temp_nums);
    *returnSize = 0;
    return NULL;
}

/**
 * 暴力解法 - O(n^2) 时间复杂度
 */
int* twoSumBruteForce(int* nums, int numsSize, int target, int* returnSize) {
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                int* result = MALLOC(int, 2);
                result[0] = i;
                result[1] = j;
                *returnSize = 2;
                return result;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}

int main(void) {
    int nums[] = {2, 7, 11, 15};
    int numsSize = 4;
    int target = 9;
    int returnSize;
    int* result = twoSum(nums, numsSize, target, &returnSize);
    printf("[%d, %d]\n", result[0], result[1]);
    FREE(result);
    return 0;
}
