# Compilers
CC := gcc

# Compiler flags
CFLAGS := -std=c99 -iquote include

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
# DEPS := $(OBJS:%.o=%.d)
# -include $(DEPS)

# Target
TARGET := app.out

# Final linker rule
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $^ -o $@ 
	@echo "Compiled ($^) -> $@"


# *.c build rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all
all: | $(BUILD_DIR) $(BUILD_DIR)/$(TARGET)

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
