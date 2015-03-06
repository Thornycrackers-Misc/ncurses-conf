# Makefile for my little ncurses experiment
# choose which compiler to use
CC=g++
# Which flags to include
INCLUDES=-lncurses

all: conf.cpp
	$(CC) conf.cpp $(INCLUDES) -o conf.o

clean:
	rm -rf conf.o
