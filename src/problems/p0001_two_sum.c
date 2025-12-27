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
#include "uthash.h"

// 内联宏替代 common.h
#define MALLOC(type, n) ((type*)malloc(sizeof(type) * (n)))
#define FREE(ptr) do { free(ptr); (ptr) = NULL; } while(0)

/**
 * 哈希表结构体
 */
typedef struct {
    int key;              // 数组元素值
    int val;              // 元素索引
    UT_hash_handle hh;    // uthash 句柄
} HashTable;

/**
 * 两数之和 - O(n) 时间复杂度
 * 使用 uthash 哈希表存储已经遍历过的数字及其索引
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashTable* hashtable = NULL;

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        HashTable* entry;

        // 查找补数是否在哈希表中
        HASH_FIND_INT(hashtable, &complement, entry);
        if (entry != NULL) {
            int* result = MALLOC(int, 2);
            result[0] = entry->val;
            result[1] = i;
            *returnSize = 2;
            HASH_CLEAR(hh, hashtable);
            return result;
        }

        // 将当前数字存入哈希表
        entry = MALLOC(HashTable, 1);
        entry->key = nums[i];
        entry->val = i;
        HASH_ADD_INT(hashtable, key, entry);
    }

    *returnSize = 0;
    return NULL;
}

// 内联 swap 函数
static inline void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
/**
 * 两数之和 - O(n log n) 时间复杂度
 * 先排序再使用双指针法
 */
int* twoSumWithDoublePoint(int* nums, int numsSize, int target, int* returnSize) {
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
 * 两数之和 - O(n^2) 时间复杂度
 * 使用双重循环暴力破解
 */
int* twoSumWithDoubleFor(int* nums, int numsSize, int target, int* returnSize) {
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
