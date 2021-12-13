#Which flag to use
CFLAGS := -Wall -g
#Which compiler to use
CC=gcc 

SRC_DIR := Algorithms/src
BUILD_DIR := Algorithms/build
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
target= main

all: $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%) $(target)

$(target): $(target).c $(target).h
	$(CC) $(CFLAGS) $(target).c -o $(target)


$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@
	
permissions:
	chmod u+rx $(target)
	chmod u+rx $(BUILD_DIR)
	chmod u+rx $(SRC_DIR)

help:
	@echo "src: $(SRC_FILES)"
	@echo "Build: $(wildcard $(BUILD_DIR)/*)"

clean:
	rm -rf $(BUILD_DIR)/*
	rm -f $(target)
