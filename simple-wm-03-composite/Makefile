all: program

program: config.h main.o keyboard.o composite.o
	cc -g -o program -Wall -lX11 -lXcomposite -lXrender config.h main.o keyboard.o composite.o
	
keyboard.o: keyboard.h keyboard.c
	cc -g -o keyboard.o -Wall -lX11 -c keyboard.c
	
composite.o: composite.h composite.c
	cc -g -o composite.o -Wall -lX11 -lXcomposite -lXrender -c composite.c
	
main.o: main.c
	cc -g -o main.o -Wall -lX11 -lXcomposite -c main.c
