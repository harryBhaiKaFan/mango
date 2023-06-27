CC=g++
CFLAGS=-lm -lSDL2 -lSDL2_ttf


all: main

main: main.cpp
	$(CC) $^ -o $@ $(CFLAGS)
