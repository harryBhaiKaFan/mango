CC=g++
CFLAGS=-lm -lSDL2 -lSDL2_ttf


all: main

main: src/ui/*.cpp src/render/*.cpp src/*.cpp
	$(CC) $^ -o $@ $(CFLAGS)
