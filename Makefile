# Compiler
CC = gcc

# Directories
SRC_DIR = src
BUILD_DEBUG_DIR = build/debug
BUILD_LINUX_DIR = build

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS_LINUX = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_LINUX_DIR)/%.o)
OBJECTS_DEBUG = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DEBUG_DIR)/%.o)

# Executable names
EXEC_LINUX = salsac

# Flags
CFLAGS = -Wall -Wextra -I$(SRC_DIR)

# Debug Flags
DEBUGFLAGS = -fsanitize=address -g

# Default rule
all: linux

# Linux build
linux: $(BUILD_LINUX_DIR)/$(EXEC_LINUX)

$(BUILD_LINUX_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_LINUX_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_LINUX_DIR)/$(EXEC_LINUX): $(OBJECTS_LINUX)
	$(CC) $(OBJECTS_LINUX) -o $@

# Debug build
debug: $(BUILD_DEBUG_DIR)/$(EXEC_LINUX)

$(BUILD_DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DEBUG_DIR)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -c $< -o $@

$(BUILD_DEBUG_DIR)/$(EXEC_LINUX): $(OBJECTS_DEBUG)
	$(CC) $(DEBUGFLAGS) $(OBJECTS_DEBUG) -o $@

# Clean up the build directories
clean:
	rm -rf $(BUILD_LINUX_DIR) $(BUILD_DEBUG_DIR)

# Make sure nothing else runs if the Makefile targets are up-to-date
.PHONY: all clean debug linux