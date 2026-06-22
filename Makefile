.PHONY: all build run clean help

.DEFAULT:
	@true

all: build

# 提取参数: make build 1 → PROBLEM=1, make build all → PROBLEM=all
PROBLEM := $(firstword $(filter-out build run all,$(MAKECMDGOALS)))

build:
ifdef PROBLEM
ifeq ($(PROBLEM),all)
	@mkdir -p build
	cd build && cmake .. && make
else
	@mkdir -p build
	@cd build && cmake .. > /dev/null 2>&1
	@src_file=$$(ls src/problems/p$$(printf '%04d' $(PROBLEM))_*.c 2>/dev/null | head -1); \
	if [ -z "$$src_file" ]; then echo "Error: Problem $(PROBLEM) not found"; exit 1; fi; \
	target_name=$$(basename "$$src_file" .c); \
	echo "Building $$target_name..."; \
	cmake --build build --target $$target_name
endif
else
	@mkdir -p build
	cd build && cmake .. && make
endif

run: build
ifdef PROBLEM
ifneq ($(PROBLEM),all)
	@src_file=$$(ls src/problems/p$$(printf '%04d' $(PROBLEM))_*.c 2>/dev/null | head -1); \
	target_name=$$(basename "$$src_file" .c); \
	./build/bin/$$target_name
endif
endif

clean:
	rm -rf build

help:
	@echo "LeetCode C Project"
	@echo "  make build       - Build all problems (default)"
	@echo "  make build N     - Build problem N (e.g. make build 1)"
	@echo "  make build all   - Build all problems"
	@echo "  make run N       - Build and run problem N (e.g. make run 1)"
	@echo "  make clean       - Clean build directory"
	@echo "  make help        - Show this help"
