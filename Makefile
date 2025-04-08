CC=g++
CFLAGS=-lm -lSDL2 -lSDL2_ttf
SRC_DIR=src
OBJ_DIR=obj
SRCS=$(shell find $(SRC_DIR) -name '*.cpp')
OBJS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

all: main

main: $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -c -o $@
