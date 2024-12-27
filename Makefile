BUILD_DIR := build
SRC_DIR := src
EXECUTABLE := DynamicDNS

LOG_LEVEL ?= WARNING

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
	cmake -B $(BUILD_DIR)
	cmake --build $(BUILD_DIR) --target test

.PHONY: install
install:
	cmake --install $(BUILD_DIR)

.PHONY: lint
lint:
	cmake -B $(BUILD_DIR)
	run-clang-tidy -p $(BUILD_DIR)

.PHONY: run
run:
	@./$(BUILD_DIR)/$(SRC_DIR)/$(EXECUTABLE)
