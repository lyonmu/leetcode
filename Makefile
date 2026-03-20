.PHONY: all build clean run help

all: build

build:
	@mkdir -p build
	cd build && cmake .. && make

run: build
	./build/bin/p0005_longest_palindromic_substring

clean:
	rm -rf build

help:
	@echo "LeetCode C Project"
	@echo "  make build  - Build all problems"
	@echo "  make clean  - Clean build directory"
