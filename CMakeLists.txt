cmake_minimum_required(VERSION 3.10)
project(LeetCode C)

set(CMAKE_C_COMPILER /usr/bin/clang-20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 收集所有题目源文件
file(GLOB PROBLEM_SOURCES "src/problems/*.c")

# 为每个题目创建可执行文件
foreach(problem_src ${PROBLEM_SOURCES})
    get_filename_component(PROBLEM_NAME ${problem_src} NAME_WE)
    add_executable(${PROBLEM_NAME} ${problem_src})
endforeach()
