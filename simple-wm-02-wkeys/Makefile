all: program

program: main.o keyboard.o config.h
	cc -g -o program -Wall -lX11 config.h main.o keyboard.o
	
keyboard.o: keyboard.h keyboard.c
	cc -g -o keyboard.o -Wall -lX11 -c keyboard.c
	
main.o: main.c
	cc -g -o main.o -Wall -lX11 -c main.c
