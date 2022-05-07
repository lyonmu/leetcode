cmake_minimum_required(VERSION 3.22)
project(leetcode C)

set(CMAKE_C_STANDARD 99)

add_executable(leetcode main.c 0507/time0507.h 0507/time0507.c utils/utils.h utils/utils.c)
