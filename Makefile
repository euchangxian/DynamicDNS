BUILD_DIR := build
EXECUTABLE := DynamicDNS_exec
TESTS_EXECUTABLE := DynamicDNS_tests_exec

LOG_LEVEL ?= ERROR

override CMAKE_FLAGS := --log-level=$(or ${log-level},${LOG_LEVEL})

.PHONY: all
all: build

.PHONY: build
build:
	cmake -B $(BUILD_DIR) $(CMAKE_FLAGS)
	cmake --build $(BUILD_DIR) -j $(nproc)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: test
test:
	@./$(BUILD_DIR)/$(TESTS_EXECUTABLE)

.PHONY: install
install:
	cmake --install $(BUILD_DIR)

.PHONY: lint
lint:
	cmake -B $(BUILD_DIR)
	run-clang-tidy -p $(BUILD_DIR)

.PHONY: run
run:
	@./$(BUILD_DIR)/$(EXECUTABLE)
