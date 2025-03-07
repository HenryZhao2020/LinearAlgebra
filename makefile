# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra # -g -DNDEBUG

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

# Clean compiled executables
clean:
	rm -f $(CLIENT_EXEC) $(TEST_EXEC)