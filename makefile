
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
	@$(CC) $^ $(LFLAGS) -o $@
	@echo LINKING: $(TARGET)
	@echo
	@echo Build successful!

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo COMPILING: $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@$(RM) -r $(OBJ_DIR)
	@$(RM) snake_game
	@echo CLEAN

.PHONY: all clean

-include $(OBJ:.o=.d)

