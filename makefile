
CC=g++

TARGET=snake_game
LIBS=-lncurses -lpthread

SRC_DIR=src
SRC=$(wildcard $(SRC_DIR)/*.cpp)
CFLAGS=-std=gnu++1z -g -W -O2 -Wall -Wshadow

OBJ_DIR=obj
OBJ=$(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


DEP_DIR=.deps
DEPFLAGS= -MMD -MF $(DEP_DIR)/$*.d -MP
DEP=$(OBJ:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo LINKING: $(TARGET)
	@$(CC) -o $@ $^ $(LIBS)
	@echo
	@echo Build successful!

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) $(DEP_DIR)
	@echo COMPILING: $@
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(DEP_DIR):
	@mkdir -p $@

clean:
	@echo CLEANING: dependency files
	@$(RM) -r $(DEP_DIR)
	@echo CLEANING: object files
	@$(RM) -r $(OBJ_DIR)
	@echo CLEANING: executable files
	@$(RM) snake_game
	@echo
	@echo CLEAN

.PHONY: all clean

-include $(DEP)

