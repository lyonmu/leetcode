.PHONY: all build clean run help

all: build

build:
	@mkdir -p build
	cd build && cmake .. && make

run: build
# 	./build/bin/p0001_two_sum
# 	./build/bin/p0002_add_two_numbers
	./build/bin/p0003_longest_substring_without_repeating_characters

clean:
	rm -rf build

help:
	@echo "LeetCode C Project"
	@echo "  make build  - Build all problems"
	@echo "  make clean  - Clean build directory"
