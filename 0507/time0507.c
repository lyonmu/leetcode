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

/*
 * 给你两个非空 的链表，表示两个非负的整数。它们每位数字都是按照逆序的方式存储的，并且每个节点只能存储一位数字。
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 * */
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    int tagValue = 0;
    struct ListNode *result = NULL;
    struct ListNode *tagNode = NULL;

    struct ListNode *tagNode01 = l1;
    struct ListNode *tagNode02 = l2;
    struct ListNode *node = NULL;

    while (tagNode01 != NULL || tagNode02 != NULL) {
        if (result == NULL) {
            node = (struct ListNode *) malloc(sizeof(struct ListNode));
            node->val = (tagNode01->val + tagNode02->val + tagValue) % 10;
            node->next = NULL;
            tagValue = (tagNode01->val + tagNode02->val + tagValue) / 10;
            result = node;
            tagNode = node;
            tagNode01 = tagNode01->next;
            tagNode02 = tagNode02->next;
        } else {
            if (tagNode01 != NULL) {
                if (tagNode02 != NULL) {
                    node = (struct ListNode *) malloc(sizeof(struct ListNode));
                    node->val = (tagNode01->val + tagNode02->val + tagValue) % 10;
                    node->next = NULL;
                    tagValue = (tagNode01->val + tagNode02->val + tagValue) / 10;
                    tagNode01 = tagNode01->next;
                    tagNode02 = tagNode02->next;
                    tagNode->next = node;
                    tagNode = node;
                } else {
                    node = (struct ListNode *) malloc(sizeof(struct ListNode));
                    node->val = (tagNode01->val + tagValue) % 10;
                    node->next = NULL;
                    tagValue = (tagNode01->val + tagValue) / 10;
                    tagNode01 = tagNode01->next;
                    tagNode->next = node;
                    tagNode = node;
                }
            } else {
                node = (struct ListNode *) malloc(sizeof(struct ListNode));
                node->val = (tagNode02->val + tagValue) % 10;
                node->next = NULL;
                tagValue = (tagNode02->val + tagValue) / 10;
                tagNode02 = tagNode02->next;
                tagNode->next = node;
                tagNode = node;
            }
        }
    }
    if (tagValue != 0 && tagValue != NULL) {
        node = (struct ListNode *) malloc(sizeof(struct ListNode));
        node->val = tagValue;
        node->next = NULL;
        tagNode->next = node;
    }
    return result;
}