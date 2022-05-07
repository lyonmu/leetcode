//
// Created by muqing on 2022/5/7.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifndef LEETCODE_TIME0507_H
#define LEETCODE_TIME0507_H

#endif //LEETCODE_TIME0507_H

typedef struct ListNode {
    int val;
    struct ListNode *next;
} node, *Node;;

int *twoSum(int *nums, int numsSize, int target, int *returnSize);

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2);
