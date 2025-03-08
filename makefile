# Detect OS
ifeq ($(OS),Windows_NT)
    # Windows: Use `where`, suppress errors, and ensure CC is empty if not found
    CC := $(shell where clang 2>NUL || where gcc 2>NUL || where cc 2>NUL)
else
    # Unix: Use `which`, suppress errors, and ensure CC is empty if not found
    CC := $(shell which clang 2>/dev/null || which gcc 2>/dev/null || which cc 2>/dev/null)
endif

# If no compiler is found, fallback to a default
ifneq ($(CC),)
    CC := $(firstword $(CC))
else
    CC := gcc  # Default to GCC if nothing is found
endif

# Show the selected compiler (for debugging)
$(info Using compiler: $(CC))

# Compiler flags
CFLAGS = -Wall -Wextra -lm -I./src

# Directories
SRC_DIR = src
TEST_DIR = tests

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
TEST_FILES := $(wildcard $(TEST_DIR)/*.c) $(filter-out $(SRC_DIR)/main.c, $(SRC_FILES))

# Executable names
CLIENT_EXEC = linalg
TEST_EXEC = test

# Default target
all: $(CLIENT_EXEC)

# Compile the main client program
$(CLIENT_EXEC): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile the test program (excluding main.c)
$(TEST_EXEC): $(TEST_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Clean compiled executables (cross-platform)
clean:
ifeq ($(OS),Windows_NT)
	if exist $(CLIENT_EXEC).exe del /f $(CLIENT_EXEC).exe
	if exist $(TEST_EXEC).exe del /f $(TEST_EXEC).exe
else
	rm -f $(CLIENT_EXEC) $(TEST_EXEC)
endif
