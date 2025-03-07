# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -g # -DNDEBUG

# Directories
SRC_DIR = src
TEST_DIR = tests

# Source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
TEST_FILES := $(wildcard $(TEST_DIR)/*.c) $(SRC_FILES)

# Executable names
CLIENT_EXEC = linalg
TEST_EXEC = test

# Default target
all: $(CLIENT_EXEC)

# Compile the main client program directly from source files
$(CLIENT_EXEC): $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile the test program directly from source files
$(TEST_EXEC): $(TEST_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Run tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Clean compiled executables
clean:
	rm -f $(CLIENT_EXEC) $(TEST_EXEC)
