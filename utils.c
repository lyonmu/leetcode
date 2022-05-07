//
// Created by muqing on 2022/5/7.
//

#include "utils.h"

// 为数组赋予随机数
void getRand(int *arr, int num) {
    // 设置随机数种子
    srand(time(NULL));
    for (int i = 0; i < num; ++i) {
        arr[i] = rand() % 100;
    }
}

// 遍历数组
void traverseArrays(int *arr, int number) {
    for (int i = 0; i < number; ++i) {
        printf("%5d", arr[i]);
    }
    printf("\n");
}

// 交换数组两个数位置
void swapNumber(int *a, int *b) {
    int tag = *a;
    *a = *b;
    *b = tag;
}
