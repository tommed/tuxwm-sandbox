all: program

program: main.o
	cc -g -o program -Wall `pkg-config --cflags --libs cairo-xlib` main.o
	
main.o: main.c
	cc -g -o main.o -Wall `pkg-config --cflags --libs cairo-xlib` -c main.c
