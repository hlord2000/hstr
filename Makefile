# Variables
CC = gcc
CFLAGS = -Isrc/inc
DEBUG_FLAGS = -g
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/*/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.c=$(BUILD_DIR)/%.o)

# Targets
all: hstr

debug: CFLAGS += $(DEBUG_FLAGS)
debug: hstr

hstr: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o build/$@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) hstr

tests: $(TEST_OBJECTS) $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o build/$@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean debug tests

