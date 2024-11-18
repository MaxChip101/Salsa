# Compiler
CXX = g++

# Directories
SRC_DIR = src
BUILD_64_DIR = build/m64
BUILD_32_DIR = build/m32

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Executable name
EXEC = salsa

# Flags
CXXFLAGS = -Wall -std=c++17 -lncurses

# Build 64-bit binary
m64: CXXFLAGS += -m64
m64: $(BUILD_DIR)/x86_64/$(EXEC)

# Build 32-bit binary
m32: CXXFLAGS += -m32
m32: $(BUILD_DIR)/x86/$(EXEC)

# Compile 64-bit executable
$(BUILD_DIR)/x86_64/$(EXEC): $(SOURCES)
	@mkdir -p $(BUILD_DIR)/x86_64
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

# Compile 32-bit executable
$(BUILD_DIR)/x86/$(EXEC): $(SOURCES)
	@mkdir -p $(BUILD_DIR)/x86
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

# Clean up the build directories
clean:
	rm -rf $(BUILD_DIR)

# Make sure nothing else runs if the Makefile targets are up-to-date
.PHONY: all clean m64 m32
