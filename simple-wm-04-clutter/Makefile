clutteropts=`pkg-config --cflags --libs clutter-0.8`
all: program

program: state.h config.h main.o keyboard.o composite.o opengl.o mouse.o desktop.o size_and_stack.o
	cc -g -o program -Wall -lX11 -lXcomposite -lXrender $(clutteropts) state.h config.h main.o keyboard.o composite.o opengl.o mouse.o desktop.o size_and_stack.o
	
keyboard.o: keyboard.h config.h keyboard.c
	cc -g -o keyboard.o -Wall -lX11 -c keyboard.c
	
mouse.o: mouse.h mouse.c
	cc -g -o mouse.o -Wall -lX11 -c mouse.c
	
size_and_stack.o: size_and_stack.h size_and_stack.c
	cc -g -o size_and_stack.o -Wall -lX11 -c size_and_stack.c
	
composite.o: composite.h composite.c opengl.h opengl.c
	cc -g -o composite.o -Wall -lX11 -lXcomposite -lXrender $(clutteropts) -c composite.c
	
opengl.o: opengl.h opengl.c
	cc -g -o opengl.o $(clutteropts) -c opengl.c
	
desktop.o: desktop.h desktop.c
	cc -g -o desktop.o -Wall -lX11 $(clutteropts) -c desktop.c
	
main.o: main.c state.h
	cc -g -o main.o -Wall -lX11 -lXcomposite -c main.c
