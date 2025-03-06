# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -fno-stack-protector -z execstack -no-pie

# Directories
SRC_DIR = code/src
OBJ_DIR = code/obj
BIN_DIR = code/bin
BIN_PRIVATE_DIR = code/bin/private
BIN_PUBLIC_DIR = code/bin/public
RES_PRIVATE_DIR = code/resources/private
RES_PUBLIC_DIR = code/resources/public
DOCKER_BIN_DIR = docker/bin
FILES_DIR = files

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Target binaries
TARGET_PRIVATE = $(BIN_PRIVATE_DIR)/client
TARGET_PUBLIC = $(BIN_PUBLIC_DIR)/client

# Default target
all: clean $(TARGET_PRIVATE) $(TARGET_PUBLIC) copy_resources copy_to_docker zip_public copy_client_c

# Link the target binaries
$(TARGET_PRIVATE): $(OBJS)
	@mkdir -p $(BIN_PRIVATE_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET_PUBLIC): $(OBJS)
	@mkdir -p $(BIN_PUBLIC_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Copy resources
copy_resources:
	@mkdir -p $(BIN_PRIVATE_DIR)
	@mkdir -p $(BIN_PUBLIC_DIR)
	cp -r $(RES_PRIVATE_DIR)/* $(BIN_PRIVATE_DIR)/
	cp -r $(RES_PUBLIC_DIR)/* $(BIN_PUBLIC_DIR)/

# Copy private bin directory to docker
copy_to_docker:
	rm -rf $(DOCKER_BIN_DIR)
	@mkdir -p $(DOCKER_BIN_DIR)
	cp -r $(BIN_PRIVATE_DIR)/* $(DOCKER_BIN_DIR)/

# Zip public bin directory
zip_public:
	@mkdir -p $(FILES_DIR)
	cd $(BIN_PUBLIC_DIR) && zip -r ../../../$(FILES_DIR)/distribution.zip *

# Copy client.c to files
copy_client_c:
	cp $(SRC_DIR)/client.c $(FILES_DIR)/client.c

# Clean up build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_PRIVATE_DIR) $(BIN_PUBLIC_DIR) $(BIN_DIR) $(DOCKER_BIN_DIR) $(FILES_DIR)/distribution.zip $(FILES_DIR)/client.c

.PHONY: all clean copy_resources copy_to_docker zip_public copy_client_c