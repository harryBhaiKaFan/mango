CC=g++
CFLAGS=-I include -lm -lSDL2 -lSDL2_ttf


all: main

main: src/*
	$(CC) $^ -o $@ $(CFLAGS)
