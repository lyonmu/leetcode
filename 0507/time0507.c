//
// Created by muqing on 2022/5/7.
//

#include "time0507.h"

/*
 * 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
 *
 * */
int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    int tag = 0;
    int *result = (int *) malloc(sizeof(int) * 2);
    for (int i = 0; i < numsSize; ++i) {
        tag = target - nums[i];
        printf("tag:%d\n", tag);
        for (int j = i + 1; j < numsSize; ++j) {
            printf("nums[j]:%d\n", nums[j]);
            if (tag == nums[j]) {
                result[0] = i;
                result[1] = j;
                returnSize[0] = 2;
                return result;
            }
        }
    }
    returnSize[0] = 0;
    return result;
}