# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -lgdi32 -luser32

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
LIB_DIR = $(BUILD_DIR)/lib
BIN_DIR = $(BUILD_DIR)/bin
EXAMPLES_DIR = examples
TESTS_DIR = tests

# Source files
LIB_SRCS = $(wildcard $(SRC_DIR)/*.c)
LIB_OBJS = $(LIB_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
EXAMPLE_SRCS = $(wildcard $(EXAMPLES_DIR)/*.c)
EXAMPLE_BINS = $(EXAMPLE_SRCS:$(EXAMPLES_DIR)/%.c=$(BIN_DIR)/%)
TEST_SRCS = $(wildcard $(TESTS_DIR)/*.c)
TEST_BINS = $(TEST_SRCS:$(TESTS_DIR)/%.c=$(BIN_DIR)/%)

# Library name
LIB_NAME = libeasyui.a
LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

# Main targets
.PHONY: all clean examples tests directories

all: directories $(LIB_TARGET) examples tests

# Create build directories
directories:
	-@mkdir build 2>NUL
	-@mkdir build\lib 2>NUL
	-@mkdir build\bin 2>NUL

# Build library
$(LIB_TARGET): $(LIB_OBJS)
	ar rcs $@ $^

# Compile library objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Build examples
examples: $(EXAMPLE_BINS)

$(BIN_DIR)/%: $(EXAMPLES_DIR)/%.c $(LIB_TARGET)
	$(CC) $(CFLAGS) $< -L$(LIB_DIR) -leasyui $(LDFLAGS) -o $@

# Build tests
tests: $(TEST_BINS)

$(BIN_DIR)/%: $(TESTS_DIR)/%.c $(LIB_TARGET)
	$(CC) $(CFLAGS) $< -L$(LIB_DIR) -leasyui $(LDFLAGS) -o $@

# Run tests
.PHONY: run-tests
run-tests: tests
	-@for %%f in ($(TEST_BINS)) do @echo Running %%f && %%f

# Clean build files
clean:
	-@rd /s /q build 2>NUL || echo Building fresh...

# Install (for system-wide installation)
.PHONY: install
install: all
	-@mkdir "$(DESTDIR)\usr\local\lib" 2>NUL
	-@mkdir "$(DESTDIR)\usr\local\include" 2>NUL
	@copy "$(LIB_TARGET)" "$(DESTDIR)\usr\local\lib\"
	@copy "$(INCLUDE_DIR)\easyui.h" "$(DESTDIR)\usr\local\include\"
