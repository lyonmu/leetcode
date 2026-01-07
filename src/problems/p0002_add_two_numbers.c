/**
 * 2. 两数相加
 * https://leetcode.cn/problems/add-two-numbers
 *
 * 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序
 * 的方式存储的，并且每个节点只能存储 一位 数字。
 *
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 *
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 *
 * 每个链表中的节点数在范围 [1, 100] 内
 * 0 <= Node.val <= 9
 * 题目数据保证列表表示的数字不含前导零
 *
 * 输入：l1 = [2,4,3], l2 = [5,6,4]
 * 输出：[7,0,8]
 * 解释：342 + 465 = 807.
 *
 * 输入：l1 = [0], l2 = [0]
 * 输出：[0]
 *
 * 输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * 输出：[8,9,9,9,0,0,0,1]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {

  struct ListNode *res = NULL;
  int exceed = 0;

  while (l1 != NULL || l2 != NULL || exceed != 0) {
    struct ListNode *tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
    tmp->next = NULL;
    if (exceed != 0) {
      tmp->val = exceed;
      exceed = 0;
    } else {
      tmp->val = 0;
    }

    if (l1 != NULL) {
      tmp->val += l1->val;
      l1 = l1->next;
    }
    if (l2 != NULL) {
      tmp->val += l2->val;
      l2 = l2->next;
    }

    exceed = tmp->val / 10;
    tmp->val %= 10;

    if (res == NULL) {
      res = tmp;
    } else {
      struct ListNode *cur = res;
      while (cur->next != NULL) {
        cur = cur->next;
      }
      cur->next = tmp;
    }
  }

  return res;
}

int main(void) {
  struct ListNode *ex1 = (struct ListNode *)malloc(sizeof(struct ListNode));
  struct ListNode *ex2 = (struct ListNode *)malloc(sizeof(struct ListNode));
  struct ListNode *res = NULL;

  ex1->val = 9;
  ex1->next = NULL;

  ex2->val = 1;
  ex2->next = NULL;

  for (size_t i = 0; i < 10; i++) {
    struct ListNode *tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
    tmp->val = 9;
    tmp->next = NULL;

    struct ListNode *cur = ex2;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    cur->next = tmp;
  }

  res = addTwoNumbers(ex1, ex2);

  do {
    printf("%d ", res->val);
    struct ListNode *tmp = res;
    res = res->next;
    free(tmp);
    tmp = NULL;
  } while (res != NULL);

  return 0;
}
