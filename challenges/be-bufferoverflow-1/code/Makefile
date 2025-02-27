# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -fno-stack-protector -z execstack -no-pie

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
RES_DIR = resources
DOCKER_BIN_DIR = ../docker/bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Target binary
TARGET = $(BIN_DIR)/client

# Default target
all: $(TARGET) copy_resources copy_to_docker

# Link the target binary
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Copy resources
copy_resources:
	@mkdir -p $(BIN_DIR)
	cp -r $(RES_DIR)/* $(BIN_DIR)/

# Copy bin directory to docker
copy_to_docker:
	rm -rf $(DOCKER_BIN_DIR)
	@mkdir -p $(DOCKER_BIN_DIR)
	cp -r $(BIN_DIR)/* $(DOCKER_BIN_DIR)/

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean copy_resources copy_to_docker