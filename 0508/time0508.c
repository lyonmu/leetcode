//
// Created by muqing on 2022/5/8.
//
#include <stdio.h>
#include <stdlib.h>

#include "time0508.h"

/*
 * 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
 * */
int lengthOfLongestSubstring(char *s) {
    int start = 0, end = 0;
    int retLen = 0;

    while (s[end]) {
        for (int i = start; i < end; i++) {
            if (s[i] == s[end]) {
                start = i + 1;
                break;
            }
        }

        int tempLen = end - start + 1;
        retLen = tempLen > retLen ? tempLen : retLen;
        end += 1;
    }

    return retLen;
}