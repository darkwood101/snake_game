
CC=g++
TARGET=snake_game
OBJ_DIR=obj
SRC_DIR=src
SRC=$(wildcard $(SRC_DIR)/*.cpp)
CFLAGS=-std=gnu++1z -g -W -Wall -Wshadow -MMD -MP
LFLAGS=-lncurses -lpthread

OBJ=$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ $(LFLAGS) -o $@
	@echo Compilation successful!

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rv $(OBJ_DIR)
	rm -v $(TARGET)

.PHONY: all clean

