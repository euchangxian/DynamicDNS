BUILD_DIR := build
EXECUTABLE := DynamicDNS_exec

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
test: build
	pushd $(BUILD_DIR)
	ctest -j $(nproc)
	popd

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
