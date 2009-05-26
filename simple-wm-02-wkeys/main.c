#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "keyboard.h"

static Window focused_win; // currently focused window
static Bool app_is_done = False; // when True, application should exit before next X-Event

// handle errors
int handle_xerror(Display *dpy, XErrorEvent *ee) {
	int i=0, alen = sizeof(ee) / sizeof(XErrorEvent);
	for (i=0; i<alen; i++) {
		fprintf(stderr, "An error occurred: %d\n", ee[i].error_code);
	}
	return 0;
}

// program entry point
int main() 
{
	printf("opening display\n");
	Display *d = XOpenDisplay(NULL);
	
	printf("grabbing default screen\n");
	int screen = DefaultScreen(d);
	printf("default screen = %d\n", screen);
	
	printf("grabbing root window\n");
	Window root = DefaultRootWindow(d);
	
	// tell root window you'll be capturing it's events
	XSetWindowAttributes a;
	a.event_mask = KeyReleaseMask|StructureNotifyMask|SubstructureNotifyMask|EnterWindowMask|LeaveWindowMask; // windows created, window-in/out, mouse down/up
	XSelectInput(d, root, a.event_mask);
	
	// handle errors
	XSetErrorHandler(handle_xerror);

	// capture those events
	XEvent e;
	
	// main event loop
	while (!app_is_done) {
		XNextEvent(d, &e);
		
		if (e.type == CreateNotify) {
			printf("Event: create\n");
			XSelectInput(e.xcreatewindow.display, e.xcreatewindow.window, a.event_mask);
			XSetWindowBorderWidth(e.xcreatewindow.display, e.xcreatewindow.window, 1); // always set border to 1px
		}
		
		else if (e.type == ConfigureNotify) {
			printf("EVENT: configure\n");
		}
			
		else if (e.type == EnterNotify) {
			printf("EVENT: focus-in\n");
			focused_win = e.xcrossing.window;
			a.border_pixel = WhitePixel(e.xcrossing.display, screen);
			XChangeWindowAttributes(e.xcrossing.display, focused_win, CWBorderPixel, &a);
		}
		
		else if (e.type == LeaveNotify) {
			printf("EVENT: focus-out\n");
			a.border_pixel = BlackPixel(e.xcrossing.display, screen);
			XChangeWindowAttributes(e.xcrossing.display, e.xcrossing.window, CWBorderPixel, &a);
		}
		
		else if (e.type == KeyRelease) {
			printf("EVENT: key-release[%d]\n", e.xkey.keycode);
			app_is_done = handle_keyevent(&e.xkey);
		}
	}
	
	XCloseDisplay(d); // shutdown xlib gracefully
	return 0;
}
