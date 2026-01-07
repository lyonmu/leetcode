# LeetCode C 语言

用 C 语言实现的 LeetCode 算法题解集。

## 项目结构

```
leetcode/
├── CMakeLists.txt          # CMake 构建配置
├── Makefile                # 便捷构建脚本
├── README.md               # 项目说明文档
├── src/
│   └── problems/
│       └── p####_name.c    # 各题目源文件（每个包含 main 函数）
└── build/
    └── bin/
        └── p####_name      # 编译后的可执行文件
```

## 已完成题目

| 编号 | 题目                                                     | 难度 | 状态 |
| ---- | -------------------------------------------------------- | ---- | ---- |
| 1    | [两数之和](https://leetcode.cn/problems/two-sum)         | 简单 | ✅   |
| 2    | [两数相加](https://leetcode.cn/problems/add-two-numbers) | 中等 | ✅   |

## 构建与运行

### 环境要求

- **编译器**: clang
- **标准**: C11

### 使用 Makefile 构建

```bash
# 构建所有题目
make build

# 清理构建文件
make clean
```

### 手动构建

```bash
git submodule update --init --recursive
make build
```

运行特定题目：

```bash
./build/bin/p0001_two_sum
```

## 代码规范

- 每个问题文件是独立的可执行程序，包含自己的 `main()` 函数
- 使用内联宏 `MALLOC` 和 `FREE` 进行内存管理
- 编译选项: `-Wall -Wextra -Werror`

## 添加新题目

1. 在 `src/problems/` 目录下创建 `p####_name.c` 文件
2. 文件名格式: `p` + 4 位题目编号 + 下划线 + 题目名
3. 每个文件必须包含独立的 `main()` 函数用于测试
4. 重新运行 `make build` 即可自动编译新题目
