# Compilers
CC := gcc

# Compiler flags
CFLAGS := -std=c99 -iquote include -Wall -Wextra -MMD -MP

# Linker flags
LFLAGS := 

# Source + Build Directories
SRC_DIR := ./src
BUILD_DIR := ./build

# Source files
SRCS := $(shell find $(SRC_DIR) -name "*.c")

# Object files
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Dependencies
DEPS := $(OBJS:%.o=%.d)

# Target
TARGET := app.out

.PHONY: all
all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Final linker rule
$(BUILD_DIR)/$(TARGET): $(OBJS)
	@echo "Linking -> $@"
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@ 
	@echo "Compiled ($^) -> $@"

# *.c build rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

# dependency includes
-include $(DEPS)

# Quick run all rule (useful for debugging)
.PHONY: run
run: all
	./$(BUILD_DIR)/$(TARGET)

# clang-tidy rule. Cause why not?
.PHONY: tidy
tidy:
	clang-tidy "$(SRCS)" -- $(CFLAGS) || true

# Clean rule
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
