CC = gcc
CFLAGS = -g -Wall
INCLUDES = -Istructures/include

SRC_DIR = structures
OBJ_DIR = obj
MAIN_DIR = main

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

TARGET = main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(MAIN_DIR)/main.o $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(MAIN_DIR)/main.o: $(MAIN_DIR)/main.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	del /f /q $(TARGET).exe $(MAIN_DIR)\main.o $(OBJ_DIR)\*.o
	rmdir /q /s $(OBJ_DIR)
